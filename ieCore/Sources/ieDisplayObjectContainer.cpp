//
//  ieDisplayObjectContainer.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieDisplayObjectContainer.h"
#include "ieResourceAccessor.h"
#include "ieStage.h"
#include "ieCamera.h"
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
    std::for_each(m_childs.begin(), m_childs.end(), [event](std::shared_ptr<ieDisplayObject> iterator){
        iterator->onUpdate(event);
    });
}

void ieDisplayObjectContainer::onDraw(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onDraw(event);
    std::for_each(m_childs.begin(), m_childs.end(), [event](std::shared_ptr<ieDisplayObject> iterator){
        iterator->onDraw(event);
    });
}

void ieDisplayObjectContainer::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onEnterFrame(event);
    std::for_each(m_childs.begin(), m_childs.end(), [event](std::shared_ptr<ieDisplayObject> iterator){
        iterator->onEnterFrame(event);
    });
}

void ieDisplayObjectContainer::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onExitFrame(event);
    std::for_each(m_childs.begin(), m_childs.end(), [event](std::shared_ptr<ieDisplayObject> iterator){
        iterator->onExitFrame(event);
    });
}

void ieDisplayObjectContainer::onAdded(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onAdded(event);
    std::for_each(m_childs.begin(), m_childs.end(), [event](std::shared_ptr<ieDisplayObject> iterator){
        iterator->onAdded(event);
    });
    std::cout<<"ieDisplayObjectContainer::onAdded"<<std::endl;
}

void ieDisplayObjectContainer::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onRemoved(event);
    std::for_each(m_childs.begin(), m_childs.end(), [event](std::shared_ptr<ieDisplayObject> iterator){
        iterator->onRemoved(event);
    });
}

void ieDisplayObjectContainer::addChild(const std::shared_ptr<ieDisplayObject>& child)
{
    assert(m_uniqueChilds.count(child) == 0);
    m_uniqueChilds.insert(child);
    m_childs.push_back(child);
    child->m_parent = std::static_pointer_cast<ieDisplayObjectContainer>(shared_from_this());
    
    std::shared_ptr<ieEvent> eventOnStageAdded = std::make_shared<ieEvent>(kEVENT_ON_ADDED, child);
    eventOnStageAdded->addObjectWithKey(m_resourceAccessor, "resourceAccessor");
    eventOnStageAdded->addObjectWithKey(m_stage, "stage");
    eventOnStageAdded->addObjectWithKey(m_camera, "camera");
    ieDisplayObjectContainer::dispatchEvent(eventOnStageAdded);
}

void ieDisplayObjectContainer::addChildAt(const std::shared_ptr<ieDisplayObject>& child, i32 index)
{
    assert(m_uniqueChilds.count(child) == 0);
    assert(index <= m_childs.size());
    m_uniqueChilds.insert(child);
    m_childs.insert(m_childs.begin() + index, child);
    child->m_parent = std::static_pointer_cast<ieDisplayObjectContainer>(shared_from_this());
    
    std::shared_ptr<ieEvent> eventOnStageAdded = std::make_shared<ieEvent>(kEVENT_ON_ADDED, child);
    eventOnStageAdded->addObjectWithKey(m_resourceAccessor, "resourceAccessor");
    eventOnStageAdded->addObjectWithKey(m_stage, "stage");
    eventOnStageAdded->addObjectWithKey(m_camera, "camera");
    ieDisplayObjectContainer::dispatchEvent(eventOnStageAdded);
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
    m_uniqueChilds.erase(child);
    auto iterator = std::find(m_childs.begin(), m_childs.end(), child);
    if(iterator != m_childs.end())
    {
        m_childs.erase(iterator);
    }
    std::shared_ptr<ieEvent> eventOnStageRemoved = std::make_shared<ieEvent>(kEVENT_ON_REMOVED, child);
    ieDisplayObjectContainer::dispatchEvent(eventOnStageRemoved);
}

void ieDisplayObjectContainer::removeChildAt(i32 index)
{
    assert(index < m_childs.size());
    auto child = m_childs.at(index);
    ieDisplayObjectContainer::removeChild(child);
    
    std::shared_ptr<ieEvent> eventOnStageRemoved = std::make_shared<ieEvent>(kEVENT_ON_REMOVED, child);
    ieDisplayObjectContainer::dispatchEvent(eventOnStageRemoved);
}

void ieDisplayObjectContainer::removeChildren(i32 startIndex, i32 endIndex)
{
    assert(startIndex <= endIndex);
    assert(startIndex >= 0);
    assert(endIndex < m_childs.size());
    for(ui32 index = startIndex; index < endIndex; ++index)
    {
        auto child = m_childs.at(index);
        ieDisplayObjectContainer::removeChild(child);
        
        std::shared_ptr<ieEvent> eventOnStageRemoved = std::make_shared<ieEvent>(kEVENT_ON_REMOVED, child);
        ieDisplayObjectContainer::dispatchEvent(eventOnStageRemoved);
    }
}

void ieDisplayObjectContainer::setChildIndex(const std::shared_ptr<ieDisplayObject>& child, i32 index)
{
    assert(m_uniqueChilds.count(child) != 0);
    auto iterator = std::find(m_childs.begin(), m_childs.end(), child);
    assert(iterator != m_childs.end());
    m_childs.erase(iterator);
    ieDisplayObjectContainer::addChildAt((*iterator), index);
}

void ieDisplayObjectContainer::swapChildren(const std::shared_ptr<ieDisplayObject>& child_01,
                  const std::shared_ptr<ieDisplayObject>& child_02)
{
    
}

void ieDisplayObjectContainer::swapChildrenAt(i32 index_01, i32 index_02)
{
    
}
