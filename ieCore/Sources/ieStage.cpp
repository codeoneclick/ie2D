//
//  ieStage.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieStage.h"
#include "ieEvent.h"

ieStage::ieStage(const glm::vec4& frame) :
ieDisplayObjectContainer(frame)
{

}

ieStage::~ieStage(void)
{

}

void ieStage::onResize(const std::shared_ptr<ieEvent>& event)
{
    
}

void ieStage::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onUpdate(event);
}

void ieStage::onDraw(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onDraw(event);
}

void ieStage::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glViewport(0, 0, m_frame.z, m_frame.w);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    ieDisplayObjectContainer::onEnterFrame(event);
}

void ieStage::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
#if defined(__IOS__)
    
    const GLenum discards[] = { GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT };
    glDiscardFramebufferEXT(GL_FRAMEBUFFER, 2, discards);
    
#elif defined(__WIN32__)
    
#endif
    
    ieDisplayObjectContainer::onExitFrame(event);
}

void ieStage::onAdded(const std::shared_ptr<ieEvent>& event)
{
    glGenTextures(1, &m_colorAttachment);
    glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 m_frame.z,
                 m_frame.w,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    
    glGenTextures(1, &m_depthAttachment);
    glBindTexture(GL_TEXTURE_2D, m_depthAttachment);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
#if defined(__NDK__)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 m_frame.z,
                 m_frame.w,
                 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
#else
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 m_frame.z,
                 m_frame.w,
                 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);
#endif
    
    glGenFramebuffers(1, &m_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0);
    
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_DITHER);
    glDepthFunc(GL_LEQUAL);
    
    ieDisplayObjectContainer::onAdded(event);
    std::cout<<"ieStage::onAdded"<<std::endl;
}

void ieStage::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onRemoved(event);
}


