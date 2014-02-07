//
//  ieVertexBuffer.h
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieVertexBuffer__
#define __ieCore__ieVertexBuffer__

#include "ieCommon.h"

struct ieVertex
{
    glm::vec3    m_position;
    glm::u16vec2 m_texcoord;
    glm::u8vec4  m_color;
};

class ieVertexBuffer
{
private:
    
protected:
    
    ui32      m_size;
    ieVertex* m_data;
    ui32      m_vbo;
    GLenum    m_mode;
    
public:
    
    ieVertexBuffer(ui32 size, GLenum mode);
    ~ieVertexBuffer(void);
    
    const ui32 getSize(void) const;
    
    static glm::u16vec2 compressVec2(const glm::vec2& uncompressed);
    static glm::vec2 uncompressU16Vec2(const glm::u16vec2& compressed);
    
    ieVertex* lock(void) const;
    void unlock(ui32 size = 0);
    
    void bind(const i32* attributes);
    void unbind(const i32* attributes);
};

#endif
