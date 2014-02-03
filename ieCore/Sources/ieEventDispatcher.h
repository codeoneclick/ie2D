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

typedef std::shared_ptr<std::function<void(const std::shared_ptr<ieEvent>&)>> ieEventDispatcherFunction;

class ieEventDispatcher :
public ieObject,
public ieIEventDispatcher
{
private:
    
protected:
    
    std::map<std::string, std::set<ieEventDispatcherFunction>> m_functions;
    
public:
    
    ieEventDispatcher(void);
    ~ieEventDispatcher(void);
    
    void addEventListener(const std::string& type,
                          const ieEventDispatcherFunction& function);
    void removeEventListener(const std::string& type,
                             const ieEventDispatcherFunction& function);
    bool hasEventListener(const std::string& type);
    void dispatchEvent(const std::shared_ptr<ieEvent>& event);
    
};

#endif
