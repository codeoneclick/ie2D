//
//  ieStage.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieStage.h"
#include "ieEvent.h"
#include "ieObject.h"

ieStage::ieStage(const glm::vec4& frame) :
ieDisplayObjectContainer(frame),
m_frameBuffer(0),
m_colorAttachment(0),
m_depthAttachment(0)
{
     m_functionOnResize = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieStage::onResize, this, std::placeholders::_1));
}

ieStage::~ieStage(void)
{

}

void ieStage::createFBO(ui32 width, ui32 height)
{
    if(m_frameBuffer != 0)
    {
        glDeleteFramebuffers(1, &m_frameBuffer);
    }
    if(m_colorAttachment != 0)
    {
        glDeleteTextures(1, &m_colorAttachment);
    }
    if(m_depthAttachment != 0)
    {
        glDeleteTextures(1, &m_depthAttachment);
    }
    
    glGenTextures(1, &m_colorAttachment);
    glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 width,
                 height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    
    glGenTextures(1, &m_depthAttachment);
    glBindTexture(GL_TEXTURE_2D, m_depthAttachment);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
#if defined(__NDK__)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 width,
                 height,
                 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
#else
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 width,
                 height,
                 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);
#endif
    
    glGenFramebuffers(1, &m_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0);
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
}

void ieStage::onResize(const std::shared_ptr<ieEvent>& event)
{
    ui32 width = event->getValueWithKey("width").getValue<ui32>();
    ui32 height = event->getValueWithKey("height").getValue<ui32>();
    m_frame.z = width;
    m_frame.w = height;
    ieStage::createFBO(width, height);
    std::cout<<"ieStage::onResize"<<std::endl;
}

void ieStage::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onUpdate(event);
}

void ieStage::onDraw(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onDraw(event);
}

void ieStage::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glViewport(0, 0, m_frame.z, m_frame.w);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    ieDisplayObjectContainer::onEnterFrame(event);
}

void ieStage::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
#if defined(__IOS__)
    
    const GLenum discards[] = { GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT };
    glDiscardFramebufferEXT(GL_FRAMEBUFFER, 2, discards);
    
#elif defined(__WIN32__)
    
#endif
    
    ieDisplayObjectContainer::onExitFrame(event);
}

void ieStage::onAdded(const std::shared_ptr<ieEvent>& event)
{
    ieStage::createFBO(m_frame.z, m_frame.w);
    ieDisplayObjectContainer::onAdded(event);
    std::cout<<"ieStage::onAdded"<<std::endl;
    ieStage::addEventListener(kEVENT_ON_RESIZE, m_functionOnResize);
}

void ieStage::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onRemoved(event);
    ieStage::removeEventListener(kEVENT_ON_RESIZE, m_functionOnResize);
}


