//
//  ieTexture.h
//  ieCore
//
//  Created by Sergey Sergeev on 2/16/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieTexture__
#define __ieCore__ieTexture__

#include "ieResource.h"

class ieImage;
class ieTexture : public ieResource
{
private:
    
protected:
    
    ui32 m_texture;
    ui32 m_width;
    ui32 m_height;
    std::shared_ptr<ieImage> m_image;
    
public:
    
    ieTexture(const std::string& filename);
    ieTexture(ui32 texture, ui32 width, ui32 height);
    ~ieTexture(void);
    
    const ui32 getTexture(void) const;
    const ui32 getWidth(void) const;
    const ui32 getHeight(void) const;
    std::shared_ptr<ieImage> getImage(void) const;
};

#endif
