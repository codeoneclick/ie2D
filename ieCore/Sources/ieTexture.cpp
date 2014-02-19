//
//  ieTexture.cpp
//  ieCore
//
//  Created by Sergey Sergeev on 2/16/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieTexture.h"

ieTexture::ieTexture(const std::string& filename) :
ieResource(E_RESOURCE_TYPE_TEXTURE),
m_texture(0),
m_width(0),
m_height(0)
{
    
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