//
//  ieInteractiveObject.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieInteractiveObject.h"
#include "ieTouchRecognizer.h"
#include "ieEvent.h"

ieInteractiveObject::ieInteractiveObject(const glm::vec4& frame) :
ieDisplayObject(frame),
m_isTouchable(false)
{
    
}

ieInteractiveObject::~ieInteractiveObject(void)
{
    
}

void ieInteractiveObject::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onUpdate(event);
}

void ieInteractiveObject::onDraw(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onDraw(event);
}

void ieInteractiveObject::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onEnterFrame(event);
}

void ieInteractiveObject::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onExitFrame(event);
}

void ieInteractiveObject::onAdded(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onAdded(event);
    m_touchRecognizer = std::static_pointer_cast<ieTouchRecognizer>(event->getObjectWithKey("touchRecognizer"));
    assert(m_camera != nullptr);
}

void ieInteractiveObject::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onRemoved(event);
}

void ieInteractiveObject::setTouchable(bool value)
{
    m_isTouchable = value;
    if(m_touchRecognizer != nullptr && m_isTouchable)
    {
        m_touchRecognizer->registerInteractiveObject(std::dynamic_pointer_cast<ieInteractiveObject>(ieDisplayObject::shared_from_this()));
    } else if(m_touchRecognizer != nullptr){
        m_touchRecognizer->unregisterInteractiveObject(std::dynamic_pointer_cast<ieInteractiveObject>(ieDisplayObject::shared_from_this()));
    }
}

bool ieInteractiveObject::isTouchable(void) const
{
    return m_isTouchable;
}