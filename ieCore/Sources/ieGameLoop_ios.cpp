//
//  ieGameLoop_ios.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieIGameLoop.h"

#if defined(__IOS__)

#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>

class ieGameLoop_ios : public ieIGameLoop
{
private:
    
protected:
    
public:
    
    ieGameLoop_ios(void);
    ~ieGameLoop_ios(void);
};

std::shared_ptr<ieIGameLoop> createGameLoop_ios(void)
{
    return std::make_shared<ieGameLoop_ios>();
};

@interface ieGameLoopExecutor_ios : NSObject

@property(nonatomic, unsafe_unretained) ieGameLoop_ios* m_gameLoop;

+ (ieGameLoopExecutor_ios *)sharedInstance;

@end

ieGameLoop_ios::ieGameLoop_ios(void)
{
    [ieGameLoopExecutor_ios sharedInstance].m_gameLoop = this;
}

ieGameLoop_ios::~ieGameLoop_ios(void)
{
    [ieGameLoopExecutor_ios sharedInstance].m_gameLoop = nullptr;
}

@implementation ieGameLoopExecutor_ios

+ (ieGameLoopExecutor_ios *)sharedInstance
{
    static ieGameLoopExecutor_ios *instance = nil;
    static dispatch_once_t once;
    dispatch_once(&once, ^{
        instance = [[self alloc] init];
    });
    return instance;
}

- (id)init
{
    self = [super init];
    if(self)
    {
        CADisplayLink* displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(onUpdate:)];
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    }
    return self;
}

- (void)onUpdate:(CADisplayLink*)sender
{
    if(_m_gameLoop != nullptr)
    {
        _m_gameLoop->update();
        _m_gameLoop->draw();
    }
}

@end

#endif
