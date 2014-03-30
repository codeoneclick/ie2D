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
#include "ieMovieClip.h"
#include "ieTile.h"
#include "ieTileset.h"

@interface CGameViewController ()

@property (weak, nonatomic) IBOutlet ieHWND *m_hwnd;
@property (unsafe_unretained, nonatomic) ieGameController* gameController;
@property (unsafe_unretained, nonatomic) std::shared_ptr<ieSprite> sprite;
@property (unsafe_unretained, nonatomic) std::shared_ptr<ieSprite> sprite2;
@property (unsafe_unretained, nonatomic) std::shared_ptr<ieMovieClip> sprite3;
@property (unsafe_unretained, nonatomic) std::shared_ptr<ieMovieClip> sprite4;
@property (unsafe_unretained, nonatomic) std::shared_ptr<ieTile> tile;

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
    
    std::shared_ptr<ieColor> color_01 = std::make_shared<ieColor>(255, 255, 0, 255);
    self.sprite = std::make_shared<ieSprite>(glm::vec4(10, 10, 50, 50), color_01);
    self.sprite->setPivot(glm::vec2(25, 25));
    transition->addChild(self.sprite);
    self.sprite->setPosition(glm::vec2(200, 200));
    
    std::shared_ptr<ieColor> color_02 = std::make_shared<ieColor>(0, 0, 255, 255);
    self.sprite2 = std::make_shared<ieSprite>(glm::vec4(250, 250, 100, 100), color_02);
    self.sprite2->setPivot(glm::vec2(50, 50));
    self.sprite->addChild(self.sprite2);
    self.sprite2->setPosition(glm::vec2(100, 100));
    
    std::string path([[[NSBundle mainBundle] resourcePath] UTF8String]);
    path.append("/");
    path.append("animation_02.json");
    self.sprite3 = std::make_shared<ieMovieClip>(glm::vec4(250, 250, 100, 100), path);
    transition->addChild(self.sprite3);
    self.sprite3->setPosition(glm::vec2(250, 250));
    self.sprite3->setScale(glm::vec2(0.5f, 0.5f));
    self.sprite3->setBatched(false);
    
    path = [[[NSBundle mainBundle] resourcePath] UTF8String];
    path.append("/");
    path.append("dragon.json");
    self.sprite4 = std::make_shared<ieMovieClip>(glm::vec4(0, 0, 50, 50), path);
    transition->addChild(self.sprite4);
    self.sprite4->setPosition(glm::vec2(350, 150));
    self.sprite4->setBatched(true);
    
    path = [[[NSBundle mainBundle] resourcePath] UTF8String];
    path.append("/");
    path.append("leather_armor.png");
    std::shared_ptr<ieTileset> tileset = std::make_shared<ieTileset>(path, glm::ivec2(128, 128));
    ui32 indexX = 0;
    ui32 indexY = 0;
    for(ui32 i = 0; i < tileset->getTilesCount(); ++i)
    {
        std::shared_ptr<ieTile> tile = tileset->getTileAtIndex(i);
        transition->addChild(tile);
        tile->setPosition(glm::vec2(indexX * 128, indexY * 128 + 128));
        indexX++;
        indexY = indexX >= 6 ? indexY + 1 : indexY;
        indexX = indexX >= 6 ? 0 : indexX;
    }
    
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
    static f32 scale = 0.5f;
    static f32 inc = 0.1f;
    self.sprite->setRotation(rotation);
    self.sprite->setScale(glm::vec2(scale, scale));
    self.sprite2->setScale(glm::vec2(scale, scale));
    self.sprite2->setRotation(rotation);
    scale += inc;
    if(scale > 2.0f || scale < 0.5f)
    {
        inc *= -1.0f;
    }
    rotation += 5.5f;
    
    static ui32 index = 0;
    self.sprite4->gotoAndStop(index);
    self.sprite3->gotoAndStop(index);
    index++;
    if(index >= 8)
    {
        index = 0;
    }
}

@end
