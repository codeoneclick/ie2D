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
#include <png.h>

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
    
    std::string path([[[NSBundle mainBundle] resourcePath] UTF8String]);
    path.append("/");
    path.append("_e01_move_18.png");
    
    png_image image;
    memset(&image, 0, sizeof image);
    image.version = PNG_IMAGE_VERSION;
    
    if (png_image_begin_read_from_file(&image, path.c_str()))
    {
        std::cout<<"loaded"<<std::endl;
    }
    else
    {
        assert(false);
    }
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
