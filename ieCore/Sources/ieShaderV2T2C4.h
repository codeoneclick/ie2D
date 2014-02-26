//
//  ieShaderTexture.h
//  ieCore
//
//  Created by Sergey Sergeev on 2/17/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef ieCore_ieShaderTexture_h
#define ieCore_ieShaderTexture_h

static const char* ieShaderV2T2C4_vert = STRING_SHADER
(
 attribute vec4 attribute_position;
 attribute vec2 attribute_texcoord;
 attribute vec4 attribute_color;
 
 varying vec2 varying_texcoord;
 varying vec4 varying_color;
 
 void main(void)
{
    varying_texcoord = attribute_texcoord / 32767.0  - 1.0;
    varying_color = attribute_color / 255.0;
    gl_Position = attribute_position;
}
);

static const char* ieShaderV2T2C4_frag = STRING_SHADER
(
 varying highp vec2 varying_texcoord;
 varying lowp vec4 varying_color;
 uniform sampler2D uniform_sampler_01;
 
 void main(void)
{
    gl_FragColor = texture2D(uniform_sampler_01, varying_texcoord) * varying_color;
}
);

#endif
