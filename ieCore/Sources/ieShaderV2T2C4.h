//
//  ieShaderTexture.h
//  ieCore
//
//  Created by Sergey Sergeev on 2/17/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef ieCore_ieShaderV2T2C4_h
#define ieCore_ieShaderV2T2C4_h

static const char* ieShaderV2T2C4_vert = STRING_SHADER
(
 attribute vec2 attribute_position;
 attribute vec2 attribute_texcoord;
 attribute vec4 attribute_color;
 
 varying vec2 varying_texcoord;
 varying vec4 varying_color;
 
 uniform mat4 uniform_projection;
 uniform mat4 uniform_modelview;
 
 void main(void)
{
    varying_texcoord = attribute_texcoord / 32767.0  - 1.0;
    varying_color = attribute_color / 255.0;
    gl_Position = uniform_projection * uniform_modelview * vec4(attribute_position, 0.0, 1.0);
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
    /*if (color.a > 0.1)
    {
        gl_FragColor = color;
    } else {
        discard;
    }*/
}
);

#endif
