//
//  ieMaterial.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/10/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieMaterial.h"
#include "ieShader.h"

class ieMaterialCachedParameters
{
private:
    
    friend class ieMaterial;
    
protected:
    
    bool m_isCulling;
    GLenum m_cullingMode;
    
    bool m_isBlending;
    GLenum m_blendingFunctionSource;
    GLenum m_blendingFunctionDestination;
    
    bool m_isDepthTest;
    bool m_isDepthMask;
    
    std::shared_ptr<ieShader> m_shader;
    std::array<ui32, E_SHADER_SAMPLER_MAX> m_textures;
    
public:
    
    ieMaterialCachedParameters(void);
    ~ieMaterialCachedParameters(void);
};

ieMaterialCachedParameters::ieMaterialCachedParameters(void) :
m_shader(nullptr)
{
    std::for_each(m_textures.begin(), m_textures.end(), [](ui32& iterator){
        iterator = 0;
    });
}

ieMaterialCachedParameters::~ieMaterialCachedParameters(void)
{
}

std::shared_ptr<ieMaterialCachedParameters> ieMaterial::m_cachedParameters = nullptr;

std::shared_ptr<ieMaterialCachedParameters> ieMaterial::getCachedParameters(void)
{
    if(m_cachedParameters == nullptr)
    {
        m_cachedParameters = std::make_shared<ieMaterialCachedParameters>();
        m_cachedParameters->m_isDepthTest = true;
        m_cachedParameters->m_isDepthMask = true;
        m_cachedParameters->m_isCulling = false;
        m_cachedParameters->m_isBlending = false;
    }
    return m_cachedParameters;
}

ieMaterial::ieMaterial(void)
{
    m_parameters = std::make_shared<ieMaterialCachedParameters>();
}

ieMaterial::~ieMaterial(void)
{
    
}

bool ieMaterial::isCulling(void) const
{
    assert(m_parameters != nullptr);
    return m_parameters->m_isCulling;
}

GLenum ieMaterial::getCullingMode(void) const
{
    assert(m_parameters != nullptr);
    return m_parameters->m_cullingMode;
}

bool ieMaterial::isBlending(void) const
{
    assert(m_parameters != nullptr);
    return m_parameters->m_isBlending;
}

GLenum ieMaterial::getBlendingFunctionSource(void) const
{
    assert(m_parameters != nullptr);
    return m_parameters->m_blendingFunctionSource;
}

GLenum ieMaterial::getBlendingFunctionDestination(void) const
{
    assert(m_parameters != nullptr);
    return m_parameters->m_blendingFunctionDestination;
}

bool ieMaterial::isDepthTest(void) const
{
    assert(m_parameters != nullptr);
    return m_parameters->m_isDepthTest;
}

bool ieMaterial::isDepthMask(void) const
{
    assert(m_parameters != nullptr);
    return m_parameters->m_isDepthMask;
}

void ieMaterial::setCulling(bool value)
{
    assert(m_parameters != nullptr);
    m_parameters->m_isCulling = value;
}

void ieMaterial::setCullingMode(GLenum value)
{
    assert(m_parameters != nullptr);
    m_parameters->m_cullingMode = value;
}

void ieMaterial::setBlending(bool value)
{
    assert(m_parameters != nullptr);
    m_parameters->m_isBlending = value;
}

void ieMaterial::setBlendingFunctionSource(GLenum value)
{
    assert(m_parameters != nullptr);
    m_parameters->m_blendingFunctionSource = value;
}

void ieMaterial::setBlendingFunctionDestination(GLenum value)
{
    assert(m_parameters != nullptr);
    m_parameters->m_blendingFunctionDestination = value;
}

void ieMaterial::setDepthTest(bool value)
{
    assert(m_parameters != nullptr);
    m_parameters->m_isDepthTest = value;
}

void ieMaterial::setDepthMask(bool value)
{
    assert(m_parameters != nullptr);
    m_parameters->m_isDepthMask = value;
}

void ieMaterial::setShader(const std::shared_ptr<ieShader>& shader)
{
    assert(m_parameters != nullptr);
    m_parameters->m_shader = shader;
}

void ieMaterial::setTexture(ui32 texture,
                            E_SHADER_SAMPLER sampler)
{
    assert(m_parameters != nullptr);
    m_parameters->m_textures.at(sampler) = texture;
}

void ieMaterial::bind(void)
{
    assert(m_parameters != nullptr);
    assert(m_parameters->m_shader != nullptr);
    m_parameters->m_shader->bind();
    
    for(ui32 i = 0; i < E_SHADER_SAMPLER_MAX; ++i)
    {
        m_parameters->m_shader->setTexture(m_parameters->m_textures[i], static_cast<E_SHADER_SAMPLER>(i));
    }
    
    if(m_parameters->m_isDepthTest &&
       getCachedParameters()->m_isDepthTest != m_parameters->m_isDepthTest)
    {
        glEnable(GL_DEPTH_TEST);
        getCachedParameters()->m_isDepthTest = m_parameters->m_isDepthTest;
    }
    else if(getCachedParameters()->m_isDepthTest != m_parameters->m_isDepthTest)
    {
        glDisable(GL_DEPTH_TEST);
        getCachedParameters()->m_isDepthTest = m_parameters->m_isDepthTest;
    }
    
    if(m_parameters->m_isDepthMask &&
       getCachedParameters()->m_isDepthMask != m_parameters->m_isDepthMask)
    {
        glDepthMask(GL_TRUE);
        getCachedParameters()->m_isDepthMask = m_parameters->m_isDepthMask;
    }
    else if(getCachedParameters()->m_isDepthMask != m_parameters->m_isDepthMask)
    {
        glDepthMask(GL_FALSE);
        getCachedParameters()->m_isDepthMask = m_parameters->m_isDepthMask;
    }
    
    if(m_parameters->m_isCulling &&
       getCachedParameters()->m_isCulling != m_parameters->m_isCulling)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(m_parameters->m_cullingMode);
        getCachedParameters()->m_isCulling = m_parameters->m_isCulling;
    }
    else if(getCachedParameters()->m_isCulling != m_parameters->m_isCulling)
    {
        glDisable(GL_CULL_FACE);
        getCachedParameters()->m_isCulling = m_parameters->m_isCulling;
    }
    
    if(m_parameters->m_isBlending &&
       getCachedParameters()->m_isBlending != m_parameters->m_isBlending)
    {
        glEnable(GL_BLEND);
        glBlendFunc(m_parameters->m_blendingFunctionSource, m_parameters->m_blendingFunctionDestination);
        getCachedParameters()->m_isBlending = m_parameters->m_isBlending;
    }
    else if(getCachedParameters()->m_isBlending != m_parameters->m_isBlending)
    {
        glDisable(GL_BLEND);
        getCachedParameters()->m_isBlending = m_parameters->m_isBlending;
    }
}

void ieMaterial::unbind(void)
{
    assert(m_parameters != nullptr);
    assert(m_parameters->m_shader != nullptr);
    m_parameters->m_shader->unbind();
}

