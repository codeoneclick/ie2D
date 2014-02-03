//
//  ieEvent.h
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieEvent__
#define __ieCore__ieEvent__

#include "ieObject.h"

class ieEventDispatcher;
class ieEvent : public ieObject
{
private:
    
protected:
    
    std::string m_type;
    std::shared_ptr<ieIEventDispatcher> m_target;
    
public:
    
    ieEvent(const std::string& type, const std::shared_ptr<ieIEventDispatcher>& target);
    ~ieEvent(void);
    
    std::string getType(void) const;
    std::shared_ptr<ieIEventDispatcher> getTarget(void) const;
};

#endif
