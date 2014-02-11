//
//  ieShader.h
//  ieCore
//
//  Created by sergey.sergeev on 2/10/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieShader__
#define __ieCore__ieShader__

#include "ieCommon.h"
#include "ieEnums.h"

class ieShaderUniform;

class ieShader
{
private:
    
protected:
    
    i32 m_uniforms[E_SHADER_UNIFORM_MAX];
    i32 m_samplers[E_SHADER_SAMPLER_MAX];
    i32 m_attributes[E_SHADER_ATTRIBUTE_MAX];
    std::array<std::shared_ptr<ieShaderUniform>, E_SHADER_UNIFORM_MAX + E_SHADER_SAMPLER_MAX> m_values;
    
    std::string m_vsSourceCode;
    std::string m_fsSourceCode;
    ui32 m_shader;
    
    ui32 link(ui32 vertexShader, ui32 fragmentShader);
    ui32 compile(const std::string &sourceCode,  GLenum shader);
    
public:
    
    ieShader(const std::string& vsSourceCode,
             const std::string& fsSourceCode);
    ~ieShader(void);
    
    std::string getVertexShaderSourceCode(void) const;
    std::string getFragmentShaderSourceCode(void) const;
    
    const i32* getAttributes(void) const;
    
    void setMatrix3x3(const glm::mat3x3& matrix, E_SHADER_UNIFORM uniform);
    void setMatrix3x3Custom(const glm::mat3x3& matrix, const std::string& uniform);
    void setMatrix4x4(const glm::mat4x4& matrix, E_SHADER_UNIFORM uniform);
    void setMatrix4x4Custom(const glm::mat4x4& matrix, const std::string& uniform);
    void setMatrixArray4x4(const glm::mat4x4* matrix, ui32 size, E_SHADER_UNIFORM uniform);
    void setMatrixArray4x4Custom(const glm::mat4x4* matrix, ui32 size, const std::string& uniform);
    void setVector2(const glm::vec2& vector, E_SHADER_UNIFORM uniform);
    void setVector2Custom(const glm::vec2& vector, const std::string& uniform);
    void setVector3(const glm::vec3& vector, E_SHADER_UNIFORM uniform);
    void setVector3Custom(const glm::vec3& vector, const std::string& uniform);
    void setVector4(const glm::vec4& vector, E_SHADER_UNIFORM uniform);
    void setVector4Custom(const glm::vec4& vector, const std::string& uniform);
    void setFloat(f32 value, E_SHADER_UNIFORM uniform);
    void setFloatCustom(f32 value, const std::string& uniform);
    void setInt(i32 value, E_SHADER_UNIFORM uniform);
    void setIntCustom(i32 value, const std::string& uniform);
    void setTexture(ui32 texture, E_SHADER_SAMPLER sampler);
    
    void bind(void) const;
    void unbind(void) const;
};

#endif
