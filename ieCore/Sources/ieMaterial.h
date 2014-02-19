//
//  ieMaterial.h
//  ieCore
//
//  Created by sergey.sergeev on 2/10/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieMaterial__
#define __ieCore__ieMaterial__

#include "ieCommon.h"
#include "ieEnums.h"

class ieShader;
class ieTexture;
class ieMaterialCachedParameters;

class ieMaterial
{
private:
    
protected:
    
    std::shared_ptr<ieMaterialCachedParameters> m_parameters;
    static std::shared_ptr<ieMaterialCachedParameters> m_cachedParameters;
    static std::shared_ptr<ieMaterialCachedParameters> getCachedParameters(void);
    
public:
    
    ieMaterial(void);
    ~ieMaterial(void);
    
    bool isCulling(void) const;
    GLenum getCullingMode(void) const;
    
    bool isBlending(void) const;
    GLenum getBlendingFunctionSource(void) const;
    GLenum getBlendingFunctionDestination(void) const;
    
    bool isDepthTest(void) const;
    bool isDepthMask(void) const;
    
    void setCulling(bool value);
    void setCullingMode(GLenum value);
    
    void setBlending(bool value);
    void setBlendingFunctionSource(GLenum value);
    void setBlendingFunctionDestination(GLenum value);
    
    void setDepthTest(bool value);
    void setDepthMask(bool value);
    
    void setShader(const std::shared_ptr<ieShader>& shader);
    void setTexture(const std::shared_ptr<ieTexture>& texture,
                    E_SHADER_SAMPLER sampler);
    void bind(void);
    void unbind(void);
};

#endif
