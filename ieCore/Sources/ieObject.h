//
//  ieObject.h
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieObject__
#define __ieCore__ieObject__

#include "ieCommon.h"

class ieObject : public std::enable_shared_from_this<ieObject>
{
private:
    
protected:
    
    std::string m_description;
    std::map<std::string, std::shared_ptr<ieObject>> m_objects;
    
public:
    
    std::string getDescription(void) const;
    
    ieObject(void);
    ~ieObject(void);
    
    void addObjectWithKey(const std::shared_ptr<ieObject>& object, const std::string& key);
    void removeObjectWithKey(const std::string& key);
    void setObjectWithKey(const std::shared_ptr<ieObject>& object, const std::string& key);
    std::shared_ptr<ieObject> getObjectWithKey(const std::string& key);
};

#endif 
