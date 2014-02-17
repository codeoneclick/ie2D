//
//  ieDisplayObjectContainer.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieDisplayObjectContainer.h"
#include "ieEvent.h"

ieDisplayObjectContainer::ieDisplayObjectContainer(void)
{
    m_functionOnUpdate = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObjectContainer::onUpdate, this, std::placeholders::_1));
    m_functionOnDraw = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObjectContainer::onDraw, this, std::placeholders::_1));
    m_functionOnEnterFrame = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObjectContainer::onEnterFrame, this, std::placeholders::_1));
    m_functionOnExitFrame = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObjectContainer::onExitFrame, this, std::placeholders::_1));
    m_functionOnAdded = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObjectContainer::onAdded, this, std::placeholders::_1));
    m_functionOnRemoved = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObjectContainer::onRemoved, this, std::placeholders::_1));;
    
    ieDisplayObjectContainer::addEventListener(kEVENT_ON_ADDED, m_functionOnAdded);
    ieDisplayObjectContainer::addEventListener(kEVENT_ON_REMOVED, m_functionOnRemoved);
}

ieDisplayObjectContainer::~ieDisplayObjectContainer(void)
{
    ieDisplayObjectContainer::removeEventListener(kEVENT_ON_ADDED, m_functionOnAdded);
    ieDisplayObjectContainer::removeEventListener(kEVENT_ON_REMOVED, m_functionOnRemoved);
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
}

void ieDisplayObjectContainer::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onRemoved(event);
}
