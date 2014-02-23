//
//  ieShape.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieShape.h"
#include "ieVertexBuffer.h"
#include "ieIndexBuffer.h"

ieShape::ieShape(const glm::vec4& frame)
{
    m_vertexBuffer = std::make_shared<ieVertexBuffer>(4, GL_STATIC_DRAW);
    ieVertex* vertexData = m_vertexBuffer->lock();
    vertexData[0].m_position = glm::vec3(frame.x, frame.y, 0.0f);
    vertexData[0].m_texcoord = ieVertexBuffer::compressVec2(glm::vec2(0.0f, 0.0f));
    vertexData[1].m_position = glm::vec3(frame.x, frame.w, 0.0f);
    vertexData[1].m_texcoord = ieVertexBuffer::compressVec2(glm::vec2(0.0f, 1.0f));
    vertexData[2].m_position = glm::vec3(frame.z, frame.y, 0.0f);
    vertexData[2].m_texcoord = ieVertexBuffer::compressVec2(glm::vec2(1.0f, 0.0f));
    vertexData[3].m_position = glm::vec3(frame.z, frame.w, 0.0f);
    vertexData[3].m_texcoord = ieVertexBuffer::compressVec2(glm::vec2(1.0f, 1.0f));
    m_vertexBuffer->unlock();
    
    m_indexBuffer = std::make_shared<ieIndexBuffer>(6, GL_STATIC_DRAW);
    ui16* indexData = m_indexBuffer->lock();
    indexData[0] = 0;
    indexData[1] = 1;
    indexData[2] = 2;
    indexData[3] = 1;
    indexData[4] = 2;
    indexData[5] = 3;
    m_indexBuffer->unlock();
}

ieShape::~ieShape(void)
{
    
}

std::shared_ptr<ieVertexBuffer> ieShape::getVertexBuffer(void) const
{
    return m_vertexBuffer;
}

std::shared_ptr<ieIndexBuffer> ieShape::getIndexBuffer(void) const
{
    return m_indexBuffer;
}

const ui32 ieShape::getNumVertexes(void) const
{
    return m_vertexBuffer->getSize();
}

const ui32 ieShape::getNumIndexes(void) const
{
    return m_indexBuffer->getSize();
}

void ieShape::bind(const i32* attributes)
{
    assert(m_vertexBuffer != nullptr);
    assert(m_indexBuffer != nullptr);
    m_vertexBuffer->bind(attributes);
    m_indexBuffer->bind();
}

void ieShape::draw(void)
{
    assert(m_vertexBuffer != nullptr);
    assert(m_indexBuffer != nullptr);
    glDrawElements(GL_TRIANGLES, m_indexBuffer->getSize(), GL_UNSIGNED_SHORT, 0);
}

void ieShape::unbind(const i32* attributes)
{
    assert(m_vertexBuffer != nullptr);
    assert(m_indexBuffer != nullptr);
    m_vertexBuffer->unbind(attributes);
    m_indexBuffer->unbind();
}