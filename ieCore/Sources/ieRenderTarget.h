//
//  ieRenderTarget.h
//  ieCore
//
//  Created by sergey.sergeev on 4/4/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieRenderTarget__
#define __ieCore__ieRenderTarget__

#include "ieCommon.h"

class ieStage;

class ieRenderTarget
{
private:
    
protected:
    
    ui32 m_frameBuffer;
    ui32 m_colorAttachment;
    ui32 m_depthAttachment;
    
    glm::ivec2 m_size;
    std::shared_ptr<ieStage> m_stage;
    
public:
    
    ieRenderTarget(const std::shared_ptr<ieStage>& stage, const glm::ivec2& size);
    ~ieRenderTarget(void);
    
    void clear(void);
    void begin(void);
    void end(void);
    
    void saveToFile(const std::string& imageFilename);
};

#endif
