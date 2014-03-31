//
//  ieStage.h
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieStage__
#define __ieCore__ieStage__

#include "ieDisplayObjectContainer.h"

class ieStage : public ieDisplayObjectContainer
{
private:
    
    ieEventDispatcherFunctionShared m_functionOnResize;
    
protected:
    
    ui32 m_frameBuffer;
    ui32 m_colorAttachment;
    ui32 m_depthAttachment;
    
    ui32 m_offscreenFrameBuffer;
    ui32 m_offscreenColorAttachment;
    ui32 m_offscreenDepthAttachment;
    
    void createFBO(ui32 width, ui32 height);
    
    virtual void onResize(const std::shared_ptr<ieEvent>& event);
    
    virtual void onUpdate(const std::shared_ptr<ieEvent>& event);
    virtual void onDraw(const std::shared_ptr<ieEvent>& event);
    virtual void onEnterFrame(const std::shared_ptr<ieEvent>& event);
    virtual void onExitFrame(const std::shared_ptr<ieEvent>& event);
    
    virtual void onAdded(const std::shared_ptr<ieEvent>& event);
    virtual void onRemoved(const std::shared_ptr<ieEvent>& event);
    
public:
    
    ieStage(const glm::vec4& frame);
    virtual ~ieStage(void);
    
    void drawOffscreenStart(ui32 width, ui32 height);
    void drawOffscreenEnd(void);
};

#endif
