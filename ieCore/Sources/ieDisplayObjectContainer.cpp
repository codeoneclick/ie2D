//
//  ieDisplayObjectContainer.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieDisplayObjectContainer.h"
#include "ieResourceAccessor.h"
#include "ieBatchMgr.h"
#include "ieTouchRecognizer.h"
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

void ieDisplayObjectContainer::setVisible(bool value)
{
    ieInteractiveObject::setVisible(value);
    std::for_each(m_childs.begin(), m_childs.end(), [value](std::shared_ptr<ieDisplayObject> iterator){
        iterator->setVisible(value);
    });
}

void ieDisplayObjectContainer::setBatched(bool value)
{
    ieInteractiveObject::setBatched(value);
    std::for_each(m_childs.begin(), m_childs.end(), [value](std::shared_ptr<ieDisplayObject> iterator){
        iterator->setBatched(value);
    });
}

void ieDisplayObjectContainer::setShader(ieSharedShaderRef shader, bool isUpdateHierarchy)
{
    ieDisplayObject::setShader(shader, isUpdateHierarchy);
    if(isUpdateHierarchy)
    {
        std::for_each(m_childs.begin(), m_childs.end(), [shader, isUpdateHierarchy](std::shared_ptr<ieDisplayObject> iterator){
            iterator->setShader(shader, isUpdateHierarchy);
        });
    }
}

void ieDisplayObjectContainer::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    ieInteractiveObject::onUpdate(event);
    std::for_each(m_childs.begin(), m_childs.end(), [event](std::shared_ptr<ieDisplayObject> iterator){
        iterator->onUpdate(event);
    });
}

void ieDisplayObjectContainer::onDraw(const std::shared_ptr<ieEvent>& event)
{
    ieInteractiveObject::onDraw(event);
    std::for_each(m_childs.begin(), m_childs.end(), [event](std::shared_ptr<ieDisplayObject> iterator){
        iterator->onDraw(event);
    });
}

void ieDisplayObjectContainer::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    ieInteractiveObject::onEnterFrame(event);
    std::for_each(m_childs.begin(), m_childs.end(), [event](std::shared_ptr<ieDisplayObject> iterator){
        iterator->onEnterFrame(event);
    });
}

void ieDisplayObjectContainer::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    ieInteractiveObject::onExitFrame(event);
    std::for_each(m_childs.begin(), m_childs.end(), [event](std::shared_ptr<ieDisplayObject> iterator){
        iterator->onExitFrame(event);
    });
}

void ieDisplayObjectContainer::onUpdateTouchMask(const std::shared_ptr<ieEvent> &event)
{
    ieInteractiveObject::onUpdateTouchMask(event);
    std::for_each(m_childs.begin(), m_childs.end(), [event](std::shared_ptr<ieInteractiveObject> iterator){
        iterator->onUpdateTouchMask(event);
    });
}

void ieDisplayObjectContainer::onAdded(const std::shared_ptr<ieEvent>& event)
{
    ieInteractiveObject::onAdded(event);
    std::for_each(m_childs.begin(), m_childs.end(), [event](std::shared_ptr<ieDisplayObject> iterator){
        iterator->onAdded(event);
    });
}

void ieDisplayObjectContainer::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieInteractiveObject::onRemoved(event);
    std::for_each(m_childs.begin(), m_childs.end(), [event](std::shared_ptr<ieDisplayObject> iterator){
        iterator->onRemoved(event);
    });
}

void ieDisplayObjectContainer::addChild(const std::shared_ptr<ieDisplayObjectContainer>& child)
{
    assert(m_uniqueChilds.count(child) == 0);
    m_uniqueChilds.insert(child);
    m_childs.push_back(child);
    child->m_parent = std::static_pointer_cast<ieDisplayObjectContainer>(ieObject::shared_from_this());
    
    std::shared_ptr<ieEvent> eventOnStageAdded = std::make_shared<ieEvent>(kEVENT_ON_ADDED, child);
    eventOnStageAdded->addObjectWithKey(m_resourceAccessor, "resourceAccessor");
    eventOnStageAdded->addObjectWithKey(m_stage, "stage");
    eventOnStageAdded->addObjectWithKey(m_camera, "camera");
    eventOnStageAdded->addObjectWithKey(m_batchMgr, "batchMgr");
    eventOnStageAdded->addObjectWithKey(m_touchRecognizer, "touchRecognizer");
    ieDisplayObjectContainer::dispatchEvent(eventOnStageAdded);
}

void ieDisplayObjectContainer::addChildAt(const std::shared_ptr<ieDisplayObjectContainer>& child, i32 index)
{
    assert(m_uniqueChilds.count(child) == 0);
    assert(index <= m_childs.size());
    m_uniqueChilds.insert(child);
    m_childs.insert(m_childs.begin() + index, child);
    child->m_parent = std::static_pointer_cast<ieDisplayObjectContainer>(ieObject::shared_from_this());
    
    std::shared_ptr<ieEvent> eventOnStageAdded = std::make_shared<ieEvent>(kEVENT_ON_ADDED, child);
    eventOnStageAdded->addObjectWithKey(m_resourceAccessor, "resourceAccessor");
    eventOnStageAdded->addObjectWithKey(m_stage, "stage");
    eventOnStageAdded->addObjectWithKey(m_camera, "camera");
    eventOnStageAdded->addObjectWithKey(m_batchMgr, "batchMgr");
    eventOnStageAdded->addObjectWithKey(m_touchRecognizer, "touchRecognizer");
    ieDisplayObjectContainer::dispatchEvent(eventOnStageAdded);
}

bool ieDisplayObjectContainer::contains(const std::shared_ptr<ieDisplayObjectContainer>& child) const
{
    return m_uniqueChilds.count(child) != 0;
}

std::shared_ptr<ieDisplayObjectContainer> ieDisplayObjectContainer::getChildAt(i32 index) const
{
    assert(index < m_childs.size());
    return m_childs.at(index);
}

std::shared_ptr<ieDisplayObjectContainer> ieDisplayObjectContainer::getChildByName(const std::string& name) const
{
    return nullptr;
}

i32 ieDisplayObjectContainer::getChildIndex(const std::shared_ptr<ieDisplayObjectContainer>& child) const
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

std::vector<std::shared_ptr<ieDisplayObjectContainer>> ieDisplayObjectContainer::getObjectsUnderPoint(const glm::vec2& point) const
{
    return std::vector<std::shared_ptr<ieDisplayObjectContainer>>();
}

void ieDisplayObjectContainer::removeChild(const std::shared_ptr<ieDisplayObjectContainer>& child)
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

void ieDisplayObjectContainer::setChildIndex(const std::shared_ptr<ieDisplayObjectContainer>& child, i32 index)
{
    assert(m_uniqueChilds.count(child) != 0);
    auto iterator = std::find(m_childs.begin(), m_childs.end(), child);
    assert(iterator != m_childs.end());
    m_childs.erase(iterator);
    m_uniqueChilds.erase(child);
    
    assert(m_uniqueChilds.count(child) == 0);
    assert(index <= m_childs.size());
    m_uniqueChilds.insert(child);
    m_childs.insert(m_childs.begin() + index, child);
}

void ieDisplayObjectContainer::swapChildren(const std::shared_ptr<ieDisplayObjectContainer>& child_01,
                                            const std::shared_ptr<ieDisplayObjectContainer>& child_02)
{
    //#TODO
}

void ieDisplayObjectContainer::swapChildrenAt(i32 index_01, i32 index_02)
{
    //#TODO
}

void ieDisplayObjectContainer::sortChildrens(void)
{
    std::sort(m_childs.begin(), m_childs.end(), [](const std::shared_ptr<ieDisplayObjectContainer>& value_01,
                                                   const std::shared_ptr<ieDisplayObjectContainer>& value_02){
        return value_01->getZIndex() < value_02->getZIndex();
    });
}
