//
//  ieStage.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieStage.h"
#include "ieEvent.h"

ieStage::ieStage(void)
{
    m_functionOnUpdate = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieStage::onUpdate, this, std::placeholders::_1));
    m_functionOnDraw = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieStage::onDraw, this, std::placeholders::_1));
    m_functionOnEnterFrame = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieStage::onEnterFrame, this, std::placeholders::_1));
    m_functionOnExitFrame = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieStage::onExitFrame, this, std::placeholders::_1));
    m_functionOnAdded = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieStage::onAdded, this, std::placeholders::_1));
    m_functionOnRemoved = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieStage::onRemoved, this, std::placeholders::_1));;
    
    ieStage::addEventListener(kEVENT_ON_ADDED, m_functionOnAdded);
    ieStage::addEventListener(kEVENT_ON_REMOVED, m_functionOnRemoved);
}

ieStage::~ieStage(void)
{
    ieStage::removeEventListener(kEVENT_ON_ADDED, m_functionOnAdded);
    ieStage::removeEventListener(kEVENT_ON_REMOVED, m_functionOnRemoved);
}

void ieStage::onResize(const std::shared_ptr<ieEvent>& event)
{
    
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
    ieDisplayObjectContainer::onEnterFrame(event);
}

void ieStage::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onExitFrame(event);
}

void ieStage::onAdded(const std::shared_ptr<ieEvent>& event)
{
    glGenTextures(1, &m_colorAttachment);
    glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 event->getValueWithKey("width").getValue<ui32>(),
                 event->getValueWithKey("height").getValue<ui32>(),
                 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    
    glGenTextures(1, &m_depthAttachment);
    glBindTexture(GL_TEXTURE_2D, m_depthAttachment);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
#if defined(__NDK__)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 event->getValueWithKey("width").getValue<ui32>(),
                 event->getValueWithKey("height").getValue<ui32>(),
                 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
#else
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 event->getValueWithKey("width").getValue<ui32>(),
                 event->getValueWithKey("height").getValue<ui32>(),
                 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);
#endif
    
    glGenFramebuffers(1, &m_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0);
    
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    
    ieStage::addEventListener(kEVENT_ON_UPDATE, m_functionOnUpdate);
    ieStage::addEventListener(kEVENT_ON_DRAW, m_functionOnDraw);
    ieStage::addEventListener(kEVENT_ON_ENTER_FRAME, m_functionOnEnterFrame);
    ieStage::addEventListener(kEVENT_ON_EXIT_FRAME, m_functionOnExitFrame);
    
    ieDisplayObjectContainer::onAdded(event);
}

void ieStage::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieStage::removeEventListener(kEVENT_ON_UPDATE, m_functionOnUpdate);
    ieStage::removeEventListener(kEVENT_ON_DRAW, m_functionOnDraw);
    ieStage::removeEventListener(kEVENT_ON_ENTER_FRAME, m_functionOnEnterFrame);
    ieStage::removeEventListener(kEVENT_ON_EXIT_FRAME, m_functionOnExitFrame);
    
    ieDisplayObjectContainer::onRemoved(event);
}


