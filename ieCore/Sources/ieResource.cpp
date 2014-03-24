//
//  ieResource.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieResource.h"

ieResource::ieResource(E_RESOURCE_TYPE resourceType) :
m_resourceType(resourceType),
m_isLoaded(false),
m_guid("")
{
    
}

ieResource::~ieResource(void)
{
    assert(m_owners.size() == 0);
}

void ieResource::addOwner(const std::shared_ptr<ieObject>& owner)
{
    m_owners.insert(owner);
}

void ieResource::removeOwner(const std::shared_ptr<ieObject>& owner)
{
    m_owners.erase(owner);
}

const ui32 ieResource::getOwnersCount(void) const
{
    return m_owners.size();
}

std::string ieResource::getGUID(void) const
{
    return m_guid;
}
