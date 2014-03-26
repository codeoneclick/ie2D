//
//  ieCommon.h
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef ieCore_ieCommon_h
#define ieCore_ieCommon_h

#include <map>
#include <set>
#include <queue>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <numeric>
#include <future>
#include <algorithm>
#include <mutex>
#include <thread>
#include <fstream>
#include <strstream>
#include <sstream>
#include <iostream>
#include <assert.h>
#include <functional>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/type_precision.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <png.h>
#include <json/json.h>

#if defined(__IOS__)

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <QuartzCore/QuartzCore.h>

#elif defined(__OSX__)

#include <OpenGL/OpenGL.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#elif defined(__NDK__)

#include <jni.h>
#include <android/window.h>
#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/asset_manager.h>

#include <EGL/egl.hx>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#define NDK_LOG(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

#endif

typedef signed char i8;
typedef unsigned char ui8;
typedef signed short i16;
typedef unsigned short ui16;
typedef signed int i32;
typedef unsigned int ui32;
typedef long long i64;
typedef unsigned long long ui64;
typedef float f32;


#define ieMax(a,b) (((a) > (b)) ? (a) : (b))
#define ieMin(a,b) (((a) < (b)) ? (a) : (b))

namespace ieCommon
{
    static inline std::string getFilename(const std::string& value)
    {
        std::string filename = "";
        size_t found = value.find_last_of("/\\");
        
        assert(found != std::string::npos &&
               found + 1 < value.length());
        
        if(found != std::string::npos &&
           found + 1 < value.length())
        {
            filename = value.substr(found + 1, value.length() - 1);
        }
        return filename;
    };
    
    static inline std::string getPath(const std::string& value)
    {
        std::string path = "";
        size_t found = value.find_last_of("/\\");
        
        assert(found != std::string::npos);
        
        if(found != std::string::npos)
        {
            path = value.substr(0, found);
        }
        return path;
    };
    
    static inline std::string getExtension(const std::string& value)
    {
        std::string extension = "";
        size_t found = value.find_last_of(".");
        
        assert(found != std::string::npos &&
               found + 1 < value.length());
        
        if(found != std::string::npos &&
           found + 1 < value.length())
        {
            extension = value.substr(found + 1, value.length() - 1);
        }
        return extension;

    };
};

namespace glm
{
    static inline glm::vec2 transform(const glm::vec2 &vertex, const glm::mat4& matrix)
    {
        glm::vec4 value = matrix * glm::vec4(vertex, 0.0, 1.0);
        return glm::vec2(value.x, value.y);
    }
};

#endif
