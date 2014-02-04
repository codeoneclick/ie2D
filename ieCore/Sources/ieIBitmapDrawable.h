//
//  ieIBitmapDrawable.h
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieIBitmapDrawable__
#define __ieCore__ieIBitmapDrawable__

#include "ieCommon.h"
class ieBitmapData;
class ieBitmapFilter;
class ieColorTransformation;
class ieIBitmapDrawable
{
private:
    
protected:
    
public:
    
    ieIBitmapDrawable(void) = default;
    ~ieIBitmapDrawable(void) = default;
    
    virtual ui32 getWidth(void) = 0;
    
    virtual ui32 getHeight(void) = 0;
    
    virtual void applyFilter(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                             const glm::ivec4& sourceRectangle,
                             const glm::ivec2& destinationPoint,
                             std::shared_ptr<ieBitmapFilter> filter) = 0;
    
    virtual void colorTransform(const glm::ivec4& sourceRectangle,
                                const std::shared_ptr<ieColorTransformation>& colorTransformation) = 0;
    
    virtual void copyChannel(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                             const glm::ivec4& sourceRectangle,
                             const glm::ivec2& destinationPoint,
                             ui32 sourceChannel,
                             ui32 destinationChannel) = 0;
    
    virtual void copyPixels(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                            const glm::ivec4& sourceRectangle,
                            const glm::ivec2& destinationPoint);
    
    virtual void copyPixelsToByteArray(const glm::ivec4& rectangle,
                                       const std::vector<ui32>& data) = 0;
    
    virtual void fillRect(const glm::ivec4& rectangle,
                          ui32 color) = 0;
    
    virtual void floodFill(f32 x,
                           f32 y,
                           ui32 color) = 0;
    
    virtual glm::ivec4 generateFilterRectangle(const glm::ivec4& sourceRectangle,
                                               std::shared_ptr<ieBitmapFilter> filter) = 0;
    
    virtual glm::ivec4 getColorBoundsRect(ui32 color,
                                          bool findColor) = 0;
    
    virtual ui32 getPixel(ui32 x,
                          ui32 y) = 0;
    
    virtual std::vector<ui32> getPixels(const glm::ivec4& sourceRectangle) = 0;
    
    virtual bool hitTest(const glm::ivec4& rectangle) = 0;
    
    virtual void merge(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                       const glm::ivec4& sourceRectangle,
                       const glm::ivec2& destinationPoint,
                       f32 redMultiplier,
                       f32 greenMultiplier,
                       f32 blueMultiplier,
                       f32 alphaMultiplier) = 0;
    
    virtual void noise(i32 randomSeed,
                       ui32 low = 0,
                       ui32 high = 255,
                       bool grayScale = false) = 0;
    
    virtual void perlinNoise(f32 baseX,
                             f32 baseY,
                             ui32 numOctaves,
                             i32 randomSeed,
                             bool stitch,
                             bool fractalNoise,
                             bool grayScale = false) = 0;
    
    virtual void lock(void) = 0;
    
    virtual void unlock(void) = 0;
    
    virtual void setPixel(ui32 x, ui32 y, ui32 color) = 0;
    
    virtual void setPixels(const glm::ivec4& rectangle, const std::vector<ui32>& data) = 0;
    
};

#endif
