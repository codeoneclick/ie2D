//
//  ieResource.h
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieResource__
#define __ieCore__ieResource__

#include "ieEventDispatcher.h"
#include "ieEnums.h"

class ieResource : public ieEventDispatcher
{
private:
    
protected:
    
    E_RESOURCE_TYPE m_resourceType;
    bool m_isLoaded;
    std::set<std::shared_ptr<ieObject>> m_owners;
    
public:
    
    ieResource(E_RESOURCE_TYPE resourceType);
    ~ieResource(void);
    
    void addOwner(const std::shared_ptr<ieObject>& owner);
    void removeOwner(const std::shared_ptr<ieObject>& owner);
    
    const ui32 getOwnersCount(void) const;
};

#endif
