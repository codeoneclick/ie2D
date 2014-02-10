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
    
    i32 handle = m_uniforms[uniform];
    glUniformMatrix3fv(handle, 1, 0, &matrix[0][0]);
    m_values[uniform]->setMatrix3x3(matrix);
}

void ieShader::setMatrix3x3Custom(const glm::mat3x3 &matrix, const std::string &uniform)
{
    
    i32 handle = glGetUniformLocation(m_shader, uniform.c_str());
    glUniformMatrix3fv(handle, 1, 0, &matrix[0][0]);
    
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
    
    i32 handle = m_uniforms[uniform];
    glUniformMatrix4fv(handle, 1, 0, &matrix[0][0]);
    m_values[uniform]->setMatrix4x4(matrix);
}

void ieShader::setMatrix4x4Custom(const glm::mat4x4 &matrix, const std::string &uniform)
{
    i32 handle = glGetUniformLocation(m_shader, uniform.c_str());
    glUniformMatrix4fv(handle, 1, 0, &matrix[0][0]);
}

void ieShader::setMatrixArray4x4(const glm::mat4x4* matrix, ui32 size, E_SHADER_UNIFORM uniform)
{
        i32 handle = m_uniforms[uniform];
        glUniformMatrix4fv(handle, size, 0, &matrix[0][0][0]);
}

void ieShader::setMatrixArray4x4Custom(const glm::mat4x4* matrix, ui32 size, const std::string& uniform)
{
    i32 handle = glGetUniformLocation(m_shader, uniform.c_str());
    glUniformMatrix4fv(handle, size, 0, &matrix[0][0][0]);
}

void ieShader::setVector2(const glm::vec2 &vector, E_SHADER_UNIFORM uniform)
{
    if(m_values[uniform] != nullptr && m_values[uniform]->Get_Vector2() == vector)
    {
        return;
    }
    else if(m_values[_uniform] == nullptr)
    {
        m_values[_uniform] = std::make_shared<CShaderUniform>(E_UNIFORM_CLASS_VECTOR2);
    }
    
    i32 handle = m_uniforms[_uniform];
    glUniform2fv(handle, 1, &_vector[0]);
    m_values[_uniform]->Set_Vector2(_vector);
}

void CShader::Set_Vector2Custom(const glm::vec2 &_vector, const std::string &_uniform)
{
    if(IResource::IsLoaded() && IResource::IsCommited())
    {
        i32 handle = glGetUniformLocation(m_handle, _uniform.c_str());
        glUniform2fv(handle, 1, &_vector[0]);
    }
}

void CShader::Set_Vector3(const glm::vec3 &_vector, E_SHADER_UNIFORM _uniform)
{
    if(IResource::IsLoaded() && IResource::IsCommited())
    {
        if(m_values[_uniform] != nullptr && m_values[_uniform]->Get_Vector3() == _vector)
        {
            return;
        }
        else if(m_values[_uniform] == nullptr)
        {
            m_values[_uniform] = std::make_shared<CShaderUniform>(E_UNIFORM_CLASS_VECTOR3);
        }
        
        i32 handle = m_uniforms[_uniform];
        glUniform3fv(handle, 1, &_vector[0]);
        m_values[_uniform]->Set_Vector3(_vector);
    }
}

void CShader::Set_Vector3Custom(const glm::vec3 &_vector, const std::string &_uniform)
{
    if(IResource::IsLoaded() && IResource::IsCommited())
    {
        i32 handle = glGetUniformLocation(m_handle, _uniform.c_str());
        glUniform3fv(handle, 1, &_vector[0]);
    }
}

void CShader::Set_Vector4(const glm::vec4 &_vector, E_SHADER_UNIFORM _uniform)
{
    if(IResource::IsLoaded() && IResource::IsCommited())
    {
        if(m_values[_uniform] != nullptr && m_values[_uniform]->Get_Vector4() == _vector)
        {
            return;
        }
        else if(m_values[_uniform] == nullptr)
        {
            m_values[_uniform] = std::make_shared<CShaderUniform>(E_UNIFORM_CLASS_VECTOR4);
        }
        
        i32 handle = m_uniforms[_uniform];
        glUniform4fv(handle, 1, &_vector[0]);
        m_values[_uniform]->Set_Vector4(_vector);
    }
}

void CShader::Set_Vector4Custom(const glm::vec4 &_vector, const std::string &_uniform)
{
    if(IResource::IsLoaded() && IResource::IsCommited())
    {
        i32 handle = glGetUniformLocation(m_handle, _uniform.c_str());
        glUniform4fv(handle, 1, &_vector[0]);
    }
}

void CShader::Set_Float(f32 _value, E_SHADER_UNIFORM _uniform)
{
    if(IResource::IsLoaded() && IResource::IsCommited())
    {
        if(m_values[_uniform] != nullptr && m_values[_uniform]->Get_Float() == _value)
        {
            return;
        }
        else if(m_values[_uniform] == nullptr)
        {
            m_values[_uniform] = std::make_shared<CShaderUniform>(E_UNIFORM_CLASS_FLOAT);
        }
        
        i32 handle = m_uniforms[_uniform];
        glUniform1f(handle, _value);
        m_values[_uniform]->Set_Float(_value);
    }
}

void CShader::Set_FloatCustom(f32 _value, const std::string &_uniform)
{
    if(IResource::IsLoaded() && IResource::IsCommited())
    {
        i32 handle = glGetUniformLocation(m_handle, _uniform.c_str());
        glUniform1f(handle, _value);
    }
}

void CShader::Set_Int(i32 _value, E_SHADER_UNIFORM _uniform)
{
    if(IResource::IsLoaded() && IResource::IsCommited())
    {
        if(m_values[_uniform] != nullptr && m_values[_uniform]->Get_Int() == _value)
        {
            return;
        }
        else if(m_values[_uniform] == nullptr)
        {
            m_values[_uniform] = std::make_shared<CShaderUniform>(E_UNIFORM_CLASS_INT);
        }
        
        i32 handle = m_uniforms[_uniform];
        glUniform1i(handle, _value);
        m_values[_uniform]->Set_Int(_value);
    }
}

void CShader::Set_IntCustom(i32 _value, const std::string &_uniform)
{
    if(IResource::IsLoaded() && IResource::IsCommited())
    {
        i32 handle = glGetUniformLocation(m_handle, _uniform.c_str());
        glUniform1i(handle, _value);
    }
}

void CShader::Set_Texture(std::shared_ptr<CTexture> _texture, E_SHADER_SAMPLER _sampler)
{
    if(IResource::IsLoaded() && IResource::IsCommited())
    {
        assert(_sampler < E_SHADER_SAMPLER_MAX);
        glActiveTexture(GL_TEXTURE0 + _sampler);
        _texture->Bind();
        glUniform1i(m_samplers[_sampler], _sampler);
    }
}

void CShader::Bind(void) const
{
    if(IResource::IsLoaded() && IResource::IsCommited() && s_handle != m_handle)
    {
        s_handle = m_handle;
        glUseProgram(m_handle);
    }
}

void CShader::Unbind(void) const
{
    /*if(IResource::IsLoaded() && IResource::IsCommited())
     {
     glUseProgram(NULL);
     }*/
}


