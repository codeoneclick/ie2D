//
//  ieInputContext_ios.c
//  ieCore
//
//  Created by sergey.sergeev on 4/4/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieIInputContext.h"
#include "ieIOGLWindow.h"

#if defined(__IOS__)

#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>

@interface ieIInputView : UIView

@property(nonatomic, unsafe_unretained) ieIInputContext* m_context;

@end

@implementation ieIInputView

- (void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
    assert(self.m_context != nullptr);
    for (UITouch* touch in touches)
    {
        CGPoint point = [touch locationInView:self];
        self.m_context->tapRecognizerPressed(glm::ivec2(point.x, point.y));
    }
}

- (void)touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
    assert(self.m_context != nullptr);
    for (UITouch* touch in touches)
    {
        CGPoint point = [touch locationInView:self];
        self.m_context->tapRecognizerMoved(glm::ivec2(point.x, point.y));
    }
}

- (void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
    assert(self.m_context != nullptr);
    for (UITouch* touch in touches)
    {
        CGPoint point = [touch locationInView:self];
        self.m_context->tapRecognizerReleased(glm::ivec2(point.x, point.y));
    }
}

- (void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event
{
    assert(self.m_context != nullptr);
    for (UITouch* touch in touches)
    {
        CGPoint point = [touch locationInView:self];
        self.m_context->tapRecognizerReleased(glm::ivec2(point.x, point.y));
    }
}

@end

class ieIInputContext_ios : public ieIInputContext
{
private:
    
protected:
    
public:
    
    ieIInputContext_ios(const std::shared_ptr<ieIOGLWindow>& window);
    ~ieIInputContext_ios(void);
};

std::shared_ptr<ieIInputContext> createInputContext_ios(const std::shared_ptr<ieIOGLWindow>& window)
{
    return std::make_shared<ieIInputContext_ios>(window);
};

ieIInputContext_ios::ieIInputContext_ios(const std::shared_ptr<ieIOGLWindow>& window)
{
    UIView* view = (__bridge UIView*)window->getHWND();
    
    ieIInputView* inputView = [[ieIInputView alloc] init];
    inputView.m_context = this;
    inputView.frame = CGRectMake(0.0f,
                                 0.0f,
                                 view.frame.size.width,
                                 view.frame.size.height);
    [view addSubview:inputView];
}

ieIInputContext_ios::~ieIInputContext_ios(void)
{
    
}

#endif