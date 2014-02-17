//
//  ieDisplayObject.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieDisplayObject.h"
#include "ieEvent.h"
#include "ieShape.h"
#include "ieShader.h"

ieDisplayObject::ieDisplayObject(void) :
m_shape(nullptr),
m_shader(nullptr)
{
    m_description = "ieDisplayObject";
    
    m_functionOnUpdate = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObject::onUpdate, this, std::placeholders::_1));
    m_functionOnDraw = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObject::onDraw, this, std::placeholders::_1));
    m_functionOnEnterFrame = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObject::onEnterFrame, this, std::placeholders::_1));
    m_functionOnExitFrame = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObject::onExitFrame, this, std::placeholders::_1));
    m_functionOnAdded = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObject::onAdded, this, std::placeholders::_1));
    m_functionOnRemoved = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObject::onRemoved, this, std::placeholders::_1));
    
    
    ieDisplayObject::addEventListener(kEVENT_ON_ADDED, m_functionOnAdded);
    ieDisplayObject::addEventListener(kEVENT_ON_REMOVED, m_functionOnRemoved);
}

ieDisplayObject::~ieDisplayObject(void)
{
    ieDisplayObject::removeEventListener(kEVENT_ON_ADDED, m_functionOnAdded);
    ieDisplayObject::removeEventListener(kEVENT_ON_REMOVED, m_functionOnRemoved);
}

void ieDisplayObject::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    
}

void ieDisplayObject::onDraw(const std::shared_ptr<ieEvent>& event)
{
    
}

void ieDisplayObject::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    ieMaterial::bind();
}

void ieDisplayObject::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    ieMaterial::unbind();
}

void ieDisplayObject::onAdded(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::addEventListener(kEVENT_ON_UPDATE, m_functionOnUpdate);
    ieDisplayObject::addEventListener(kEVENT_ON_DRAW, m_functionOnDraw);
    ieDisplayObject::addEventListener(kEVENT_ON_ENTER_FRAME, m_functionOnEnterFrame);
    ieDisplayObject::addEventListener(kEVENT_ON_EXIT_FRAME, m_functionOnExitFrame);
    
    m_shader = std::make_shared<ieShader>(shaderCommonVertex,
                                          shaderCommonFragment);
    ieMaterial::setShader(m_shader);
}

void ieDisplayObject::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::removeEventListener(kEVENT_ON_UPDATE, m_functionOnUpdate);
    ieDisplayObject::removeEventListener(kEVENT_ON_DRAW, m_functionOnDraw);
    ieDisplayObject::removeEventListener(kEVENT_ON_ENTER_FRAME, m_functionOnEnterFrame);
    ieDisplayObject::removeEventListener(kEVENT_ON_EXIT_FRAME, m_functionOnExitFrame);
    
    m_shader = nullptr;
    ieMaterial::setShader(nullptr);
}

void ieDisplayObject::applyFilter(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                 const glm::ivec4& sourceRectangle,
                 const glm::ivec2& destinationPoint,
                 std::shared_ptr<ieBitmapFilter> filter)
{
    
}

void ieDisplayObject::colorTransform(const glm::ivec4& sourceRectangle,
                    const std::shared_ptr<ieColorTransformation>& colorTransformation)
{
    
}

void ieDisplayObject::copyChannel(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                 const glm::ivec4& sourceRectangle,
                 const glm::ivec2& destinationPoint,
                 ui32 sourceChannel,
                 ui32 destinationChannel)
{
    
}

void ieDisplayObject::copyPixels(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
                const glm::ivec4& sourceRectangle,
                const glm::ivec2& destinationPoint)
{
    
}

void ieDisplayObject::copyPixelsToByteArray(const glm::ivec4& rectangle,
                           const std::vector<ui32>& data)
{
    
}

void ieDisplayObject::fillRect(const glm::ivec4& rectangle,
              ui32 color)
{
    
}

void ieDisplayObject::floodFill(f32 x,
               f32 y,
               ui32 color)
{
    
}

glm::ivec4 ieDisplayObject::generateFilterRectangle(const glm::ivec4& sourceRectangle,
                                   std::shared_ptr<ieBitmapFilter> filter)
{
    return glm::ivec4(0.0f, 0.0f, 0.0f, 0.0f);
}

glm::ivec4 ieDisplayObject::getColorBoundsRect(ui32 color,
                              bool findColor)
{
    return glm::ivec4(0.0f, 0.0f, 0.0f, 0.0f);
}

ui32 ieDisplayObject::getPixel(ui32 x,
              ui32 y)
{
    return 0;
}

std::vector<ui32> ieDisplayObject::getPixels(const glm::ivec4& sourceRectangle)
{
    return std::vector<ui32>();
}

bool ieDisplayObject::hitTest(const glm::ivec4& rectangle)
{
    return false;
}

void ieDisplayObject::merge(const std::shared_ptr<ieIBitmapDrawable>& sourceBitmapData,
           const glm::ivec4& sourceRectangle,
           const glm::ivec2& destinationPoint,
           f32 redMultiplier,
           f32 greenMultiplier,
           f32 blueMultiplier,
           f32 alphaMultiplier)
{
    
}

void ieDisplayObject::noise(i32 randomSeed,
           ui32 low,
           ui32 high,
           bool grayScale)
{
    
}

void ieDisplayObject::perlinNoise(f32 baseX,
                 f32 baseY,
                 ui32 numOctaves,
                 i32 randomSeed,
                 bool stitch,
                 bool fractalNoise,
                 bool grayScale)
{
    
}

void ieDisplayObject::lock(void)
{
    
}

void ieDisplayObject::unlock(void)
{
    
}

void ieDisplayObject::setPixel(ui32 x, ui32 y, ui32 color)
{
    
}

void ieDisplayObject::setPixels(const glm::ivec4& rectangle, const std::vector<ui32>& data)
{
    
}
