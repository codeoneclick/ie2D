//
//  ieTile.cpp
//  ieEngine
//
//  Created by sergey.sergeev on 3/28/14.
//  Copyright (c) 2014 sergey.sergeev. All rights reserved.
//

#include "ieTile.h"
#include "ieColor.h"
#include "ieTexture.h"
#include "ieShader.h"
#include "ieSequence.h"
#include "ieResourceAccessor.h"

ieTile::ieTile(const std::string& imageFilename,
               const glm::vec4& frame,
               const glm::vec4& texCoordFrame) :
ieSprite(frame, imageFilename)
{
    m_description = "ieTile";
    m_tilesetImageName = imageFilename;
    m_tileTexCoordFrame = texCoordFrame;
}

ieTile::~ieTile(void)
{

}

void ieTile::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    ieSprite::onUpdate(event);
}

void ieTile::onDraw(const std::shared_ptr<ieEvent>& event)
{
    ieSprite::onDraw(event);
}

void ieTile::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    ieSprite::onEnterFrame(event);
}

void ieTile::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    ieSprite::onExitFrame(event);
}

void ieTile::onAdded(const std::shared_ptr<ieEvent>& event)
{
    ieSprite::onAdded(event);
    glm::ivec2 textureSize = ieSprite::getSpriteElementTextureSize(m_tilesetImageName);
    ieDisplayObject::setTexCoordsFromFrame(m_tileTexCoordFrame, textureSize);
    /*static ui32 index = 0;
    ieSprite::saveToFile("image" + std::to_string(index) + ".png");
    index++;*/
}

void ieTile::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieSprite::onRemoved(event);
}
