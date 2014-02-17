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

ieIGameTransition::ieIGameTransition(const std::string& name,
                                   const std::shared_ptr<ieIOGLWindow>& window) :
m_window(window),
m_name(name)
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
    
    m_functionOnUpdate = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieIGameTransition::onUpdate, this, std::placeholders::_1));
    m_functionOnDraw = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieIGameTransition::onDraw, this, std::placeholders::_1));
    m_functionOnEnterFrame = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieIGameTransition::onEnterFrame, this, std::placeholders::_1));
    m_functionOnExitFrame = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieIGameTransition::onExitFrame, this, std::placeholders::_1));
    
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

void ieIGameTransition::onRegistered(const std::shared_ptr<ieEvent>& event)
{
    ieIGameTransition::addEventListener(kEVENT_ON_TRANSITION_ENTER, m_functionOnTransitionEnter);
    ieIGameTransition::addEventListener(kEVENT_ON_TRANSITION_EXIT, m_functionOnTransitionExit);
    
    ieIGameTransition::addEventListener(kEVENT_ON_UPDATE, m_functionOnUpdate);
    ieIGameTransition::addEventListener(kEVENT_ON_DRAW, m_functionOnDraw);
    ieIGameTransition::addEventListener(kEVENT_ON_ENTER_FRAME, m_functionOnEnterFrame);
    ieIGameTransition::addEventListener(kEVENT_ON_EXIT_FRAME, m_functionOnExitFrame);
}

void ieIGameTransition::onUnregistered(const std::shared_ptr<ieEvent>& event)
{
    ieIGameTransition::removeEventListener(kEVENT_ON_TRANSITION_ENTER, m_functionOnTransitionEnter);
    ieIGameTransition::removeEventListener(kEVENT_ON_TRANSITION_EXIT, m_functionOnTransitionExit);
    
    ieIGameTransition::removeEventListener(kEVENT_ON_UPDATE, m_functionOnUpdate);
    ieIGameTransition::removeEventListener(kEVENT_ON_DRAW, m_functionOnDraw);
    ieIGameTransition::removeEventListener(kEVENT_ON_ENTER_FRAME, m_functionOnEnterFrame);
    ieIGameTransition::removeEventListener(kEVENT_ON_EXIT_FRAME, m_functionOnExitFrame);
}

void ieIGameTransition::onEnter(const std::shared_ptr<ieEvent>& event)
{
    std::shared_ptr<ieStage> stage = std::static_pointer_cast<ieStage>(shared_from_this());
    std::shared_ptr<ieEvent> eventOnStageAdded = std::make_shared<ieEvent>(kEVENT_ON_ADDED, stage);
    assert(m_window != nullptr);
    ieValue width(m_window->getWidth());
    eventOnStageAdded->addValueWithKey(width, "width");
    ieValue height(m_window->getHeight());
    eventOnStageAdded->addValueWithKey(height, "height");
    ieIGameTransition::dispatchEvent(eventOnStageAdded);
}

void ieIGameTransition::onExit(const std::shared_ptr<ieEvent>& event)
{
    std::shared_ptr<ieStage> stage = std::static_pointer_cast<ieStage>(shared_from_this());
    std::shared_ptr<ieEvent> eventOnStageRemoved = std::make_shared<ieEvent>(kEVENT_ON_REMOVED, stage);
    ieIGameTransition::dispatchEvent(eventOnStageRemoved);
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