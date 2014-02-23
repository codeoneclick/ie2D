//
//  ieShaderColor.h
//  ieCore
//
//  Created by sergey.sergeev on 2/19/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef ieCore_ieShaderColor_h
#define ieCore_ieShaderColor_h

static const char* shaderColorVertex = STRING_SHADER
(
 attribute vec3 IN_Position;
 attribute vec2 IN_TexCoord;
 attribute vec4 IN_Color;
 
 uniform mat4   MATRIX_World;
 uniform mat4   MATRIX_View;
 uniform mat4   MATRIX_Projection;
 
 void main(void)
{
    gl_Position = vec4(IN_Position, 1.0);
}
 );

static const char* shaderColorFragment = STRING_SHADER
(
 uniform lowp vec4 VECTOR_COLOR;
 
 void main(void)
{
    gl_FragColor = vec4(0.0, 1.0, 1.0, 1.0);//VECTOR_COLOR;
}
 );

#endif
