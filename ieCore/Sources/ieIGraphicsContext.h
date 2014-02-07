//
//  ieIGraphicsContext.h
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieIGraphicsContext__
#define __ieCore__ieIGraphicsContext__

#include "ieCommon.h"
#include "ieEnums.h"

class ieIOGLWindow;
class ieIGraphicsContext : public std::enable_shared_from_this<ieIGraphicsContext>
{
private:
    
protected:
    
    ui32 m_screenFrameBuffer;
    ui32 m_screenRenderBuffer;
	ui32 m_screenDepthBuffer;
    
    ui32 m_worldFrameBuffer;
    ui32 m_worldColorAttachment;
    ui32 m_worldDepthAttachment;
    
    std::shared_ptr<ieIOGLWindow> m_window;
    
    ieIGraphicsContext(void) = default;
    
public:
    
    virtual ~ieIGraphicsContext(void) = default;
    
    static std::shared_ptr<ieIGraphicsContext> createGraphicsContext(const std::shared_ptr<ieIOGLWindow>& window,
                                                                     E_PLATFORM_API api);
    
    const ui32 getScreenFrameBuffer(void) const;
    const ui32 getScreenRenderBuffer(void) const;
    const ui32 getScreenDepthBuffer(void) const;
    
    const ui32 getWorldFrameBuffer(void) const;
    const ui32 getWorldColorAttachment(void) const;
    const ui32 getWorldDepthAttachment(void) const;
    
    virtual void draw(void) const = 0;
};


#endif
