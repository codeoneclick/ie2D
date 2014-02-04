//
//  ieObject.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieObject.h"

ieObject::ieObject(void)
{
    m_description = "ieObject";
}

ieObject::~ieObject(void)
{
    m_objects.clear();
}

std::string ieObject::getDescription(void) const
{
    return m_description;
}

void ieObject::addObjectWithKey(const std::shared_ptr<ieObject>& object, const std::string& key)
{
    const auto& iterator = m_objects.find(key);
    assert(iterator == m_objects.end());
    m_objects.insert(std::make_pair(key, object));
}

void ieObject::removeObjectWithKey(const std::string& key)
{
    const auto& iterator = m_objects.find(key);
    assert(iterator != m_objects.end());
    m_objects.erase(iterator);
}

void ieObject::setObjectWithKey(const std::shared_ptr<ieObject>& object, const std::string& key)
{
    const auto& iterator = m_objects.find(key);
    assert(iterator != m_objects.end());
    iterator->second = object;
}

std::shared_ptr<ieObject> ieObject::getObjectWithKey(const std::string& key)
{
    auto iterator = m_objects.find(key);
    return iterator != m_objects.end() ? iterator->second : nullptr;
}