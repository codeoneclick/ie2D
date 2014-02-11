//
//  ieShader.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/10/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieShader.h"

extern const struct ieAttributes
{
    std::string m_position;
    std::string m_texcoord;
    std::string m_color;
    
} ieAttributes;

extern const struct ieUniforms
{
    std::string m_worldMatrix;
    std::string m_viewMatrix;
    std::string m_projectionMatrix;
    std::string m_cameraPosition;
    
} ieUniforms;

extern const struct ieSamplers
{
    std::string m_sampler_01;
    std::string m_sampler_02;
    std::string m_sampler_03;
    std::string m_sampler_04;
    std::string m_sampler_05;
    std::string m_sampler_06;
    std::string m_sampler_07;
    std::string m_sampler_08;
    
} ieSamplers;

const struct ieAttributes ieAttributes =
{
    "IN_Position",
    "IN_TexCoord",
    "IN_Color"
};

const struct ieUniforms ieUniforms =
{
    "MATRIX_World",
    "MATRIX_View",
    "MATRIX_Projection",
    "VECTOR_CameraPosition"
};

const struct ieSamplers ieSamplers =
{
    "SAMPLER_01",
    "SAMPLER_02",
    "SAMPLER_03",
    "SAMPLER_04",
    "SAMPLER_05",
    "SAMPLER_06",
    "SAMPLER_07",
    "SAMPLER_08"
};

class ieShaderUniform
{
private:
    
protected:
    
    E_UNIFORM_CLASS m_class;
    
    glm::mat4x4 m_mat4x4_value;
    glm::mat3x3 m_mat3x3_value;
    glm::vec4 m_vec4_value;
    glm::vec3 m_vec3_value;
    glm::vec2 m_vec2_value;
    f32 m_f32_value;
    i32 m_i32_value;
    
    E_SHADER_SAMPLER m_sampler_value;
    ui32 m_texture_value;
    
public:
    
    ieShaderUniform(E_UNIFORM_CLASS _class);
    ~ieShaderUniform(void);
    
    E_UNIFORM_CLASS getClass(void) const;
    
    void setMatrix3x3(const glm::mat3x3& matrix);
    void setMatrix4x4(const glm::mat4x4& matrix);
    void setVector2(const glm::vec2& vector);
    void setVector3(const glm::vec3& vector);
    void setVector4(const glm::vec4& vector);
    void setFloat(f32 value);
    void setInt(i32 value);
    void setSampler(ui32 texture, E_SHADER_SAMPLER sampler);
    
    const glm::mat3x3& getMatrix3x3(void) const;
    const glm::mat4x4& getMatrix4x4(void) const;
    const glm::vec2& getVector2(void) const;
    const glm::vec3& getVector3(void) const;
    const glm::vec4& getVector4(void) const;
    const f32 getFloat(void) const;
    const i32 getInt(void) const;
    const E_SHADER_SAMPLER getSampler(void) const;
    const ui32 getTexture(void) const;
};

ieShaderUniform::ieShaderUniform(E_UNIFORM_CLASS _class) :
m_class(_class),
m_mat3x3_value(0.0f),
m_mat4x4_value(0.0f),
m_vec2_value(0.0f),
m_vec3_value(0.0f),
m_vec4_value(0.0f),
m_f32_value(0.0f),
m_sampler_value(E_SHADER_SAMPLER_01),
m_texture_value(0)
{
    
}

ieShaderUniform::~ieShaderUniform(void)
{
    
}

E_UNIFORM_CLASS ieShaderUniform::getClass(void) const
{
    return m_class;
}

void ieShaderUniform::setMatrix3x3(const glm::mat3x3& matrix)
{
    assert(m_class == E_UNIFORM_CLASS_MAT3X3);
    m_mat3x3_value = matrix;
}

void ieShaderUniform::setMatrix4x4(const glm::mat4x4& matrix)
{
    assert(m_class == E_UNIFORM_CLASS_MAT4X4);
    m_mat4x4_value = matrix;
}

void ieShaderUniform::setVector2(const glm::vec2& vector)
{
    assert(m_class == E_UNIFORM_CLASS_VECTOR2);
    m_vec2_value = vector;
}

void ieShaderUniform::setVector3(const glm::vec3& vector)
{
    assert(m_class == E_UNIFORM_CLASS_VECTOR3);
    m_vec3_value = vector;
}

void ieShaderUniform::setVector4(const glm::vec4& vector)
{
    assert(m_class == E_UNIFORM_CLASS_VECTOR4);
    m_vec4_value = vector;
}

void ieShaderUniform::setFloat(f32 value)
{
    assert(m_class == E_UNIFORM_CLASS_FLOAT);
    m_f32_value = value;
};

void ieShaderUniform::setInt(i32 value)
{
    assert(m_class = E_UNIFORM_CLASS_INT);
    m_i32_value = value;
};

void ieShaderUniform::setSampler(ui32 texture, E_SHADER_SAMPLER sampler)
{
    assert(m_class == E_UNIFORM_CLASS_SAMPLER);
    m_sampler_value = sampler;
    m_texture_value = texture;
}

const glm::mat3x3& ieShaderUniform::getMatrix3x3(void) const
{
    assert(m_class == E_UNIFORM_CLASS_MAT3X3);
    return m_mat3x3_value;
}

const glm::mat4x4& ieShaderUniform::getMatrix4x4(void) const
{
    assert(m_class == E_UNIFORM_CLASS_MAT4X4);
    return m_mat4x4_value;
}

const glm::vec2& ieShaderUniform::getVector2(void) const
{
    assert(m_class == E_UNIFORM_CLASS_VECTOR2);
    return m_vec2_value;
}

const glm::vec3& ieShaderUniform::getVector3(void) const
{
    assert(m_class == E_UNIFORM_CLASS_VECTOR3);
    return m_vec3_value;
}

const glm::vec4& ieShaderUniform::getVector4(void) const
{
    assert(m_class == E_UNIFORM_CLASS_VECTOR4);
    return m_vec4_value;
}

const f32 ieShaderUniform::getFloat(void) const
{
    assert(m_class == E_UNIFORM_CLASS_FLOAT);
    return m_f32_value;
};

const i32 ieShaderUniform::getInt(void) const
{
    assert(m_class == E_UNIFORM_CLASS_INT);
    return m_i32_value;
};

const E_SHADER_SAMPLER ieShaderUniform::getSampler(void) const
{
    assert(m_class == E_UNIFORM_CLASS_SAMPLER);
    return m_sampler_value;
};

const ui32 ieShaderUniform::getTexture(void) const
{
    assert(m_class == E_UNIFORM_CLASS_SAMPLER);
    return m_texture_value;
};

ieShader::ieShader(const std::string& vsSourceCode,
                   const std::string& fsSourceCode) :
m_vsSourceCode(vsSourceCode),
m_fsSourceCode(fsSourceCode)
{
    ui32 vertexShader = ieShader::compile(m_vsSourceCode, GL_VERTEX_SHADER);
    ui32 fragmentShader = ieShader::compile(m_fsSourceCode, GL_FRAGMENT_SHADER);
    m_shader = ieShader::link(vertexShader, fragmentShader);
    
    m_attributes[E_SHADER_ATTRIBUTE_POSITION] = -1;
    m_attributes[E_SHADER_ATTRIBUTE_TEXCOORD] = -1;
    m_attributes[E_SHADER_ATTRIBUTE_COLOR] = -1;
    
    for(ui32 i = 0; i < E_SHADER_UNIFORM_MAX + E_SHADER_SAMPLER_MAX; ++i)
    {
        m_values[i] = nullptr;
    }
    
    m_uniforms[E_SHADER_UNIFORM_MATRIX_WORLD] = glGetUniformLocation(m_shader, ieUniforms.m_worldMatrix.c_str());
    m_uniforms[E_SHADER_UNIFORM_MATRIX_VIEW] = glGetUniformLocation(m_shader, ieUniforms.m_viewMatrix.c_str());
    m_uniforms[E_SHADER_UNIFORM_MATRIX_PROJECTION] = glGetUniformLocation(m_shader, ieUniforms.m_projectionMatrix.c_str());
    m_uniforms[E_SHADER_UNIFORM_VECTOR_CAMERA_POSITION] = glGetUniformLocation(m_shader, ieUniforms.m_cameraPosition.c_str());
    
    m_samplers[E_SHADER_SAMPLER_01] = glGetUniformLocation(m_shader, ieSamplers.m_sampler_01.c_str());
    m_samplers[E_SHADER_SAMPLER_02] = glGetUniformLocation(m_shader, ieSamplers.m_sampler_02.c_str());
    m_samplers[E_SHADER_SAMPLER_03] = glGetUniformLocation(m_shader, ieSamplers.m_sampler_03.c_str());
    m_samplers[E_SHADER_SAMPLER_04] = glGetUniformLocation(m_shader, ieSamplers.m_sampler_04.c_str());
    m_samplers[E_SHADER_SAMPLER_05] = glGetUniformLocation(m_shader, ieSamplers.m_sampler_05.c_str());
    m_samplers[E_SHADER_SAMPLER_06] = glGetUniformLocation(m_shader, ieSamplers.m_sampler_06.c_str());
    m_samplers[E_SHADER_SAMPLER_07] = glGetUniformLocation(m_shader, ieSamplers.m_sampler_07.c_str());
    m_samplers[E_SHADER_SAMPLER_08] = glGetUniformLocation(m_shader, ieSamplers.m_sampler_08.c_str());
    
    m_attributes[E_SHADER_ATTRIBUTE_POSITION] = glGetAttribLocation(m_shader, ieAttributes.m_position.c_str());
    m_attributes[E_SHADER_ATTRIBUTE_TEXCOORD] = glGetAttribLocation(m_shader, ieAttributes.m_texcoord.c_str());
    m_attributes[E_SHADER_ATTRIBUTE_COLOR] = glGetAttribLocation(m_shader, ieAttributes.m_color.c_str());
    
}

ieShader::~ieShader(void)
{
    
}

std::string ieShader::getVertexShaderSourceCode(void) const
{
    return m_vsSourceCode;
}

std::string ieShader::getFragmentShaderSourceCode(void) const
{
    return m_fsSourceCode;
}

const i32* ieShader::getAttributes(void) const
{
    return m_attributes;
}

ui32 ieShader::compile(const std::string &sourceCode,  GLenum shader)
{
    ui32 handle = glCreateShader(shader);
    const char* data = sourceCode.c_str();
    glShaderSource(handle, 1, &data, 0);
    glCompileShader(handle);
    
    i32 success;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(handle, sizeof(message), 0, &message[0]);
#if defined(__NDK__)
        NDK_LOG("Error: %s", message);
#endif
        std::cout<<message<<std::endl;
#if defined(__IOS__)
        assert(false);
#endif
    }
    return handle;
}

ui32 ieShader::link(ui32 vertexShader, ui32 fragmentShader)
{
    ui32 handle = glCreateProgram();
    glAttachShader(handle, vertexShader);
    glAttachShader(handle, fragmentShader);
    glLinkProgram(handle);
    
    i32 success;
    glGetProgramiv(handle, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLchar message[256];
        glGetProgramInfoLog(handle, sizeof(message), 0, &message[0]);
#if defined(__NDK__)
        NDK_LOG("Error: %s", message);
#endif
        std::cout<<message<<std::endl;
#if defined(__IOS__)
        assert(false);
#endif
    }
    return handle;
}


void ieShader::setMatrix3x3(const glm::mat3x3 &matrix, E_SHADER_UNIFORM uniform)
{
    if(m_values[uniform] != nullptr && m_values[uniform]->getMatrix3x3() == matrix)
    {
        return;
    }
    else if(m_values[uniform] == nullptr)
    {
        m_values[uniform] = std::make_shared<ieShaderUniform>(E_UNIFORM_CLASS_MAT3X3);
    }
    glUniformMatrix3fv(m_uniforms[uniform], 1, 0, &matrix[0][0]);
    m_values[uniform]->setMatrix3x3(matrix);
}

void ieShader::setMatrix3x3Custom(const glm::mat3x3 &matrix, const std::string &uniform)
{
    glUniformMatrix3fv(glGetUniformLocation(m_shader, uniform.c_str()), 1, 0, &matrix[0][0]);
}

void ieShader::setMatrix4x4(const glm::mat4x4 &matrix, E_SHADER_UNIFORM uniform)
{
    if(m_values[uniform] != nullptr && m_values[uniform]->getMatrix4x4() == matrix)
    {
        return;
    }
    else if(m_values[uniform] == nullptr)
    {
        m_values[uniform] = std::make_shared<ieShaderUniform>(E_UNIFORM_CLASS_MAT4X4);
    }
    glUniformMatrix4fv(m_uniforms[uniform], 1, 0, &matrix[0][0]);
    m_values[uniform]->setMatrix4x4(matrix);
}

void ieShader::setMatrix4x4Custom(const glm::mat4x4 &matrix, const std::string &uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(m_shader, uniform.c_str()), 1, 0, &matrix[0][0]);
}

void ieShader::setMatrixArray4x4(const glm::mat4x4* matrix, ui32 size, E_SHADER_UNIFORM uniform)
{
    glUniformMatrix4fv(m_uniforms[uniform], size, 0, &matrix[0][0][0]);
}

void ieShader::setMatrixArray4x4Custom(const glm::mat4x4* matrix, ui32 size, const std::string& uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(m_shader, uniform.c_str()), size, 0, &matrix[0][0][0]);
}

void ieShader::setVector2(const glm::vec2 &vector, E_SHADER_UNIFORM uniform)
{
    if(m_values[uniform] != nullptr && m_values[uniform]->getVector2() == vector)
    {
        return;
    }
    else if(m_values[uniform] == nullptr)
    {
        m_values[uniform] = std::make_shared<ieShaderUniform>(E_UNIFORM_CLASS_VECTOR2);
    }
    glUniform2fv(m_uniforms[uniform], 1, &vector[0]);
    m_values[uniform]->setVector2(vector);
}

void ieShader::setVector2Custom(const glm::vec2 &vector, const std::string &uniform)
{
    glUniform2fv(glGetUniformLocation(m_shader, uniform.c_str()), 1, &vector[0]);
}

void ieShader::setVector3(const glm::vec3 &vector, E_SHADER_UNIFORM uniform)
{
    if(m_values[uniform] != nullptr && m_values[uniform]->getVector3() == vector)
    {
        return;
    }
    else if(m_values[uniform] == nullptr)
    {
        m_values[uniform] = std::make_shared<ieShaderUniform>(E_UNIFORM_CLASS_VECTOR3);
    }
    glUniform3fv(m_uniforms[uniform], 1, &vector[0]);
    m_values[uniform]->setVector3(vector);
}

void ieShader::setVector3Custom(const glm::vec3 &vector, const std::string &uniform)
{
    glUniform3fv(glGetUniformLocation(m_shader, uniform.c_str()), 1, &vector[0]);
}

void ieShader::setVector4(const glm::vec4 &vector, E_SHADER_UNIFORM uniform)
{
    if(m_values[uniform] != nullptr && m_values[uniform]->getVector4() == vector)
    {
        return;
    }
    else if(m_values[uniform] == nullptr)
    {
        m_values[uniform] = std::make_shared<ieShaderUniform>(E_UNIFORM_CLASS_VECTOR4);
    }
    glUniform4fv(m_uniforms[uniform], 1, &vector[0]);
    m_values[uniform]->setVector4(vector);
}

void ieShader::setVector4Custom(const glm::vec4 &vector, const std::string &uniform)
{
    glUniform4fv(glGetUniformLocation(m_shader, uniform.c_str()), 1, &vector[0]);
}

void ieShader::setFloat(f32 value, E_SHADER_UNIFORM uniform)
{
    if(m_values[uniform] != nullptr && m_values[uniform]->getFloat() == value)
    {
        return;
    }
    else if(m_values[uniform] == nullptr)
    {
        m_values[uniform] = std::make_shared<ieShaderUniform>(E_UNIFORM_CLASS_FLOAT);
    }
    glUniform1f(m_uniforms[uniform], value);
    m_values[uniform]->setFloat(value);
}

void ieShader::setFloatCustom(f32 value, const std::string &uniform)
{
    glUniform1f(glGetUniformLocation(m_shader, uniform.c_str()), value);
}

void ieShader::setInt(i32 value, E_SHADER_UNIFORM uniform)
{
    if(m_values[uniform] != nullptr && m_values[uniform]->getInt() == value)
    {
        return;
    }
    else if(m_values[uniform] == nullptr)
    {
        m_values[uniform] = std::make_shared<ieShaderUniform>(E_UNIFORM_CLASS_INT);
    }
    glUniform1i(m_uniforms[uniform], value);
    m_values[uniform]->setInt(value);
}

void ieShader::setIntCustom(i32 value, const std::string &uniform)
{
    glUniform1i(glGetUniformLocation(m_shader, uniform.c_str()), value);
}

void ieShader::setTexture(ui32 texture, E_SHADER_SAMPLER sampler)
{
    assert(sampler < E_SHADER_SAMPLER_MAX);
    glActiveTexture(GL_TEXTURE0 + sampler);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(m_samplers[sampler], sampler);
}

void ieShader::bind(void) const
{
    glUseProgram(m_shader);
}

void ieShader::unbind(void) const
{
    glUseProgram(0);
}


