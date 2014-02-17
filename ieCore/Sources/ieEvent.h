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

static const std::string kEVENT_ON_UPDATE = "EVENT_ON_UPDATE";
static const std::string kEVENT_ON_DRAW = "EVENT_ON_DRAW";
static const std::string kEVENT_ON_ENTER_FRAME = "EVENT_ON_ENTER_FRAME";
static const std::string kEVENT_ON_EXIT_FRAME = "EVENT_ON_EXIT_FRAME";
static const std::string kEVENT_ON_TRANSITION_REGISTER = "EVENT_ON_TRANSITION_REGISTER";
static const std::string kEVENT_ON_TRANSITION_UNREGISTER = "EVENT_ON_TRANSITION_UNREGISTER";
static const std::string kEVENT_ON_TRANSITION_ENTER = "EVENT_ON_TRANSITION_ENTER";
static const std::string kEVENT_ON_TRANSITION_EXIT = "EVENT_ON_TRANSITION_EXIT";
static const std::string kEVENT_ON_ADDED = "EVENT_ON_ADDED";
static const std::string kEVENT_ON_REMOVED = "EVENT_ON_REMOVED";

class ieIEventDispatcher;
class ieEvent : public ieObject
{
private:
    
protected:
    
    std::string m_type;
    std::shared_ptr<ieIEventDispatcher> m_target;
    bool m_bubbles;
    
public:
    
    ieEvent(const std::string& type,
            const std::shared_ptr<ieIEventDispatcher>& target,
            bool bubbles = false);
    virtual ~ieEvent(void);
    
    std::string getType(void) const;
    std::shared_ptr<ieIEventDispatcher> getTarget(void) const;
    bool isBubbles(void);
};

#endif
