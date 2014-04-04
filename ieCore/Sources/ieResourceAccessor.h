//
//  ieResourceAccessor.h
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieResourceAccessor__
#define __ieCore__ieResourceAccessor__

#include "ieObject.h"

class ieResource;
class ieShader;
class ieTexture;
class ieSequence;

class ieResourceAccessor : public ieObject
{
private:
    
protected:
    
    std::map<std::string, std::shared_ptr<ieResource>> m_resources;
    
public:
    
    ieResourceAccessor(void);
    ~ieResourceAccessor(void);
    
    std::shared_ptr<ieShader> getShader(const std::string& vsFilename,
                                        const std::string& fsFilename,
                                        const std::shared_ptr<ieObject>& owner = nullptr);
    
    std::shared_ptr<ieTexture> getTexture(const std::string& filename,
                                          const std::shared_ptr<ieObject>& owner = nullptr);
    
    std::shared_ptr<ieSequence> getSequence(const std::string& filename,
                                            const std::shared_ptr<ieObject>& owner = nullptr);
};

#endif
