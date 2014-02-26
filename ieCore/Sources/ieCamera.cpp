//
//  ieCamera.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/26/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieCamera.h"

ieCamera::ieCamera(ui32 screenWidth, ui32 screenHeight)
{
    m_description = "ieCamera";
    m_projection = glm::ortho(0.0f,
                              static_cast<f32>(screenWidth),
                              static_cast<f32>(screenHeight),
                              0.0f, -1.0f, 1.0f);
}

ieCamera::~ieCamera(void)
{
    
}

glm::mat4x4 ieCamera::getProjection(void) const
{
    return m_projection;
}