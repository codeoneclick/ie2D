//
//  ieShaderColor.h
//  ieCore
//
//  Created by sergey.sergeev on 2/19/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef ieCore_ieShaderColor_h
#define ieCore_ieShaderColor_h

static const char* ieShaderV2C4_vert = STRING_SHADER
(
 attribute vec2 attribute_position;
 attribute vec4 attribute_color;
 
 uniform mat4 uniform_projection;
 uniform mat4 uniform_modelview;
 
 varying vec4 varying_color;
 
void main(void)
{
    gl_Position = uniform_projection * uniform_modelview * vec4(attribute_position, 0.0, 1.0);
    varying_color = attribute_color / 255.0;
}
);


static const char* ieShaderV2C4_frag = STRING_SHADER
(
 varying lowp vec4 varying_color;
 
void main(void)
{
    gl_FragColor = varying_color;
}
);

#endif
