//
//  ieTexture.cpp
//  ieCore
//
//  Created by Sergey Sergeev on 2/16/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieTexture.h"
#include "ieImage.h"

#define TO_RGB(r,g,b) (unsigned short)(((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3))

ieTexture::ieTexture(const std::string& filename) :
ieResource(E_RESOURCE_TYPE_TEXTURE),
m_texture(0),
m_width(0),
m_height(0)
{
    std::shared_ptr<ieImage> image = std::make_shared<ieImage>(filename);
    m_width = image->getWidth();
    m_height = image->getHeight();
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexImage2D(GL_TEXTURE_2D, 0, image->getFormat(), m_width, m_height, 0,
                 image->getFormat(), GL_UNSIGNED_BYTE, (GLvoid*)&image->getData()[0]);
}

ieTexture::ieTexture(ui32 texture, ui32 width, ui32 height) :
ieResource(E_RESOURCE_TYPE_TEXTURE),
m_texture(texture),
m_width(width),
m_height(height)
{
    
}

ieTexture::~ieTexture(void)
{
    
}

const ui32 ieTexture::getTexture(void) const
{
    return m_texture;
}

const ui32 ieTexture::getWidth(void) const
{
    return m_width;
}

const ui32 ieTexture::getHeight(void) const
{
    return m_height;
}