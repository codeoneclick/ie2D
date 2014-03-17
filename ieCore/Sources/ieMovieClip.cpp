//
//  ieMovieClip.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieMovieClip.h"
#include "ieColor.h"
#include "ieTexture.h"
#include "ieShader.h"
#include "ieSequence.h"
#include "ieResourceAccessor.h"

ieMovieClip::ieMovieClip(const glm::vec4& frame,
                         const std::string& filename,
                         const std::shared_ptr<ieColor>& color) :
ieSprite(frame, filename, color)
{
    m_description = "ieMovieClip";
}

ieMovieClip::~ieMovieClip(void)
{

}

void ieMovieClip::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    ieSprite::onUpdate(event);
}

void ieMovieClip::onDraw(const std::shared_ptr<ieEvent>& event)
{
    ieSprite::onDraw(event);
}

void ieMovieClip::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    ieSprite::onEnterFrame(event);
}

void ieMovieClip::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    ieSprite::onExitFrame(event);
}

void ieMovieClip::onAdded(const std::shared_ptr<ieEvent>& event)
{
    ieSprite::onAdded(event);
    m_spriteAnimationFrames.resize(m_sequence->getAnimationFrameCount());
    ieSpriteAnimationFrame spriteAnimationFrame = m_spriteAnimationFrames[0];
    for (ui32 index = 1; index < m_sequence->getAnimationFrameCount(); ++index)
    {
        ieSprite::createSpriteAnimationFrame(index, spriteAnimationFrame);
    }
}

void ieMovieClip::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieSprite::onRemoved(event);
}

void ieMovieClip::gotoAndStop(ui32 index)
{
    ieSprite::gotoAndStop(index);
}
