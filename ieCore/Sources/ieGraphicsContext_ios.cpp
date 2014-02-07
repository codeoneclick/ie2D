//
//  ieGraphicsContext_ios.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieIGraphicsContext.h"
#include "ieIOGLWindow.h"

#if defined(__IOS__)

#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>
#include <QuartzCore/QuartzCore.h>

class ieGraphicsContext_ios : public ieIGraphicsContext
{
private:
    
protected:
    
    EAGLContext* m_context;
    
public:
    
    ieGraphicsContext_ios(const std::shared_ptr<ieIOGLWindow>& window);
    ~ieGraphicsContext_ios(void);
    
    void draw(void) const;
};

std::shared_ptr<ieIGraphicsContext> createGraphicsContext_ios(const std::shared_ptr<ieIOGLWindow>& window)
{
    return std::make_shared<ieGraphicsContext_ios>(window);
};

ieGraphicsContext_ios::ieGraphicsContext_ios(const std::shared_ptr<ieIOGLWindow>& window)
{
    m_window = window;
    
    const UIView* hwnd = (__bridge UIView*)m_window->getHWND();
    assert([hwnd.layer isKindOfClass:[CAEAGLLayer class]]);
    
    m_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    assert(m_context != nullptr);
    
    ui8 result = [EAGLContext setCurrentContext:m_context];
    assert(result == true);
    
    glGenRenderbuffers(1, &m_screenRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_screenRenderBuffer);
    [m_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:static_cast<CAEAGLLayer*>(hwnd.layer)];
    
    glGenFramebuffers(1, &m_screenFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_screenFrameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_screenRenderBuffer);
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
}

ieGraphicsContext_ios::~ieGraphicsContext_ios(void)
{
    
}

void ieGraphicsContext_ios::draw(void) const
{
    assert(m_context != nullptr);
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
}

#endif