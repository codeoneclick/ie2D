//
//  ieMask.cpp
//  ieCore
//
//  Created by sergey.sergeev on 3/21/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieMask.h"
#include "ieDisplayObject.h"

ieMask::ieMask(const glm::vec4& frame,
               const std::string& filename) :
ieDisplayObject(frame),
m_texture(nullptr),
m_imageFilename(filename)
{
    
}

ieMask::~ieMask(void)
{
    
}

void ieMask::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onUpdate(event);
}

void ieMask::onDraw(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onDraw(event);
}

void ieMask::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onEnterFrame(event);
}

void ieMask::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onExitFrame(event);
}

void ieMask::onAdded(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onAdded(event);
}

void ieMask::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onRemoved(event);
}