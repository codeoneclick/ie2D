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
 attribute vec4 attribute_position;
 attribute vec4 attribute_color;
 varying vec4 varying_color;
 
 void main(void)
{
    gl_Position = attribute_position;
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
