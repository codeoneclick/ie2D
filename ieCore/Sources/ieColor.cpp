//
//  ieColor.cpp
//  ieCore
//
//  Created by Sergey Sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieColor.h"

ieColor::ieColor(ui8 redChannel, ui8 greenChannel, ui8 blueChannel, ui8 alphaChannel) :
ieColorTransformation()
{
    m_description = "ieColor";
    m_color.m_redChannel = redChannel;
    m_color.m_greenChannel = greenChannel;
    m_color.m_blueChannel = blueChannel;
    m_color.m_alphaChannel = alphaChannel;
}

ieColor::ieColor(ui32 hexColor)
{
    m_description = "ieColor";
    m_color.m_hexColor = hexColor;
}

ieColor::~ieColor(void)
{
    
}

ui8 ieColor::getRedChannel(void)
{
    return m_color.m_redChannel;
}

ui8 ieColor::getGreenChannel(void)
{
    return m_color.m_greenChannel;
}

ui8 ieColor::getBlueChannel(void)
{
    return m_color.m_blueChannel;
}

ui8 ieColor::getAlphaChannel(void)
{
    return m_color.m_alphaChannel;
}

ui32 ieColor::getHexColor(void)
{
    return m_color.m_hexColor;
}

void ieColor::setRedChannel(ui8 redChannel)
{
    m_color.m_redChannel = redChannel;
    ieColor::updateRedChannel();
}

void ieColor::setGreenChannel(ui8 greenChannel)
{
    m_color.m_greenChannel = greenChannel;
    ieColor::updateGreenChannel();
}

void ieColor::setBlueChannel(ui8 blueChannel)
{
    m_color.m_blueChannel = blueChannel;
    ieColor::updateBlueChannel();
}

void ieColor::setAplhaChannel(ui8 alphaChannel)
{
    m_color.m_alphaChannel = alphaChannel;
    ieColor::updateAlphaChannel();
}

void ieColor::setHexColor(ui32 hexColor)
{
    m_color.m_hexColor = hexColor;
    ieColor::updateRedChannel();
    ieColor::updateGreenChannel();
    ieColor::updateBlueChannel();
    ieColor::updateAlphaChannel();
}

void ieColor::updateRedChannel(void)
{
    i16 color = m_color.m_redChannel;
    color *= m_redMultiplier;
    color = glm::clamp(color + m_redOffset, 0, 255);
    m_color.m_redChannel = static_cast<ui8>(color);
}

void ieColor::updateGreenChannel(void)
{
    i16 color = m_color.m_greenChannel;
    color *= m_greenMultiplier;
    color = glm::clamp(color + m_greenOffset, 0, 255);
    m_color.m_greenChannel = static_cast<ui8>(color);
}

void ieColor::updateBlueChannel(void)
{
    i16 color = m_color.m_blueChannel;
    color *= m_blueMultiplier;
    color = glm::clamp(color + m_blueOffset, 0, 255);
    m_color.m_blueChannel = static_cast<ui8>(color);
}

void ieColor::updateAlphaChannel(void)
{
    i16 color = m_color.m_alphaChannel;
    color *= m_alphaMultiplier;
    color = glm::clamp(color + m_alphaOffset, 0, 255);
    m_color.m_alphaChannel = static_cast<ui8>(color);
}

void ieColor::setRedMultiplier(f32 redMultiplier)
{
    ieColorTransformation::setRedMultiplier(redMultiplier);
    ieColor::updateRedChannel();
}

void ieColor::setRedOffset(i16 redOffset)
{
    ieColorTransformation::setRedOffset(redOffset);
    ieColor::updateRedChannel();
}

void ieColor::setGreenMultiplier(f32 greenMultiplier)
{
    ieColorTransformation::setGreenMultiplier(greenMultiplier);
    ieColor::updateGreenChannel();
}

void ieColor::setGreenOffset(i16 greenOffset)
{
    ieColorTransformation::setGreenOffset(greenOffset);
    ieColor::updateGreenChannel();
}

void ieColor::setBlueMultiplier(f32 blueMultiplier)
{
    ieColorTransformation::setBlueMultiplier(blueMultiplier);
    ieColor::updateBlueChannel();
}

void ieColor::setBlueOffset(i16 blueOffset)
{
    ieColorTransformation::setBlueOffset(blueOffset);
    ieColor::updateBlueChannel();
}

void ieColor::setAlphaMultiplier(f32 alphaMultiplier)
{
    ieColorTransformation::setAlphaMultiplier(alphaMultiplier);
    ieColor::updateAlphaChannel();
}

void ieColor::setAlphaOffset(i16 alphaOffset)
{
    ieColorTransformation::setAlphaOffset(alphaOffset);
    ieColor::updateAlphaChannel();
}


