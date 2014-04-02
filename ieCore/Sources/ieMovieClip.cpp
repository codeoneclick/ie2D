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
ieSprite(frame, filename, color),
m_animationName(""),
m_currentAnimationFrameIndex(0),
m_isLooped(false),
m_isStoped(true),
m_namedAnimationStartFrameIndex(0),
m_namedAnimationEndFrameIndex(0)
{
    m_description = "ieMovieClip";
}

ieMovieClip::~ieMovieClip(void)
{

}

void ieMovieClip::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    if(!m_isStoped)
    {
        if(!ieMovieClip::gotoNextFrame() && m_isLooped)
        {
            ieMovieClip::invokeAnimation();
        }
    }
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

void ieMovieClip::invokeAnimation(void)
{
    if(m_animationName.length() == 0)
    {
        m_currentAnimationFrameIndex = 0;
        m_namedAnimationStartFrameIndex = 0;
        m_namedAnimationEndFrameIndex = m_spriteAnimationFrames.size();
    } else {
        
    }
}

bool ieMovieClip::gotoNextFrame(void)
{
    m_currentAnimationFrameIndex++;
    if(m_currentAnimationFrameIndex < m_namedAnimationEndFrameIndex)
    {
        ieSprite::gotoAndStop(m_currentAnimationFrameIndex);
        return true;
    } else {
        return false;
    }
}

void ieMovieClip::gotoAndStop(ui32 index)
{
    ieSprite::gotoAndStop(index);
    m_isStoped = true;
}

void ieMovieClip::gotoAndPlay(bool isLooped, const std::string& animationName)
{
    m_isLooped = isLooped;
    m_animationName = animationName;
    m_isStoped = false;
}
