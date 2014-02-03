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
class ieIBitmapDrawable
{
private:
    
protected:
    
    f32 m_width;
    f32 m_height;
    
public:
    
    ieIBitmapDrawable(void) = default;
    ~ieIBitmapDrawable(void) = default;
    
    virtual void copyChannel(const std::shared_ptr<ieBitmapData>& sourceBitmapData,
                             const glm::ivec4& sourceRectangle,
                             const glm::ivec2& destinationPoint,
                             ui32 sourceChannel,
                             ui32 destinationChannel) = 0;
    
    virtual void copyPixels(const std::shared_ptr<ieBitmapData>& sourceBitmapData,
                            const glm::ivec4& sourceRectangle,
                            const glm::ivec2& destinationPoint);
    virtual void copyPixelsToByteArray(const glm::ivec4& rectangle,
                                       const std::vector<ui8>& data) = 0;
    virtual void fillRect(const glm::ivec4& rectangle,
                          ui32 color);
    virtual void floodFill(f32 x, f32 y, ui32 color);
    //virtual glm::ivec4 generateFilterRectangle(
};

#endif
