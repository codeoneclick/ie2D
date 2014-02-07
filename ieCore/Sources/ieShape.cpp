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

ieShape::ieShape(void)
{
    
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