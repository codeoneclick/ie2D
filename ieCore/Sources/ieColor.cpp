//
//  ieColor.cpp
//  ieCore
//
//  Created by Sergey Sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieColor.h"

ieColor::ieColor(ui8 redChannel, ui8 greenChannel, ui8 blueChannel, ui8 alphaChannel)
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
}

void ieColor::setGreenChannel(ui8 greenChannel)
{
    m_color.m_greenChannel = greenChannel;
}

void ieColor::setBlueChannel(ui8 blueChannel)
{
    m_color.m_blueChannel = blueChannel;
}

void ieColor::setAplhaChannel(ui8 alphaChannel)
{
    m_color.m_alphaChannel = alphaChannel;
}

void ieColor::setHexColor(ui32 hexColor)
{
    m_color.m_hexColor = hexColor;
}