//
//  ieTouchRecognizer.cpp
//  ieCore
//
//  Created by sergey.sergeev on 4/4/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieTouchRecognizer.h"
#include "ieInteractiveObject.h"
#include "ieEvent.h"
#include "ieShader.h"
#include "ieRenderTarget.h"

ieTouchRecognizer::ieTouchRecognizer(void) :
m_renderTarget(nullptr)
{
    
}

ieTouchRecognizer::~ieTouchRecognizer(void)
{
    m_interactiveObjects.clear();
}

void ieTouchRecognizer::setRenderTarget(const std::shared_ptr<ieRenderTarget> &renderTarget)
{
    m_renderTarget = renderTarget;
}

void ieTouchRecognizer::registerInteractiveObject(ieSharedInteractiveObjectRef interactiveObject)
{
    m_interactiveObjects.insert(interactiveObject);
}

void ieTouchRecognizer::unregisterInteractiveObject(ieSharedInteractiveObjectRef interactiveObject)
{
    m_interactiveObjects.erase(interactiveObject);
}

void ieTouchRecognizer::updateTouchMask(void)
{
    assert(m_renderTarget != nullptr);
    m_renderTarget->begin();
    m_renderTarget->clear();
    
    std::for_each(m_interactiveObjects.begin(), m_interactiveObjects.end(), [this](ieSharedInteractiveObjectRef iterator){
        
        std::shared_ptr<ieEvent> eventOnUpdateTouchMask = std::make_shared<ieEvent>(kEVENT_ON_UPDATE_TOUCH_MASK, iterator);
        iterator->dispatchEvent(eventOnUpdateTouchMask);

    });
    
    m_renderTarget->end();
    m_renderTarget->saveToFile("a_image.png");
}
