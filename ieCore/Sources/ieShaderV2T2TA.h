//
//  ieShaderV2T2TA.h
//  ieCore
//
//  Created by sergey.sergeev on 4/4/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef ieCore_ieShaderV2T2TA_h
#define ieCore_ieShaderV2T2TA_h

static const char* ieShaderV2T2TA_vert = STRING_SHADER
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

static const char* ieShaderV2T2TA_frag = STRING_SHADER
(
 
 varying highp vec2 varying_texcoord;
 varying lowp vec4 varying_color;
 
 uniform sampler2D uniform_sampler_01;
 uniform lowp vec4 uniform_touchUniqueColor;
 
 void main(void)
{
    lowp vec4 diffuse_color = texture2D(uniform_sampler_01, varying_texcoord);
    if(diffuse_color.a > 0.0)
    {
        diffuse_color.a = 1.0;
    }
    gl_FragColor = uniform_touchUniqueColor * diffuse_color.a;
}
 );


#endif
