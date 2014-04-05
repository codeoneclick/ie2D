//
//  ieInteractiveObject.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieInteractiveObject.h"
#include "ieTouchRecognizer.h"
#include "ieEvent.h"
#include "ieShader.h"
#include "ieCamera.h"
#include "ieShape.h"
#include "ieResourceAccessor.h"

ieInteractiveObject::ieInteractiveObject(const glm::vec4& frame) :
ieDisplayObject(frame),
m_touchMaskMaterial(std::make_shared<ieMaterial>()),
m_touchRecognizer(nullptr),
m_isTouchable(false)
{
    m_description = "ieInteractiveObject";
    m_functionOnUpdateTouchMask = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieInteractiveObject::onUpdateTouchMask,
                                                                                        this, std::placeholders::_1));
}

ieInteractiveObject::~ieInteractiveObject(void)
{
    
}

void ieInteractiveObject::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onUpdate(event);
}

void ieInteractiveObject::onDraw(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onDraw(event);
}

void ieInteractiveObject::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onEnterFrame(event);
}

void ieInteractiveObject::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onExitFrame(event);
}

void ieInteractiveObject::onUpdateTouchMask(const std::shared_ptr<ieEvent>& event)
{
    if(m_visible && m_active)
    {
        assert(m_camera != nullptr);
        assert(m_touchMaskMaterial->getShader() != nullptr);
        m_touchMaskMaterial->bind();
        
        assert(m_touchMaskMaterial != nullptr);
        m_touchMaskMaterial->setTexture(ieDisplayObject::getTexture(E_SHADER_SAMPLER_01), E_SHADER_SAMPLER_01);
        m_touchMaskMaterial->setTexture(ieDisplayObject::getTexture(E_SHADER_SAMPLER_02), E_SHADER_SAMPLER_02);
        m_touchMaskMaterial->setTexture(ieDisplayObject::getTexture(E_SHADER_SAMPLER_03), E_SHADER_SAMPLER_03);
        m_touchMaskMaterial->setTexture(ieDisplayObject::getTexture(E_SHADER_SAMPLER_04), E_SHADER_SAMPLER_04);
        m_touchMaskMaterial->getShader()->setVector4Custom(glm::vec4(1.0, 0.0, 0.0, 1.0), "uniform_touchUniqueColor");
        
        m_touchMaskMaterial->getShader()->setMatrix4x4(m_localTransformation, E_SHADER_UNIFORM_MODELVIEW);
        m_touchMaskMaterial->getShader()->setMatrix4x4(m_camera->getProjection(), E_SHADER_UNIFORM_PROJECTION);
        m_shape->bind(m_touchMaskMaterial->getShader()->getAttributes());
        m_shape->draw();
        
        m_touchMaskMaterial->unbind();
        m_shape->unbind(m_touchMaskMaterial->getShader()->getAttributes());
    }
}

void ieInteractiveObject::onAdded(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onAdded(event);
    m_touchRecognizer = std::static_pointer_cast<ieTouchRecognizer>(event->getObjectWithKey("touchRecognizer"));
    assert(m_camera != nullptr);
    
    assert(m_resourceAccessor != nullptr);
    ieSharedShader shader = m_resourceAccessor->getShader(ieShaderV2T2TA_vert, ieShaderV2T2TA_frag);
    m_touchMaskMaterial->setShader(shader);
    
    m_touchMaskMaterial->setBlending(true);
    m_touchMaskMaterial->setBlendingFunctionSource(GL_SRC_ALPHA);
    m_touchMaskMaterial->setBlendingFunctionDestination(GL_ONE_MINUS_SRC_ALPHA);
    m_touchMaskMaterial->setCulling(false);
    m_touchMaskMaterial->setDepthTest(false);
    m_touchMaskMaterial->setDepthMask(false);
}

void ieInteractiveObject::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onRemoved(event);
}

void ieInteractiveObject::setTouchable(bool value)
{
    m_isTouchable = value;
    if(m_touchRecognizer != nullptr && m_isTouchable)
    {
        ieDisplayObject::addEventListener(kEVENT_ON_UPDATE_TOUCH_MASK, m_functionOnUpdateTouchMask);
        m_touchRecognizer->registerInteractiveObject(std::dynamic_pointer_cast<ieInteractiveObject>(ieDisplayObject::shared_from_this()));
    } else if(m_touchRecognizer != nullptr){
        m_touchRecognizer->unregisterInteractiveObject(std::dynamic_pointer_cast<ieInteractiveObject>(ieDisplayObject::shared_from_this()));
        ieDisplayObject::removeEventListener(kEVENT_ON_UPDATE_TOUCH_MASK, m_functionOnUpdateTouchMask);
    }
}

bool ieInteractiveObject::isTouchable(void) const
{
    return m_isTouchable;
}