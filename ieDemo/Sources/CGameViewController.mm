//
//  CGameViewController.m
//  indie2dEngine
//
//  Created by Sergey Sergeev on 5/17/13.
//  Copyright (c) 2013 Sergey Sergeev. All rights reserved.
//

#include "CGameViewController.h"
#include "ieIGameWorkflow.h"
#include "ieIGameTransition.h"
#include "ieIOGLWindow.h"
#include "ieDisplayObject.h"
#include "ieDisplayObjectContainer.h"
#include "ieStage.h"
#include "ieImage.h"

@interface CGameViewController ()

@property (weak, nonatomic) IBOutlet ieHWND *m_hwnd;

@end

@implementation CGameViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self.view setFrame:CGRectMake(0.0f, 0.0f, [[UIScreen mainScreen] bounds].size.height, [[UIScreen mainScreen] bounds].size.width)];
    
    ieIGameWorkflow* workflow = new ieIGameWorkflow();
    
    std::shared_ptr<ieIOGLWindow> window = std::make_shared<ieIOGLWindow>((__bridge void*)_m_hwnd);
    std::shared_ptr<ieIGameTransition> transition = std::make_shared<ieIGameTransition>("demo", window);
    workflow->registerTransition(transition);
    workflow->goToTransition("demo");
    
    std::shared_ptr<ieDisplayObjectContainer> sprite = std::make_shared<ieDisplayObjectContainer>(glm::vec4(0, 0, 100, 100));
    transition->addChild(sprite);
    
    std::string path([[[NSBundle mainBundle] resourcePath] UTF8String]);
    path.append("/");
    path.append("_e01_move_18.png");
    
    ieImage *image = new ieImage(path);
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown && interfaceOrientation != UIInterfaceOrientationPortrait);
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

@end
