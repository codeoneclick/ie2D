//
//  ieEvent.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieEvent.h"
#include "ieIEventDispatcher.h"

ieEvent::ieEvent(const std::string& _type, const std::shared_ptr<ieIEventDispatcher>& target):
m_type(_type),
m_target(target)
{
    m_description = "ieEvent";
}

ieEvent::~ieEvent(void)
{
    
}

std::string ieEvent::getType(void) const
{
    return m_type;
}

std::shared_ptr<ieIEventDispatcher> ieEvent::getTarget(void) const
{
    return m_target;
}