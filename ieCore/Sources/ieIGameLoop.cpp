//
//  ieIGameLoop.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieIGameLoop.h"
#include "ieIGameTransition.h"
#include "ieEvent.h"

extern std::shared_ptr<ieIGameLoop> createGameLoop_ios(void);
extern std::shared_ptr<ieIGameLoop> createGameLoop_win32(void);
extern std::shared_ptr<ieIGameLoop> createGameLoop_osx(void);
extern std::shared_ptr<ieIGameLoop> createGameLoop_ndk(void);

std::shared_ptr<ieIGameLoop> ieIGameLoop::createGameLoop(E_PLATFORM_API api)
{
    std::shared_ptr<ieIGameLoop> gameLoop = nullptr;
    switch (api)
    {
        case E_PLATFORM_API_IOS:
        {
#if defined(__IOS__)
            gameLoop = createGameLoop_ios();
#else
            assert(false);
#endif
        }
            break;
            
        case E_PLATFORM_API_WIN32:
        {
#if defined(__WIN32__)
            gameLoop = createGameLoop_win32();
#else
            assert(false);
#endif
        }
            break;
            
        case E_PLATFORM_API_OSX:
        {
#if defined(__OSX__)
            gameLoop = createGameLoop_osx();
#else
            assert(false);
#endif
        }
            break;
        case E_PLATFORM_API_NDK:
        {
#if defined(__NDK__)
            gameLoop = createGameLoop_ndk();
#else
            assert(false);
#endif
        }
            break;
        default:
        {
            assert(false);
        }
            break;
    }
    assert(gameLoop != nullptr);
    return gameLoop;
}

ieIGameLoop::ieIGameLoop(void) :
m_currentTransition(nullptr)
{
    
}

void ieIGameLoop::setCurrentTransition(const std::shared_ptr<ieIGameTransition>& transition)
{
    assert(transition != nullptr);
    m_currentTransition = transition;
}

void ieIGameLoop::update(void)
{
    if(m_currentTransition != nullptr)
    {
        std::shared_ptr<ieEvent> eventOnUpdate = std::make_shared<ieEvent>(kEVENT_ON_UPDATE, m_currentTransition);
        m_currentTransition->dispatchEvent(eventOnUpdate);
    }
}

void ieIGameLoop::draw(void)
{
    if(m_currentTransition != nullptr)
    {
        std::shared_ptr<ieEvent> eventOnEnterFrame = std::make_shared<ieEvent>(kEVENT_ON_ENTER_FRAME, m_currentTransition);
        m_currentTransition->dispatchEvent(eventOnEnterFrame);
        std::shared_ptr<ieEvent> eventOnDraw = std::make_shared<ieEvent>(kEVENT_ON_DRAW, m_currentTransition);
        m_currentTransition->dispatchEvent(eventOnDraw);
        std::shared_ptr<ieEvent> eventOnExitFrame = std::make_shared<ieEvent>(kEVENT_ON_EXIT_FRAME, m_currentTransition);
        m_currentTransition->dispatchEvent(eventOnExitFrame);
    }
}