//
//  ieIInputContext.cpp
//  ieCore
//
//  Created by sergey.sergeev on 4/4/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieIInputContext.h"
#include "ieIOGLWindow.h"
#include "ieTouchRecognizer.h"

extern std::shared_ptr<ieIInputContext> createInputContext_ios(const std::shared_ptr<ieIOGLWindow>& window);
extern std::shared_ptr<ieIInputContext> createInputContext_win32(const std::shared_ptr<ieIOGLWindow>& window);
extern std::shared_ptr<ieIInputContext> createInputContext_osx(const std::shared_ptr<ieIOGLWindow>& window);
extern std::shared_ptr<ieIInputContext> createInputContext_ndk(const std::shared_ptr<ieIOGLWindow>& window);

std::shared_ptr<ieIInputContext> ieIInputContext::createInputContext(const std::shared_ptr<ieIOGLWindow>& window,
                                                                     E_PLATFORM_API api)
{
    std::shared_ptr<ieIInputContext> context = nullptr;
    switch (api)
    {
        case E_PLATFORM_API_IOS:
        {
#if defined(__IOS__)
            context = createInputContext_ios(window);
#else
            assert(false);
#endif
        }
            break;
            
        case E_PLATFORM_API_WIN32:
        {
#if defined(__WIN32__)
            context = createInputContext_win32(window);
#else
            assert(false);
#endif
        }
            break;
            
        case E_PLATFORM_API_OSX:
        {
#if defined(__OSX__)
            context = createInputContext_osx(window);
#else
            assert(false);
#endif
        }
            break;
        case E_PLATFORM_API_NDK:
        {
#if defined(__NDK__)
            context = createInputContext_ndk(window);
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
    assert(context != nullptr);
    return context;
}

ieIInputContext::ieIInputContext(void) :
m_touchRecognizer(std::make_shared<ieTouchRecognizer>())
{
    
}

ieIInputContext::~ieIInputContext(void)
{
    
}

void ieIInputContext::tapRecognizerPressed(const glm::ivec2& _point)
{
    assert(m_touchRecognizer != nullptr);
}

void ieIInputContext::tapRecognizerMoved(const glm::ivec2& _point)
{
     assert(m_touchRecognizer != nullptr);
}

void ieIInputContext::tapRecognizerReleased(const glm::ivec2& _point)
{
     assert(m_touchRecognizer != nullptr);
}

std::shared_ptr<ieTouchRecognizer> ieIInputContext::getTouchRecognizer(void)
{
    return m_touchRecognizer;
}