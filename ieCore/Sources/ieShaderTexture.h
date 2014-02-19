//
//  ieShaderTexture.h
//  ieCore
//
//  Created by Sergey Sergeev on 2/17/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef ieCore_ieShaderTexture_h
#define ieCore_ieShaderTexture_h

static const char* shaderTextureVertex = STRING_SHADER
(
 attribute vec3 IN_Position;
 attribute vec2 IN_TexCoord;
 attribute vec4 IN_Color;
 
 varying vec2   OUT_TexCoord;
 
 uniform mat4   MATRIX_World;
 uniform mat4   MATRIX_View;
 uniform mat4   MATRIX_Projection;
 
 void main(void)
{
    OUT_TexCoord = IN_TexCoord;
    gl_Position = vec4(IN_Position, 1.0);
}
);

static const char* shaderTextureFragment = STRING_SHADER
(
 varying highp vec2 OUT_TexCoord;
 uniform sampler2D SAMPLER_01;
 
 void main(void)
{
    gl_FragColor = texture2D(SAMPLER_01, OUT_TexCoord);
}
);

#endif
