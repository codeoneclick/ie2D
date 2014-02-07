//
//  ieEventDispatcher.h
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieEventDispatcher__
#define __ieCore__ieEventDispatcher__

#include "ieObject.h"
#include "ieIEventDispatcher.h"

class ieEventDispatcher :
public ieObject,
public ieIEventDispatcher
{
private:
    
protected:
    
    std::map<std::string, std::set<ieEventDispatcherFunctionShared>> m_functions;
    
public:
    
    ieEventDispatcher(void);
    virtual ~ieEventDispatcher(void);
    
    void addEventListener(const std::string& type,
                          const ieEventDispatcherFunctionShared& function);
    void removeEventListener(const std::string& type,
                             const ieEventDispatcherFunctionShared& function);
    bool hasEventListener(const std::string& type);
    void dispatchEvent(const std::shared_ptr<ieEvent>& event);
    
};

#endif
