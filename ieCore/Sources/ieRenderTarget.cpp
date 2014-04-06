//
//  ieRenderTarget.cpp
//  ieCore
//
//  Created by sergey.sergeev on 4/4/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieRenderTarget.h"
#include "ieStage.h"

#if defined(__IOS__)

#include <UIKit/UIKit.h>
#include <QuartzCore/QuartzCore.h>

#endif

ieRenderTarget::ieRenderTarget(const std::shared_ptr<ieStage>& stage, const glm::ivec2& size) :
m_stage(stage),
m_size(size)
{
    glGenTextures(1, &m_colorAttachment);
    glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 m_size.x,
                 m_size.y,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    
    glGenRenderbuffers(1, &m_depthAttachment);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthAttachment);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES,
                          m_size.x,
                          m_size.y);
    
    glGenFramebuffers(1, &m_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthAttachment);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthAttachment);
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
}

ieRenderTarget::~ieRenderTarget(void)
{
    if(m_frameBuffer != 0)
    {
        glDeleteFramebuffers(1, &m_frameBuffer);
    }
    if(m_colorAttachment != 0)
    {
        glDeleteTextures(1, &m_colorAttachment);
    }
    if(m_depthAttachment != 0)
    {
        glDeleteRenderbuffers(1, &m_depthAttachment);
    }
}

void ieRenderTarget::clear(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT |
            GL_STENCIL_BUFFER_BIT);
}
void ieRenderTarget::begin(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glViewport(0, 0, m_size.x, m_size.y);
}

void ieRenderTarget::end(void)
{
    assert(m_stage != nullptr);
    glBindFramebuffer(GL_FRAMEBUFFER, m_stage->getFrameBuffer());
    glViewport(0, 0, m_size.x, m_size.y);
}

void ieRenderTarget::saveToFile(const std::string& imageFilename)
{
    ieRenderTarget::begin();
    
    ui32 rawdataSize = static_cast<ui32>(m_size.x) * static_cast<ui32>(m_size.y) * 4;
    ui8 *rawdata = new ui8[rawdataSize];
    glReadPixels(0, 0, m_size.x, m_size.y, GL_RGBA, GL_UNSIGNED_BYTE, rawdata);
    
    ieRenderTarget::end();
    
#if defined(__IOS__)
    
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, rawdata, rawdataSize, NULL);
    
    ui32 bitsPerComponent = 8;
    ui32 bitsPerPixel = 32;
    ui32 bytesPerRow = 4 * m_size.x;
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGImageAlphaPremultipliedLast;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    CGImageRef imageRef = CGImageCreate(m_size.x,
                                        m_size.y,
                                        bitsPerComponent,
                                        bitsPerPixel,
                                        bytesPerRow,
                                        colorSpaceRef,
                                        bitmapInfo,
                                        provider, NULL, NO, renderingIntent);
    UIImage *image = [UIImage imageWithCGImage:imageRef];
    
    UIImageView *imageView = [[UIImageView alloc] initWithImage:image];
    UIGraphicsBeginImageContext(CGSizeMake(m_size.x, m_size.y));
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGAffineTransform flip = CGAffineTransformMake(1, 0, 0, -1, 0, m_size.y);
    CGContextConcatCTM(context, flip);
    [imageView.layer renderInContext:context];
    image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *imageFilePath = [[paths objectAtIndex:0] stringByAppendingPathComponent:
                               [NSString stringWithCString:imageFilename.c_str()
                                                  encoding:[NSString defaultCStringEncoding]]];
    [UIImagePNGRepresentation(image) writeToFile:imageFilePath atomically:YES];
    
#endif
    delete[] rawdata;
}
