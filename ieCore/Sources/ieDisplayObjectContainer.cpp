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
