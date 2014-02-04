//
//  ieBitmapData.h
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieBitmapData__
#define __ieCore__ieBitmapData__

#include "ieIBitmapDrawable.h"
#include "ieObject.h"

class ieBitmapData :
public ieIBitmapDrawable,
public ieObject
{
private:
    
protected:
    
    ui32 m_width;
    ui32 m_height;
    bool m_transparent;
    ui32 m_oglTextureId;
    ui8 *m_data;
    
public:
    
    ieBitmapData(ui32 width, ui32 height, bool transparent = true, ui32 fillColor = 0xFFFFFFFF);
    ~ieBitmapData(void);
    
    ui32 getWidth(void);
    
    ui32 getHeight(void);
    
    void applyFilter(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                     const glm::ivec4& sourceRectangle,
                     const glm::ivec2& destinationPoint,
                     std::shared_ptr<ieBitmapFilter> filter);
    
    void colorTransform(const glm::ivec4& sourceRectangle,
                        const std::shared_ptr<ieColorTransformation>& colorTransformation);
    
    void copyChannel(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                     const glm::ivec4& sourceRectangle,
                     const glm::ivec2& destinationPoint,
                     ui32 sourceChannel,
                     ui32 destinationChannel);
    
    void copyPixels(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                    const glm::ivec4& sourceRectangle,
                    const glm::ivec2& destinationPoint);
    
    void copyPixelsToByteArray(const glm::ivec4& rectangle,
                               const std::vector<ui32>& data);
    
    void fillRect(const glm::ivec4& rectangle,
                  ui32 color);
    
    void floodFill(f32 x,
                   f32 y,
                   ui32 color);
    
    glm::ivec4 generateFilterRectangle(const glm::ivec4& sourceRectangle,
                                       std::shared_ptr<ieBitmapFilter> filter);
    
    glm::ivec4 getColorBoundsRect(ui32 color,
                                  bool findColor);
    
    ui32 getPixel(ui32 x,
                  ui32 y);
    
    std::vector<ui32> getPixels(const glm::ivec4& sourceRectangle);
    
    bool hitTest(const glm::ivec4& rectangle);
    
    void merge(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
               const glm::ivec4& sourceRectangle,
               const glm::ivec2& destinationPoint,
               f32 redMultiplier,
               f32 greenMultiplier,
               f32 blueMultiplier,
               f32 alphaMultiplier);
    
    void noise(i32 randomSeed,
               ui32 low = 0,
               ui32 high = 255,
               bool grayScale = false);
    
    void perlinNoise(f32 baseX,
                     f32 baseY,
                     ui32 numOctaves,
                     i32 randomSeed,
                     bool stitch,
                     bool fractalNoise,
                     bool grayScale = false);
    
    void lock(void);
    
    void unlock(void);
    
    void setPixel(ui32 x, ui32 y, ui32 color);
    
    void setPixels(const glm::ivec4& rectangle, const std::vector<ui32>& data);
    
};

#endif
