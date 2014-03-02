//
//  ieIGameTransition.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieIGameTransition.h"
#include "ieIGraphicsContext.h"
#include "ieEvent.h"
#include "ieIOGLWindow.h"
#include "ieResourceAccessor.h"
#include "ieShader.h"
#include "ieShape.h"
#include "ieCamera.h"
#include "ieTexture.h"

ieIGameTransition::ieIGameTransition(const std::string& name,
                                   const std::shared_ptr<ieIOGLWindow>& window) :
ieStage(glm::vec4(0.0f, 0.0f, window->getWidth(), window->getHeight())),
m_window(window),
m_name(name),
m_shader(nullptr),
m_shape(nullptr),
m_material(nullptr),
m_screenTexture(nullptr)
{
#if defined (__IOS__)
    m_graphicsContext = ieIGraphicsContext::createGraphicsContext(m_window, E_PLATFORM_API_IOS);
#elif defined(__WIN32__)
	m_graphicsContext = ieIGraphicsContext::createGraphicsContext(m_window, E_PLATFORM_API_WIN32);
#elif defined(__NDK__)
    m_graphicsContext = ieIGraphicsContext::createGraphicsContext(m_window, E_PLATFORM_API_NDK);
#endif
    
    m_functionOnTransitionRegister = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieIGameTransition::onRegistered, this, std::placeholders::_1));
    m_functionOnTransitionUnregister = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieIGameTransition::onUnregistered, this, std::placeholders::_1));
    
    m_functionOnTransitionEnter = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieIGameTransition::onEnter, this, std::placeholders::_1));
    m_functionOnTransitionExit = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieIGameTransition::onExit, this, std::placeholders::_1));
    
    m_functionOnPresentFrame = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieIGameTransition::onPresentFrame, this, std::placeholders::_1));
    
    m_resourceAccessor = std::make_shared<ieResourceAccessor>();
    m_camera = std::make_shared<ieCamera>(m_window->getWidth(), m_window->getHeight());
    
    ieIGameTransition::addEventListener(kEVENT_ON_TRANSITION_REGISTER, m_functionOnTransitionRegister);
    ieIGameTransition::addEventListener(kEVENT_ON_TRANSITION_UNREGISTER, m_functionOnTransitionUnregister);
}

ieIGameTransition::~ieIGameTransition(void)
{
    ieIGameTransition::removeEventListener(kEVENT_ON_TRANSITION_REGISTER, m_functionOnTransitionRegister);
    ieIGameTransition::removeEventListener(kEVENT_ON_TRANSITION_UNREGISTER, m_functionOnTransitionUnregister);
}

std::string ieIGameTransition::getName(void) const
{
    return m_name;
}

void ieIGameTransition::onResize(const std::shared_ptr<ieEvent>& event)
{
    ieStage::onResize(event);
    m_camera->onResize(m_window->getWidth(), m_window->getHeight());
    m_screenTexture = std::make_shared<ieTexture>(m_colorAttachment, m_window->getWidth(), m_window->getHeight());
}

void ieIGameTransition::onRegistered(const std::shared_ptr<ieEvent>& event)
{
    ieIGameTransition::addEventListener(kEVENT_ON_TRANSITION_ENTER, m_functionOnTransitionEnter);
    ieIGameTransition::addEventListener(kEVENT_ON_TRANSITION_EXIT, m_functionOnTransitionExit);
    
    m_shader = m_resourceAccessor->getShader(ieShaderV2T2C4_vert, ieShaderV2T2C4_frag, shared_from_this());
    m_shape = std::make_shared<ieShape>(glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f));
    
    m_material = std::make_shared<ieMaterial>();
    m_material->setBlending(false);
    m_material->setCulling(false);
    m_material->setDepthTest(false);
    m_material->setShader(m_shader);
}

void ieIGameTransition::onUnregistered(const std::shared_ptr<ieEvent>& event)
{
    ieIGameTransition::removeEventListener(kEVENT_ON_TRANSITION_ENTER, m_functionOnTransitionEnter);
    ieIGameTransition::removeEventListener(kEVENT_ON_TRANSITION_EXIT, m_functionOnTransitionExit);
    
    m_shader->removeOwner(shared_from_this());
    m_shader = nullptr;
    m_shape = nullptr;
    m_material = nullptr;
}

void ieIGameTransition::onEnter(const std::shared_ptr<ieEvent>& event)
{
    std::shared_ptr<ieStage> stage = std::static_pointer_cast<ieStage>(shared_from_this());
    std::shared_ptr<ieEvent> eventOnStageAdded = std::make_shared<ieEvent>(kEVENT_ON_ADDED, stage);
    assert(m_window != nullptr);
    eventOnStageAdded->addObjectWithKey(m_resourceAccessor, "resourceAccessor");
    eventOnStageAdded->addObjectWithKey(stage, "stage");
    eventOnStageAdded->addObjectWithKey(m_camera, "camera");
    ieIGameTransition::dispatchEvent(eventOnStageAdded);
    
    m_screenTexture = std::make_shared<ieTexture>(m_colorAttachment, m_window->getWidth(), m_window->getHeight());
    ieIGameTransition::addEventListener(kEVENT_ON_PRESENT_FRAME, m_functionOnPresentFrame);
}

void ieIGameTransition::onExit(const std::shared_ptr<ieEvent>& event)
{
    std::shared_ptr<ieStage> stage = std::static_pointer_cast<ieStage>(shared_from_this());
    std::shared_ptr<ieEvent> eventOnStageRemoved = std::make_shared<ieEvent>(kEVENT_ON_REMOVED, stage);
    ieIGameTransition::dispatchEvent(eventOnStageRemoved);
    
    m_shader->setTexture(0, E_SHADER_SAMPLER_01);
    
    ieIGameTransition::removeEventListener(kEVENT_ON_PRESENT_FRAME, m_functionOnPresentFrame);
}

void ieIGameTransition::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    ieStage::onUpdate(event);
}

void ieIGameTransition::onDraw(const std::shared_ptr<ieEvent>& event)
{
    ieStage::onDraw(event);
}

void ieIGameTransition::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    ieStage::onEnterFrame(event);
}

void ieIGameTransition::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    ieStage::onExitFrame(event);
}

void ieIGameTransition::onPresentFrame(const std::shared_ptr<ieEvent>& event)
{
    assert(m_graphicsContext != nullptr);
    
    glBindFramebuffer(GL_FRAMEBUFFER, m_graphicsContext->getFrameBuffer());
    glBindRenderbuffer(GL_RENDERBUFFER, m_graphicsContext->getRenderBuffer());
    glViewport(0, 0, m_window->getWidth(), m_window->getHeight());
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    assert(m_shader != nullptr);
    assert(m_shape != nullptr);
    
    m_shader->bind();
    m_shader->setMatrix4x4(glm::mat4x4(1.0f), E_SHADER_UNIFORM_MODELVIEW);
    m_shader->setMatrix4x4(glm::mat4x4(1.0f), E_SHADER_UNIFORM_PROJECTION);
    m_shader->setTexture(m_screenTexture->getTexture(), E_SHADER_SAMPLER_01);
    m_shape->bind(m_shader->getAttributes());
    
    m_shape->draw();
    
    m_shader->unbind();
    m_shape->unbind(m_shader->getAttributes());
    
#if defined(__IOS__)
    
    const GLenum discards[] = { GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT} ;
    glDiscardFramebufferEXT(GL_FRAMEBUFFER, 2, discards);
    
#elif defined(__WIN32__)
    
#endif

    m_graphicsContext->draw();
}
