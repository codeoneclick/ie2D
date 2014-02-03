//
//  ieColorTransformation.h
//  ieCore
//
//  Created by Sergey Sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieColorTransformation__
#define __ieCore__ieColorTransformation__

#include "ieObject.h"

class ieColorTransformation : public ieObject
{
private:
    
protected:
    
    f32 m_redMultiplier;
    i16 m_redOffset;
    f32 m_greenMultiplier;
    i16 m_greenOffset;
    f32 m_blueMultiplier;
    i16 m_blueOffset;
    f32 m_alphaMultiplier;
    i16 m_alphaOffset;
    
public:
    
    ieColorTransformation(f32 redMultiplier = 1.0f,
                          i16 redOffset = 0,
                          f32 greenMultiplier = 1.0f,
                          i16 greenOffset = 0,
                          f32 blueMultiplier = 1.0f,
                          i16 blueOffset = 0,
                          f32 alphaMultiplier = 1.0f,
                          i16 alphaOffset = 0);
    
    ~ieColorTransformation(void);
    
    f32 getRedMultiplier(void);
    i16 getRedOffset(void);
    f32 getGreenMultiplier(void);
    i16 getGreenOffset(void);
    f32 getBlueMultiplier(void);
    i16 getBlueOffset(void);
    f32 getAlphaMultiplier(void);
    i16 getAlphaOffset(void);
    
    void setRedMultiplier(f32 redMultiplier);
    void setRedOffset(i16 redOffset);
    void setGreenMultiplier(f32 greenMultiplier);
    void setGreenOffset(i16 greenOffset);
    void setBlueMultiplier(f32 blueMultiplier);
    void setBlueOffset(i16 blueOffset);
    void setAlphaMultiplier(f32 alphaMultiplier);
    void setAlphaOffset(i16 alphaOffset);
};

#endif
