//
//  CGameViewController.m
//  indie2dEngine
//
//  Created by Sergey Sergeev on 5/17/13.
//  Copyright (c) 2013 Sergey Sergeev. All rights reserved.
//

#include "CGameViewController.h"
#include "ieGameController.h"
#include "ieIGameTransition.h"
#include "ieIOGLWindow.h"
#include "ieDisplayObject.h"
#include "ieDisplayObjectContainer.h"
#include "ieStage.h"
#include "ieImage.h"
#include "ieColor.h"
#include "ieSprite.h"

@interface CGameViewController ()

@property (weak, nonatomic) IBOutlet ieHWND *m_hwnd;
@property (unsafe_unretained, nonatomic) ieGameController* gameController;
@property (unsafe_unretained, nonatomic) std::shared_ptr<ieDisplayObjectContainer> sprite;

@end

@implementation CGameViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    CGRect screenFrame = CGRectMake(0.0f, 0.0f, [[UIScreen mainScreen] bounds].size.height, [[UIScreen mainScreen] bounds].size.width);
    
    [self.view setFrame:screenFrame];
    [self.m_hwnd setFrame:screenFrame];
    
    self.view.autoresizingMask = UIViewAutoresizingNone;
    self.m_hwnd.autoresizingMask = UIViewAutoresizingNone;
    
    self.gameController = new ieGameController();
    std::shared_ptr<ieIOGLWindow> window = std::make_shared<ieIOGLWindow>((__bridge void*)_m_hwnd);
    std::shared_ptr<ieIGameTransition> transition = std::make_shared<ieIGameTransition>("demo", window);
    self.gameController->registerTransition(transition);
    self.gameController->goToTransition("demo");
    
    std::shared_ptr<ieColor> color_01 = std::make_shared<ieColor>(255, 0, 255, 255);
    self.sprite = std::make_shared<ieDisplayObjectContainer>(glm::vec4(10, 10, 50, 50));
    transition->addChild(self.sprite);
    self.sprite->setColor(color_01);
    //self.sprite->setRotation(15);
    self.sprite->setPosition(glm::vec2(200, 200));
    
    std::shared_ptr<ieColor> color_02 = std::make_shared<ieColor>(0, 0, 255, 255);
    std::shared_ptr<ieDisplayObjectContainer> sprite2 = std::make_shared<ieDisplayObjectContainer>(glm::vec4(250, 250, 100, 100));
    self.sprite->addChild(sprite2);
    sprite2->setColor(color_02);
    sprite2->setPosition(glm::vec2(100, 100));
    
    std::string path([[[NSBundle mainBundle] resourcePath] UTF8String]);
    path.append("/");
    path.append("4.json");
    std::shared_ptr<ieSprite> sprite3 = std::make_shared<ieSprite>(glm::vec4(250, 250, 400, 400), path);
    transition->addChild(sprite3);
    sprite3->setPosition(glm::vec2(250, 250));
    
    NSMethodSignature* signature = [self methodSignatureForSelector:@selector(onTick:)];
    NSInvocation* invocation = [NSInvocation invocationWithMethodSignature:signature];
    [invocation setTarget: self];
    [invocation setSelector:@selector(onTick:)];
    
    NSTimer *sender = [NSTimer timerWithTimeInterval:0.1 invocation:invocation repeats:YES];
    NSRunLoop *runner = [NSRunLoop currentRunLoop];
    [runner addTimer:sender forMode:NSDefaultRunLoopMode];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown &&
            interfaceOrientation != UIInterfaceOrientationPortrait);
}

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration;
{
    CGSize size = CGSizeZero;
    if(UIInterfaceOrientationIsPortrait(toInterfaceOrientation))
    {
        size = CGSizeMake(MIN([UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height), MAX([UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height));
    } else {
        size = CGSizeMake(MAX([UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height), MIN([UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height));
    }
    self.gameController->onResize(size.width, size.height);
    
    [UIView animateWithDuration:0.25 animations:^{
        self.view.alpha = 0.0f;
    } completion:^(BOOL finished) {
        self.view.hidden = YES;
    }];
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation;
{
    self.view.hidden = NO;
    [UIView animateWithDuration:0.25 animations:^{
        self.view.alpha = 1.0f;
    }];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}


- (void)onTick:(NSTimer*)sender
{
    static f32 rotation = 0.0f;
    self.sprite->setRotation(rotation);
    rotation += 5.5f;
}

@end
