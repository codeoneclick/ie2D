//
//  ieMaterial.h
//  ieCore
//
//  Created by sergey.sergeev on 2/10/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieMaterial__
#define __ieCore__ieMaterial__

#include "iePredefined.h"
#include "ieEnums.h"

class ieMaterialCachedParameters;

#pragma mark -
#pragma mark ieIMaterial
class ieIMaterial
{
    
#pragma mark -
#pragma mark ieIMaterial - private section
private:
    
#pragma mark -
#pragma mark ieIMaterial - protected section
protected:

public:
    
#pragma mark -
#pragma mark ieIMaterial - public constructor/destructor
    
    ieIMaterial(void) = default;
    virtual ~ieIMaterial(void) = default;
    
#pragma mark -
#pragma mark ieMaterialProtocol - setters
    
    virtual void setCulling(bool value) = 0;
    virtual void setCullingMode(GLenum value) = 0;
    
    virtual void setBlending(bool value) = 0;
    virtual void setBlendingFunctionSource(GLenum value) = 0;
    virtual void setBlendingFunctionDestination(GLenum value) = 0;
    
    virtual void setDepthTest(bool value) = 0;
    virtual void setDepthMask(bool value) = 0;
    
    virtual void setShader(ieSharedShaderRef shader) = 0;
    
    virtual void setTexture(ieSharedTextureRef texture,
                            E_SHADER_SAMPLER sampler) = 0;
    
    virtual void setColor(ieSharedColorRef color) = 0;
    
#pragma mark -
#pragma mark ieMaterialProtocol - getters
    
    virtual bool isCulling(void) const = 0;
    virtual GLenum getCullingMode(void) const = 0;
    
    virtual bool isBlending(void) const = 0;
    virtual GLenum getBlendingFunctionSource(void) const = 0;
    virtual GLenum getBlendingFunctionDestination(void) const = 0;
    
    virtual bool isDepthTest(void) const = 0;
    virtual bool isDepthMask(void) const = 0;
    
    virtual ieSharedShader getShader(void) const = 0;
    
    virtual ieSharedTexture getTexture(E_SHADER_SAMPLER sampler) const = 0;
    
    virtual ieSharedColor getColor(void) const = 0;
};

#pragma mark -
#pragma mark ieMaterial
class ieMaterial final: public ieIMaterial
{

#pragma mark -
#pragma mark ieMaterial - private section
private:
   
#pragma mark -
#pragma mark ieMaterial - protected section
protected:
    
    std::shared_ptr<ieMaterialCachedParameters> m_parameters;
    static std::shared_ptr<ieMaterialCachedParameters> m_cachedParameters;
    static std::shared_ptr<ieMaterialCachedParameters> getCachedParameters(void);
    
public:
    
#pragma mark -
#pragma mark ieMaterial - public constructor/destructor
    
    ieMaterial(void);
    ~ieMaterial(void);
    
#pragma mark -
#pragma mark ieMaterial - setters
    
    void setCulling(bool value);
    void setCullingMode(GLenum value);
    
    void setBlending(bool value);
    void setBlendingFunctionSource(GLenum value);
    void setBlendingFunctionDestination(GLenum value);
    
    void setDepthTest(bool value);
    void setDepthMask(bool value);
    
    void setShader(ieSharedShaderRef shader);
    
    void setTexture(ieSharedTextureRef texture,
                            E_SHADER_SAMPLER sampler);
    
    void setColor(ieSharedColorRef color);
    
#pragma mark -
#pragma mark ieMaterial - getters
    
    std::string getBatchGUID(void) const;
    
    bool isCulling(void) const;
    GLenum getCullingMode(void) const;
    
    bool isBlending(void) const;
    GLenum getBlendingFunctionSource(void) const;
    GLenum getBlendingFunctionDestination(void) const;
    
    bool isDepthTest(void) const;
    bool isDepthMask(void) const;
    
    ieSharedShader getShader(void) const;
    
    ieSharedTexture getTexture(E_SHADER_SAMPLER sampler) const;
    
    ieSharedColor getColor(void) const;
    
#pragma mark -
#pragma mark ieMaterial - functions
    
    void bind(void) const;
    void unbind(void) const;
};

#endif
