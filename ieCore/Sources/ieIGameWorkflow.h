//
//  ieIGameWorkflow.h
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieIGameWorkflow__
#define __ieCore__ieIGameWorkflow__

#include "ieCommon.h"

class ieIGameTransition;
class ieIGameLoop;

class ieIGameWorkflow
{
private:
    
protected:
    
    std::map<std::string, std::shared_ptr<ieIGameTransition> > m_transitions;
    std::shared_ptr<ieIGameTransition> m_currentTransition;
    std::shared_ptr<ieIGameLoop> m_gameLoop;

public:
    
    ieIGameWorkflow(void);
    virtual ~ieIGameWorkflow(void);
    
    void registerTransition(const std::shared_ptr<ieIGameTransition>& transition);
    void unregisterTransition(const std::shared_ptr<ieIGameTransition>& transition);
    
    void goToTransition(const std::string& name);
};

#endif
