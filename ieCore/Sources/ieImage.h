//
//  ieImage.h
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieImage__
#define __ieCore__ieImage__

#include "ieCommon.h"

class ieImage
{
private:
    
protected:
    
    png_byte* m_data;
    ui32 m_format;
    ui32 m_width;
    ui32 m_height;
    
public:
    
    ieImage(const std::string& filename);
    ~ieImage(void);
    
    const png_byte* getData(void) const;
    const ui32 getWidth(void) const;
    const ui32 getHeight(void) const;
    const ui32 getFormat(void) const;
    
};

#endif
