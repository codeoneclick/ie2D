//
//  ieVertexBuffer.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieVertexBuffer.h"
#include "ieEnums.h"

ieVertexBuffer::ieVertexBuffer(ui32 size, GLenum mode) :
m_size(size),
m_mode(mode)
{
    assert(size != 0);
    m_data = new ieVertex[m_size];
    glGenBuffers(1, &m_vbo);
}

ieVertexBuffer::~ieVertexBuffer(void)
{
    glDeleteBuffers(1, &m_vbo);
    delete[] m_data;
}

glm::u16vec2 ieVertexBuffer::compressVec2(const glm::vec2& uncompressed)
{
    glm::u16vec2 compressed;
    compressed.x = static_cast<ui16>((uncompressed.x + 1.0f) * 0.5f * 65535);
    compressed.y = static_cast<ui16>((uncompressed.y + 1.0f) * 0.5f * 65535);
    return compressed;
}

glm::vec2 ieVertexBuffer::uncompressU16Vec2(const glm::u16vec2& compressed)
{
    glm::vec2 uncompressed;
    uncompressed.x = static_cast<f32>(compressed.x / (65535 * 0.5f) - 1.0f);
    uncompressed.y = static_cast<f32>(compressed.y / (65535 * 0.5f) - 1.0f);
    return uncompressed;
}

const ui32 ieVertexBuffer::getSize(void) const
{
    assert(m_size != 0);
    return m_size;
}

ieVertex* ieVertexBuffer::lock(void) const
{
    assert(m_data != nullptr);
    return m_data;
}

void ieVertexBuffer::unlock(ui32 size)
{
    assert(m_data != nullptr);
    assert(m_size != 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ieVertex) * (size > 0 ? MIN(size, m_size) : m_size) , m_data, m_mode);
}

void ieVertexBuffer::bind(const i32* attributes)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    i32 attribute = attributes[E_SHADER_ATTRIBUTE_POSITION];
    if(attribute >= 0)
    {
        glEnableVertexAttribArray(attribute);
        glVertexAttribPointer(attribute, 2, GL_FLOAT, GL_FALSE, sizeof(ieVertex), (GLvoid*)offsetof(ieVertex, m_position));
    }
    attribute = attributes[E_SHADER_ATTRIBUTE_TEXCOORD];
    if(attribute >= 0)
    {
        glEnableVertexAttribArray(attribute);
        glVertexAttribPointer(attribute, 2, GL_UNSIGNED_SHORT, GL_FALSE, sizeof(ieVertex), (GLvoid*)offsetof(ieVertex, m_texcoord));
    }
    attribute = attributes[E_SHADER_ATTRIBUTE_COLOR];
    if(attribute >= 0)
    {
        glEnableVertexAttribArray(attribute);
        glVertexAttribPointer(attribute, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(ieVertex), (GLvoid*)offsetof(ieVertex, m_color));
    }
}

void ieVertexBuffer::unbind(const i32* attributes)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    i32 attribute = attributes[E_SHADER_ATTRIBUTE_POSITION];
    if(attribute >= 0)
    {
        glDisableVertexAttribArray(attribute);
    }
    attribute = attributes[E_SHADER_ATTRIBUTE_TEXCOORD];
    if(attribute >= 0)
    {
        glDisableVertexAttribArray(attribute);
    }
    attribute = attributes[E_SHADER_ATTRIBUTE_COLOR];
    if(attribute >= 0)
    {
        glDisableVertexAttribArray(attribute);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
