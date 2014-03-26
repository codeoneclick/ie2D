//
//  ieOGLWindow_osx.c
//  ieCore
//
//  Created by sergey.sergeev on 3/26/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieIOGLWindow.h"

#if defined(__OSX__)

@interface ieHWND()

@property(nonatomic, assign) CVDisplayLinkRef m_displayLink;

@end

@implementation ieHWND

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        NSOpenGLPixelFormatAttribute attributes[] =
        {
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFADepthSize, 24,
            NULL
        };
        
        NSOpenGLPixelFormat *pixelformat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
        NSOpenGLContext* context = [[NSOpenGLContext alloc] initWithFormat:pixelformat shareContext:nil];
        [self setPixelFormat:pixelformat];
        [self setOpenGLContext:context];
    }
    return self;
}

- (void)prepareOpenGL
{
	[super prepareOpenGL];
	[[self openGLContext] makeCurrentContext];
	GLint swap = 1;
	[[self openGLContext] setValues:&swap forParameter:NSOpenGLCPSwapInterval];
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
    const NSView *hwnd = (__bridge NSView*)m_hwnd;
    return static_cast<ui32>(hwnd.frame.size.width);
}

ui32 ieIOGLWindow::getHeight(void)
{
    assert(m_hwnd != nullptr);
    const NSView* hwnd = (__bridge NSView*)m_hwnd;
    return static_cast<ui32>(hwnd.frame.size.height);
}

#endif