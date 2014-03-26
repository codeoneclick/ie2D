//
//  ieOGLWindow_osx.c
//  ieCore
//
//  Created by sergey.sergeev on 3/26/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieIOGLWindow.h"

#if defined(__OSX__)

@interface IOGLWindow()

@property(nonatomic, assign) CVDisplayLinkRef m_displayLink;

@end

@implementation IOGLWindow

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

- (void) prepareOpenGL
{
	[super prepareOpenGL];
	[[self openGLContext] makeCurrentContext];
	GLint swap = 1;
	[[self openGLContext] setValues:&swap forParameter:NSOpenGLCPSwapInterval];
}

@end

#endif