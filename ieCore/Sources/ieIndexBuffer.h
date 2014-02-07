//
//  ieIndexBuffer.h
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieIndexBuffer__
#define __ieCore__ieIndexBuffer__

#include "ieCommon.h"

class ieIndexBuffer
{
private:
    
protected:
    
    ui32   m_ibo;
	ui16*  m_data;
    ui32   m_size;
    GLenum m_mode;
    
public:
    
    ieIndexBuffer(ui32 size, GLenum mode);
    ~ieIndexBuffer(void);
    
    const ui32 getSize(void) const;
    
    ui16* lock(void) const;
    void unlock(ui32 size = 0);
    
    void bind(void) const;
    void unbind(void) const;
};

#endif
