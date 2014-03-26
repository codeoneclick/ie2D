//
//  ieGameController.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieGameController.h"
#include "ieIGameTransition.h"
#include "ieIGameLoop.h"
#include "ieEvent.h"

ieGameController::ieGameController(void) :
m_currentTransition(nullptr)
{
#if defined (__IOS__)
    m_gameLoop = ieIGameLoop::createGameLoop(E_PLATFORM_API_IOS);
#elif defined(__WIN32__)
    m_gameLoop = ieIGameLoop::createGameLoop(E_PLATFORM_API_WIN32);
#elif defined(__OSX__)
    m_gameLoop = ieIGameLoop::createGameLoop(E_PLATFORM_API_OSX);
#elif defined(__NDK__)
    m_gameLoop = ieIGameLoop::createGameLoop(E_PLATFORM_API_NDK);
#endif
}

ieGameController::~ieGameController(void)
{
    m_transitions.clear();
}

void ieGameController::registerTransition(const std::shared_ptr<ieIGameTransition>& transition)
{
    assert(m_transitions.find(transition->getName()) == m_transitions.end());
    m_transitions.insert(std::make_pair(transition->getName(), transition));
    std::shared_ptr<ieEvent> eventOnTransitionRegister = std::make_shared<ieEvent>(kEVENT_ON_TRANSITION_REGISTER, transition);
    transition->dispatchEvent(eventOnTransitionRegister);
}

void ieGameController::unregisterTransition(const std::shared_ptr<ieIGameTransition>& transition)
{
    assert(m_transitions.find(transition->getName()) != m_transitions.end());
    m_transitions.erase(m_transitions.find(transition->getName()));
    std::shared_ptr<ieEvent> eventOnTransitionUnregister = std::make_shared<ieEvent>(kEVENT_ON_TRANSITION_UNREGISTER, transition);
    transition->dispatchEvent(eventOnTransitionUnregister);
}

void ieGameController::goToTransition(const std::string& name)
{
    std::cout<<"ieGameController::goToTransition"<<std::endl;
    assert(m_transitions.find(name) != m_transitions.end());
    if(m_currentTransition != nullptr)
    {
        std::shared_ptr<ieEvent> eventOnTransitionExit = std::make_shared<ieEvent>(kEVENT_ON_TRANSITION_EXIT, m_currentTransition);
        m_currentTransition->dispatchEvent(eventOnTransitionExit);
    }
    m_currentTransition = m_transitions.find(name)->second;
    m_gameLoop->setCurrentTransition(m_currentTransition);
    std::shared_ptr<ieEvent> eventOnTransitionEnter = std::make_shared<ieEvent>(kEVENT_ON_TRANSITION_ENTER, m_currentTransition);
    m_currentTransition->dispatchEvent(eventOnTransitionEnter);
}

void ieGameController::onResize(ui32 width, ui32 height)
{
    std::shared_ptr<ieEvent> eventOnResize = std::make_shared<ieEvent>(kEVENT_ON_RESIZE, m_currentTransition);
    eventOnResize->addValueWithKey(width, "width");
    eventOnResize->addValueWithKey(height, "height");
    m_currentTransition->dispatchEvent(eventOnResize);
}


