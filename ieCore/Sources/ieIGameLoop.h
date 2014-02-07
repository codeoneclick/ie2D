//
//  ieIGameLoop.h
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieIGameLoop__
#define __ieCore__ieIGameLoop__

#include "ieCommon.h"
#include "ieEnums.h"

class ieIGameTransition;

class ieIGameLoop
{
private:
    
protected:
    
    std::shared_ptr<ieIGameTransition> m_currentTransition;
    ieIGameLoop(void);

public:
    
    virtual ~ieIGameLoop(void) = default;
    
    static std::shared_ptr<ieIGameLoop> createGameLoop(E_PLATFORM_API api);
    
    void setCurrentTransition(const std::shared_ptr<ieIGameTransition>& transition);
    void update(void);
    void draw(void);
};

#endif
