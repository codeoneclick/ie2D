//
//  ieIGraphicsContext.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieIGraphicsContext.h"

extern std::shared_ptr<ieIGraphicsContext> createGraphicsContext_ios(const std::shared_ptr<ieIOGLWindow>& window);
extern std::shared_ptr<ieIGraphicsContext> createGraphicsContext_win32(const std::shared_ptr<ieIOGLWindow>& window);
extern std::shared_ptr<ieIGraphicsContext> createGraphicsContext_osx(const std::shared_ptr<ieIOGLWindow>& window);
extern std::shared_ptr<ieIGraphicsContext> createGraphicsContext_ndk(const std::shared_ptr<ieIOGLWindow>& window);

std::shared_ptr<ieIGraphicsContext> ieIGraphicsContext::createGraphicsContext(const std::shared_ptr<ieIOGLWindow> &window,
                                                                              E_PLATFORM_API api)
{
    std::shared_ptr<ieIGraphicsContext> context = nullptr;
    switch (api)
    {
        case E_PLATFORM_API_IOS:
        {
#if defined(__IOS__)
            context = createGraphicsContext_ios(window);
#else
            assert(false);
#endif
        }
            break;
            
        case E_PLATFORM_API_WIN32:
        {
#if defined(__WIN32__)
            context = createGraphicsContext_win32(window);
#else
            assert(false);
#endif
        }
            break;
            
        case E_PLATFORM_API_OSX:
        {
#if defined(__OSX__)
            context = createGraphicsContext_osx(window);
#else
            assert(false);
#endif
        }
            break;
        case E_PLATFORM_API_NDK:
        {
#if defined(__NDK__)
            context = createGraphicsContext_ndk(window);
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

const ui32 ieIGraphicsContext::getFrameBuffer(void) const
{
    return m_frameBuffer;
}

const ui32 ieIGraphicsContext::getRenderBuffer(void) const
{
    return m_renderBuffer;
}

const ui32 ieIGraphicsContext::getDepthBuffer(void) const
{
    return m_depthBuffer;
}

