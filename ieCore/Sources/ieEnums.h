//
//  ieEnums.h
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef ieCore_ieEnums_h
#define ieCore_ieEnums_h

enum E_PLATFORM_API
{
    E_PLATFORM_API_IOS = 0,
    E_PLATFORM_API_WIN32,
    E_PLATFORM_API_OSX,
    E_PLATFORM_API_NDK
};

enum E_SHADER_ATTRIBUTE
{
    E_SHADER_ATTRIBUTE_POSITION = 0,
    E_SHADER_ATTRIBUTE_TEXCOORD,
    E_SHADER_ATTRIBUTE_COLOR,
    E_SHADER_ATTRIBUTE_MAX
};

enum E_VALUE_TYPE
{
    E_VALUE_TYPE_BOOL = 0,
    E_VALUE_TYPE_I8,
    E_VALUE_TYPE_UI8,
    E_VALUE_TYPE_I16,
    E_VALUE_TYPE_UI16,
    E_VALUE_TYPE_I32,
    E_VALUE_TYPE_UI32,
    E_VALUE_TYPE_F32
};

#endif
