//
//  ieGameLoop_osx.c
//  ieCore
//
//  Created by Sergey Sergeev on 3/26/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//
#include "ieIGameLoop.h"

#if defined(__OSX__)

#include <Cocoa/Cocoa.h>

class ieGameLoop_osx : public ieIGameLoop
{
private:
    
protected:
    
public:
    
    ieGameLoop_osx(void);
    ~ieGameLoop_osx(void);
};

std::shared_ptr<ieIGameLoop> createGameLoop_osx(void)
{
    return std::make_shared<ieGameLoop_osx>();
};

@interface ieGameLoopExecutor_osx : NSObject

@property(nonatomic, unsafe_unretained) ieGameLoop_osx* m_gameLoop;
@property(nonatomic, strong) NSTimer* m_runTimer;

+ (ieGameLoopExecutor_osx *)sharedInstance;

@end

ieGameLoop_osx::ieGameLoop_osx(void)
{
    [ieGameLoopExecutor_osx sharedInstance].m_gameLoop = this;
}

ieGameLoop_osx::~ieGameLoop_osx(void)
{
    [ieGameLoopExecutor_osx sharedInstance].m_gameLoop = nullptr;
}

@implementation ieGameLoopExecutor_osx

+ (ieGameLoopExecutor_osx *)sharedInstance
{
    static ieGameLoopExecutor_osx *instance = nil;
    static dispatch_once_t once;
    dispatch_once(&once, ^{
        instance = [[ieGameLoopExecutor_osx alloc] init];
    });
    return instance;
}

- (id)init
{
    self = [super init];
    if(self)
    {
        [NSTimer scheduledTimerWithTimeInterval:(1.0 / 60.0f) target:self selector:@selector(onUpdate) userInfo:nil repeats:YES];
    }
    return self;
}

- (void)onUpdate
{
    if(_m_gameLoop != nullptr)
    {
        _m_gameLoop->update();
        _m_gameLoop->draw();
    }
}

@end

#endif
