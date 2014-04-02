//
//  ieMaterial.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/10/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieMaterial.h"
#include "ieShader.h"
#include "ieTexture.h"
#include "ieColor.h"

#pragma mark -
#pragma mark ieMaterialCachedParameters

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
    
    ieSharedShader m_shader;
    ieSharedColor m_color;
    std::array<ieSharedTexture, E_SHADER_SAMPLER_MAX> m_textures;
    
public:
    
    ieMaterialCachedParameters(void);
    ~ieMaterialCachedParameters(void);
};

ieMaterialCachedParameters::ieMaterialCachedParameters(void) :
m_shader(nullptr),
m_color(std::make_shared<ieColor>(255, 255, 255, 255))
{
    std::for_each(m_textures.begin(), m_textures.end(), [](ieSharedTexture& iterator){
        iterator = nullptr;
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

#pragma mark -
#pragma mark ieMaterial - constructor/destructor

ieMaterial::ieMaterial(void) :
m_parameters(std::make_shared<ieMaterialCachedParameters>())
{
    
}

ieMaterial::~ieMaterial(void)
{
    
}

#pragma mark -
#pragma mark ieMaterial - getters

std::string ieMaterial::getBatchGUID(void) const
{
    std::string guid = "";
    for(ui32 i = 0; i < E_SHADER_SAMPLER_MAX; ++i)
    {
        if(m_parameters->m_textures[i] != nullptr)
        {
           guid = guid.append(m_parameters->m_textures[i]->getGUID());
        }
    }
    guid = guid.append(m_parameters->m_shader->getGUID());
    guid = m_parameters->m_isCulling ? guid.append("CULLING:YES") : guid.append("CULLING:NO");
    guid = m_parameters->m_isBlending ? guid.append("BLENDING:YES") : guid.append("BLENDING:NO");
    guid = m_parameters->m_isDepthMask ? guid.append("DEPTH_MASK:YES") : guid.append("DEPTH_MASK:NO");
    guid = m_parameters->m_isDepthTest ? guid.append("DEPTH_TEST:YES") : guid.append("DEPTH_TEST:NO");
    return guid;
}

bool ieMaterial::isCulling(void) const
{
    assert(m_parameters != nullptr);
    return m_parameters->m_isCulling;
}

bool ieMaterial::isBlending(void) const
{
    assert(m_parameters != nullptr);
    return m_parameters->m_isBlending;
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

GLenum ieMaterial::getCullingMode(void) const
{
    assert(m_parameters != nullptr);
    return m_parameters->m_cullingMode;
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

ieSharedShader ieMaterial::getShader(void) const
{
    assert(m_parameters != nullptr);
    return m_parameters->m_shader;
}

ieSharedTexture ieMaterial::getTexture(E_SHADER_SAMPLER sampler) const
{
    assert(m_parameters != nullptr);
    return m_parameters->m_textures[sampler];
}

ieSharedColor ieMaterial::getColor(void) const
{
    assert(m_parameters != nullptr);
    return m_parameters->m_color;
}

#pragma mark -
#pragma mark ieMaterial - setters

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

void ieMaterial::setShader(ieSharedShaderRef shader)
{
    assert(m_parameters != nullptr);
    m_parameters->m_shader = shader;
}

void ieMaterial::setTexture(ieSharedTextureRef texture,
                            E_SHADER_SAMPLER sampler)
{
    assert(m_parameters != nullptr);
    m_parameters->m_textures.at(sampler) = texture;
}

void ieMaterial::setColor(ieSharedColorRef color)
{
    assert(m_parameters != nullptr);
    m_parameters->m_color = color;
}

#pragma mark -
#pragma mark ieMaterial - functions

void ieMaterial::bind(void) const
{
    assert(m_parameters != nullptr);
    assert(m_parameters->m_shader != nullptr);
    m_parameters->m_shader->bind();
    
    for(ui32 i = 0; i < E_SHADER_SAMPLER_MAX; ++i)
    {
        if(m_parameters->m_textures[i] != nullptr)
        {
            m_parameters->m_shader->setTexture(m_parameters->m_textures[i]->getTexture(),
                                               static_cast<E_SHADER_SAMPLER>(i));
        }
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

void ieMaterial::unbind(void) const
{
    assert(m_parameters != nullptr);
    assert(m_parameters->m_shader != nullptr);
    m_parameters->m_shader->unbind();
}

