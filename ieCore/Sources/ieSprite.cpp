//
//  ieSprite.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieSprite.h"
#include "ieColor.h"
#include "ieTexture.h"
#include "ieShader.h"
#include "ieResourceAccessor.h"

ieSprite::ieSprite(const glm::vec4& frame,
                   const std::shared_ptr<ieColor>& color) :
ieDisplayObjectContainer(frame),
m_texture(nullptr)
{
    m_description = "ieSprite";
    m_color = color;
    m_filename = "";
}

ieSprite::ieSprite(const glm::vec4& frame,
                   const std::string& filename,
                   const std::shared_ptr<ieColor>& color) :
ieDisplayObjectContainer(frame),
m_texture(nullptr)
{
    m_description = "ieSprite";
    m_color = color != nullptr ? color : std::make_shared<ieColor>(255, 255, 255, 255);
    m_filename = filename;
    m_drawMode = E_DRAW_OBJECT_MODE_V2T2C4;
}

ieSprite::~ieSprite(void)
{
    
}

void ieSprite::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onUpdate(event);
}

void ieSprite::onDraw(const std::shared_ptr<ieEvent>& event)
{
    ieMaterial::bind();
    ieMaterial::setTexture(m_texture, E_SHADER_SAMPLER_01);
    ieDisplayObjectContainer::onDraw(event);
}

void ieSprite::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onEnterFrame(event);
}

void ieSprite::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onExitFrame(event);
}

void ieSprite::onAdded(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onAdded(event);
    if(m_drawMode == E_DRAW_OBJECT_MODE_V2T2C4)
    {
        m_texture = m_resourceAccessor->getTexture(m_filename);
    }
}

void ieSprite::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onRemoved(event);
}
