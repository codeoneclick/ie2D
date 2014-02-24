//
//  ieDisplayObjectContainer.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieDisplayObjectContainer.h"
#include "ieEvent.h"

ieDisplayObjectContainer::ieDisplayObjectContainer(const glm::vec4& frame) :
ieInteractiveObject(frame)
{

}

ieDisplayObjectContainer::~ieDisplayObjectContainer(void)
{

}

void ieDisplayObjectContainer::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onUpdate(event);
}

void ieDisplayObjectContainer::onDraw(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onDraw(event);
}

void ieDisplayObjectContainer::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onEnterFrame(event);
}

void ieDisplayObjectContainer::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onExitFrame(event);
}

void ieDisplayObjectContainer::onAdded(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onAdded(event);
    std::cout<<"ieDisplayObjectContainer::onAdded"<<std::endl;
}

void ieDisplayObjectContainer::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onRemoved(event);
}

void ieDisplayObjectContainer::addChild(const std::shared_ptr<ieDisplayObject>& child)
{
    assert(m_uniqueChilds.count(child) == 0);
    m_uniqueChilds.insert(child);
    m_childs.push_back(child);
}

void ieDisplayObjectContainer::addChildAt(const std::shared_ptr<ieDisplayObject>& child, i32 index)
{
    assert(m_uniqueChilds.count(child) == 0);
    assert(index <= m_childs.size());
    m_uniqueChilds.insert(child);
    m_childs.insert(m_childs.begin() + index, child);
}

bool ieDisplayObjectContainer::contains(const std::shared_ptr<ieDisplayObject>& child) const
{
    return m_uniqueChilds.count(child) != 0;
}

std::shared_ptr<ieDisplayObject> ieDisplayObjectContainer::getChildAt(i32 index) const
{
    assert(index < m_childs.size());
    return m_childs.at(index);
}

std::shared_ptr<ieDisplayObject> ieDisplayObjectContainer::getChildByName(const std::string& name) const
{
    return nullptr;
}

i32 ieDisplayObjectContainer::getChildIndex(const std::shared_ptr<ieDisplayObject>& child) const
{
    for(ui32 i = 0; i < m_childs.size(); ++i)
    {
        if(child == m_childs.at(i))
        {
            return i;
        }
    }
    return -1;
}

std::vector<std::shared_ptr<ieDisplayObject>> ieDisplayObjectContainer::getObjectsUnderPoint(const glm::vec2& point) const
{
    return std::vector<std::shared_ptr<ieDisplayObject>>();
}

void ieDisplayObjectContainer::removeChild(const std::shared_ptr<ieDisplayObject>& child)
{
    
}

void ieDisplayObjectContainer::removeChildAt(i32 index)
{
    
}

void ieDisplayObjectContainer::removeChildren(i32 startIndex, i32 endIndex)
{
    
}

void ieDisplayObjectContainer::setChildIndex(const std::shared_ptr<ieDisplayObject>& child, i32 index)
{
    
}

void ieDisplayObjectContainer::swapChildren(const std::shared_ptr<ieDisplayObject>& child_01,
                  const std::shared_ptr<ieDisplayObject>& child_02)
{
    
}

void ieDisplayObjectContainer::swapChildrenAt(i32 index_01, i32 index_02)
{
    
}
