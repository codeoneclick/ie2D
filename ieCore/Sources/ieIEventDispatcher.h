//
//  ieIEventDispatcher.h
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieIEventDispatcher__
#define __ieCore__ieIEventDispatcher__

#include "ieCommon.h"

class ieEvent;
class ieIEventDispatcher
{
private:
    
protected:
    
public:
    
    ieIEventDispatcher(void) = default;
    ~ieIEventDispatcher(void) = default;
    
    virtual void addEventListener(const std::string& type,
                                  const std::function<void(const std::shared_ptr<ieEvent>&)>& function) = 0;
    virtual void removeEventListener(const std::string& type,
                                     const std::function<void(const std::shared_ptr<ieEvent>&)>& function) = 0;
    virtual bool hasEventListener(const std::string& _type) = 0;
    virtual void dispatchEvent(const std::shared_ptr<ieEvent>& event) = 0;
};

#endif
