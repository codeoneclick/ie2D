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
    glDeleteTextures(1, &m_oglTextureId);
    
}

void ieBitmapData::applyFilter(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                               const glm::ivec4& sourceRectangle,
                               const glm::ivec2& destinationPoint,
                               std::shared_ptr<ieBitmapFilter> filter)
{
    
}

void ieBitmapData::colorTransform(const glm::ivec4& sourceRectangle,
                                  const std::shared_ptr<ieColorTransformation>& colorTransformation)
{
    
}

void ieBitmapData::copyChannel(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                               const glm::ivec4& sourceRectangle,
                               const glm::ivec2& destinationPoint,
                               ui32 sourceChannel,
                               ui32 destinationChannel)
{
    
}

void ieBitmapData::copyPixels(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                              const glm::ivec4& sourceRectangle,
                              const glm::ivec2& destinationPoint)
{
    
}

void ieBitmapData::copyPixelsToByteArray(const glm::ivec4& rectangle,
                                         const std::vector<ui32>& data)
{
    
}

void ieBitmapData::fillRect(const glm::ivec4& rectangle,
                            ui32 color)
{
    
}

void ieBitmapData::floodFill(f32 x,
                             f32 y,
                             ui32 color)
{
    
}

glm::ivec4 ieBitmapData::generateFilterRectangle(const glm::ivec4& sourceRectangle,
                                                 std::shared_ptr<ieBitmapFilter> filter)
{
    return glm::ivec4(0.0f, 0.0f, 0.0f, 0.0f);
}

glm::ivec4 ieBitmapData::getColorBoundsRect(ui32 color,
                                            bool findColor)
{
    return glm::ivec4(0.0f, 0.0f, 0.0f, 0.0f);
}

ui32 ieBitmapData::getPixel(ui32 x,
                            ui32 y)
{
    return 0;
}

std::vector<ui32> ieBitmapData::getPixels(const glm::ivec4& sourceRectangle)
{
    return std::vector<ui32>();
}

bool ieBitmapData::hitTest(const glm::ivec4& rectangle)
{
    return false;
}

void ieBitmapData::merge(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                         const glm::ivec4& sourceRectangle,
                         const glm::ivec2& destinationPoint,
                         f32 redMultiplier,
                         f32 greenMultiplier,
                         f32 blueMultiplier,
                         f32 alphaMultiplier)
{
    
}

void ieBitmapData::noise(i32 randomSeed,
                         ui32 low,
                         ui32 high,
                         bool grayScale)
{
    
}

void ieBitmapData::perlinNoise(f32 baseX,
                               f32 baseY,
                               ui32 numOctaves,
                               i32 randomSeed,
                               bool stitch,
                               bool fractalNoise,
                               bool grayScale)
{
    
}

void ieBitmapData::lock(void)
{
    
}

void ieBitmapData::unlock(void)
{
    
}

void ieBitmapData::setPixel(ui32 x, ui32 y, ui32 color)
{
    
}

void ieBitmapData::setPixels(const glm::ivec4& rectangle, const std::vector<ui32>& data)
{
    
}
