//
//  ieColor.h
//  ieCore
//
//  Created by Sergey Sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieColor__
#define __ieCore__ieColor__

#include "ieColorTransformation.h"

class ieColor : public ieColorTransformation
{
private:
    
protected:
    union ieUColor
    {
        struct
        {
            ui8 m_redChannel;
            ui8 m_greenChannel;
            ui8 m_blueChannel;
            ui8 m_alphaChannel;
        };
        ui32 m_hexColor;
    } m_color;
    
    void updateRedChannel(void);
    void updateGreenChannel(void);
    void updateBlueChannel(void);
    void updateAlphaChannel(void);
    
public:
    
    ieColor(ui8 redChannel, ui8 greenChannel, ui8 blueChannel, ui8 alphaChannel = 0);
    ieColor(ui32 hexColor);
    ~ieColor(void);
    
    ui8 getRedChannel(void);
    ui8 getGreenChannel(void);
    ui8 getBlueChannel(void);
    ui8 getAlphaChannel(void);
    
    ui32 getHexColor(void);
    
    void setRedChannel(ui8 redChannel);
    void setGreenChannel(ui8 greenChannel);
    void setBlueChannel(ui8 blueChannel);
    void setAplhaChannel(ui8 alphaChannel);
    
    void setHexColor(ui32 hexColor);
    
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
