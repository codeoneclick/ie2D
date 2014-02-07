//
//  ieIndexBuffer.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieIndexBuffer.h"


ieIndexBuffer::ieIndexBuffer(ui32 size, GLenum mode) :
m_size(size),
m_mode(mode)
{
	assert(m_size != 0);
	m_data = new ui16[m_size];
    glGenBuffers(1, &m_ibo);
}

ieIndexBuffer::~ieIndexBuffer(void)
{
    glDeleteBuffers(1, &m_ibo);
    delete[] m_data;
}

const ui32 ieIndexBuffer::getSize(void) const
{
    return m_size;
}

ui16* ieIndexBuffer::lock(void) const
{
    assert(m_data != nullptr);
    return m_data;
}

void ieIndexBuffer::unlock(ui32 size)
{
    assert(m_data != nullptr);
    assert(m_size != 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ui16) * (size > 0 ? MIN(size, m_size) : m_size), m_data, m_mode);
}

void ieIndexBuffer::bind(void) const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
}

void ieIndexBuffer::unbind(void) const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}