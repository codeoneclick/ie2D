//
//  ieColorTransformation.cpp
//  ieCore
//
//  Created by Sergey Sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieColorTransformation.h"

ieColorTransformation::ieColorTransformation(f32 redMultiplier,
                                             i16 redOffset,
                                             f32 greenMultiplier,
                                             i16 greenOffset,
                                             f32 blueMultiplier,
                                             i16 blueOffset,
                                             f32 alphaMultiplier,
                                             i16 alphaOffset) :
m_redMultiplier(redMultiplier),
m_redOffset(redOffset),
m_greenMultiplier(greenMultiplier),
m_greenOffset(greenOffset),
m_blueMultiplier(blueMultiplier),
m_blueOffset(blueOffset),
m_alphaMultiplier(alphaMultiplier),
m_alphaOffset(alphaOffset)
{
    m_description = "ieColorTransformation";
}

ieColorTransformation::~ieColorTransformation(void)
{
    
}

f32 ieColorTransformation::getRedMultiplier(void)
{
    return m_redMultiplier;
}

i16 ieColorTransformation::getRedOffset(void)
{
    return m_redOffset;
}

f32 ieColorTransformation::getGreenMultiplier(void)
{
    return m_greenMultiplier;
}

i16 ieColorTransformation::getGreenOffset(void)
{
    return m_greenOffset;
}

f32 ieColorTransformation::getBlueMultiplier(void)
{
    return m_blueMultiplier;
}

i16 ieColorTransformation::getBlueOffset(void)
{
    return m_blueOffset;
}

f32 ieColorTransformation::getAlphaMultiplier(void)
{
    return m_alphaMultiplier;
}

i16 ieColorTransformation::getAlphaOffset(void)
{
    return m_alphaOffset;
}

void ieColorTransformation::setRedMultiplier(f32 redMultiplier)
{
    redMultiplier = glm::clamp(redMultiplier, 0.0f, 1.0f);
    m_redMultiplier = redMultiplier;
}

void ieColorTransformation::setRedOffset(i16 redOffset)
{
    redOffset = glm::clamp(redOffset, static_cast<i16>(-255), static_cast<i16>(255));
    m_redOffset = redOffset;
}

void ieColorTransformation::setGreenMultiplier(f32 greenMultiplier)
{
    greenMultiplier = glm::clamp(greenMultiplier, 0.0f, 1.0f);
    m_greenMultiplier = greenMultiplier;
}

void ieColorTransformation::setGreenOffset(i16 greenOffset)
{
    greenOffset = glm::clamp(greenOffset, static_cast<i16>(-255), static_cast<i16>(255));
    m_greenOffset = greenOffset;
}

void ieColorTransformation::setBlueMultiplier(f32 blueMultiplier)
{
    blueMultiplier = glm::clamp(blueMultiplier, 0.0f, 1.0f);
    m_blueMultiplier = blueMultiplier;
}

void ieColorTransformation::setBlueOffset(i16 blueOffset)
{
    blueOffset = glm::clamp(blueOffset, static_cast<i16>(-255), static_cast<i16>(255));
    m_blueOffset = blueOffset;
}

void ieColorTransformation::setAlphaMultiplier(f32 alphaMultiplier)
{
    alphaMultiplier = glm::clamp(alphaMultiplier, 0.0f, 1.0f);
    m_alphaMultiplier = alphaMultiplier;
}

void ieColorTransformation::setAlphaOffset(i16 alphaOffset)
{
    alphaOffset = glm::clamp(alphaOffset, static_cast<i16>(-255), static_cast<i16>(255));
    m_alphaOffset = alphaOffset;
}