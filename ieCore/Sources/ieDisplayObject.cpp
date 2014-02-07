//
//  ieDisplayObject.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieDisplayObject.h"

ieDisplayObject::ieDisplayObject(void)
{
    
}

ieDisplayObject::~ieDisplayObject(void)
{
    
}

void ieDisplayObject::applyFilter(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                 const glm::ivec4& sourceRectangle,
                 const glm::ivec2& destinationPoint,
                 std::shared_ptr<ieBitmapFilter> filter)
{
    
}

void ieDisplayObject::colorTransform(const glm::ivec4& sourceRectangle,
                    const std::shared_ptr<ieColorTransformation>& colorTransformation)
{
    
}

void ieDisplayObject::copyChannel(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                 const glm::ivec4& sourceRectangle,
                 const glm::ivec2& destinationPoint,
                 ui32 sourceChannel,
                 ui32 destinationChannel)
{
    
}

void ieDisplayObject::copyPixels(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                const glm::ivec4& sourceRectangle,
                const glm::ivec2& destinationPoint)
{
    
}

void ieDisplayObject::copyPixelsToByteArray(const glm::ivec4& rectangle,
                           const std::vector<ui32>& data)
{
    
}

void ieDisplayObject::fillRect(const glm::ivec4& rectangle,
              ui32 color)
{
    
}

void ieDisplayObject::floodFill(f32 x,
               f32 y,
               ui32 color)
{
    
}

glm::ivec4 ieDisplayObject::generateFilterRectangle(const glm::ivec4& sourceRectangle,
                                   std::shared_ptr<ieBitmapFilter> filter)
{
    return glm::ivec4(0.0f, 0.0f, 0.0f, 0.0f);
}

glm::ivec4 ieDisplayObject::getColorBoundsRect(ui32 color,
                              bool findColor)
{
    return glm::ivec4(0.0f, 0.0f, 0.0f, 0.0f);
}

ui32 ieDisplayObject::getPixel(ui32 x,
              ui32 y)
{
    return 0;
}

std::vector<ui32> ieDisplayObject::getPixels(const glm::ivec4& sourceRectangle)
{
    return std::vector<ui32>();
}

bool ieDisplayObject::hitTest(const glm::ivec4& rectangle)
{
    return false;
}

void ieDisplayObject::merge(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
           const glm::ivec4& sourceRectangle,
           const glm::ivec2& destinationPoint,
           f32 redMultiplier,
           f32 greenMultiplier,
           f32 blueMultiplier,
           f32 alphaMultiplier)
{
    
}

void ieDisplayObject::noise(i32 randomSeed,
           ui32 low,
           ui32 high,
           bool grayScale)
{
    
}

void ieDisplayObject::perlinNoise(f32 baseX,
                 f32 baseY,
                 ui32 numOctaves,
                 i32 randomSeed,
                 bool stitch,
                 bool fractalNoise,
                 bool grayScale)
{
    
}

void ieDisplayObject::lock(void)
{
    
}

void ieDisplayObject::unlock(void)
{
    
}

void ieDisplayObject::setPixel(ui32 x, ui32 y, ui32 color)
{
    
}

void ieDisplayObject::setPixels(const glm::ivec4& rectangle, const std::vector<ui32>& data)
{
    
}
