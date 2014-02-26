//
//  ieCamera.h
//  ieCore
//
//  Created by sergey.sergeev on 2/26/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieCamera__
#define __ieCore__ieCamera__

#include "ieObject.h"

class ieCamera : public ieObject
{
private:
    
protected:
    
    glm::mat4x4 m_projection;
    
public:
    
    ieCamera(ui32 screenWidth, ui32 screenHeight);
    ~ieCamera(void);
    
    glm::mat4x4 getProjection(void) const;
};

#endif
