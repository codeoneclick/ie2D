//
//  ieOGLWindow_ios.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieIOGLWindow.h"

#if defined(__IOS__)

@implementation ieHWND

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame;
{
    if (self = [super initWithFrame:frame])
    {
        super.layer.opaque = YES;
    }
    return self;
}

@end

ieIOGLWindow::ieIOGLWindow(void* hwnd) :
m_hwnd(hwnd)
{
    assert(m_hwnd != nullptr);
}

ieIOGLWindow::~ieIOGLWindow(void)
{
    
}

const void* ieIOGLWindow::getHWND(void) const
{
    return m_hwnd;
}

ui32 ieIOGLWindow::getWidth(void)
{
    assert(m_hwnd != nullptr);
    const UIView* hwnd = (__bridge UIView*)m_hwnd;
    return static_cast<ui32>(hwnd.frame.size.width);
}

ui32 ieIOGLWindow::getHeight(void)
{
    assert(m_hwnd != nullptr);
    const UIView* hwnd = (__bridge UIView*)m_hwnd;
    return static_cast<ui32>(hwnd.frame.size.width);
}

#endif