//
//  ieIOGLWindow.h
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieIOGLWindow__
#define __ieCore__ieIOGLWindow__

#include "ieCommon.h"

#if defined(__IOS__)

#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>
#include <QuartzCore/QuartzCore.h>

@interface ieHWND : UIView

@property (nonatomic, assign) UIInterfaceOrientation orientation;

@end

#elif defined(__OSX__)

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

@interface ieHWND : NSOpenGLView

@end

#endif

class ieIOGLWindow
{
private:
    
protected:
    
#if defined(__IOS__) || defined(__OSX__)

    void* m_hwnd;
    
#elif defined(__NDK__)
    
#elif defined(__WIN32__)
    
    HWND m_hwnd;
	HDC	m_hdc;
    
#endif
    
public:
    
    ieIOGLWindow(void* hwnd);
    virtual ~ieIOGLWindow(void);
    
    virtual ui32 getWidth(void);
    virtual ui32 getHeight(void);

#if defined(__WIN32__)
    
    HWND getHWND(void) const;
    HDC getHDC(void) const;
    
#elif defined(__NDK__)
    
#elif defined(__IOS__) || defined(__OSX__)
    
    const void* getHWND(void) const;
    
#endif
    
};

#endif
