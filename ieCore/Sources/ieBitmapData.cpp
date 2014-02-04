//
//  ieBitmapData.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieBitmapData.h"
#include "ieColor.h"

ieBitmapData::ieBitmapData(ui32 width, ui32 height, bool transparent, ui32 fillColor) :
m_width(width),
m_height(height),
m_transparent(transparent)
{
    m_description = "ieBitmapData";
    glGenTextures(1, &m_oglTextureId);
    glBindTexture(GL_TEXTURE_2D, m_oglTextureId);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    m_data = new ui8[m_width * m_height * m_transparent == true ? 4 : 3];
    ui32 dataOffset = 0;
    ieColor color(fillColor);
    for(ui32 i = 0; i < m_width * m_height; ++i)
    {
        m_data[dataOffset++] = color.getRedChannel();
        m_data[dataOffset++] = color.getGreenChannel();
        m_data[dataOffset++] = color.getBlueChannel();
        if(m_transparent)
        {
            m_data[dataOffset++] = color.getAlphaChannel();
        }
    }
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 m_transparent == true ? GL_RGBA : GL_RGB,
                 m_width,
                 m_height,
                 0,
                 m_transparent == true ? GL_RGBA : GL_RGB,
                 GL_UNSIGNED_BYTE,
                 m_data);
}

ieBitmapData::~ieBitmapData(void)
{
    
}