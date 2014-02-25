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
#include "ieStage.h"
#include "ieResourceAccessor.h"

ieDisplayObject::ieDisplayObject(const glm::vec4& frame) :
m_shape(nullptr),
m_shader(nullptr),
m_resourceAccessor(nullptr),
m_stage(nullptr),
m_frame(frame),
m_parent(nullptr)
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
    ieMaterial::bind();
    m_shape->bind(m_shader->getAttributes());
    m_shader->setVector4(m_color, E_SHADER_UNIFORM_VECTOR_COLOR);
    
    m_shape->draw();
    std::cout<<"ieDisplayObject::onDraw"<<std::endl;
    
    ieMaterial::unbind();
    m_shape->unbind(m_shader->getAttributes());
}

void ieDisplayObject::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    std::cout<<"ieDisplayObject::onEnterFrame"<<std::endl;
}

void ieDisplayObject::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    std::cout<<"ieDisplayObject::onExitFrame"<<std::endl;
}

void ieDisplayObject::onAdded(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::addEventListener(kEVENT_ON_UPDATE, m_functionOnUpdate);
    ieDisplayObject::addEventListener(kEVENT_ON_DRAW, m_functionOnDraw);
    ieDisplayObject::addEventListener(kEVENT_ON_ENTER_FRAME, m_functionOnEnterFrame);
    ieDisplayObject::addEventListener(kEVENT_ON_EXIT_FRAME, m_functionOnExitFrame);
    
    m_resourceAccessor = std::static_pointer_cast<ieResourceAccessor>(event->getObjectWithKey("resourceAccessor"));
    assert(m_resourceAccessor != nullptr);
    
    m_stage = std::static_pointer_cast<ieStage>(event->getObjectWithKey("stage"));
    assert(m_stage != nullptr);
    
    m_shader = m_resourceAccessor->getShader(shaderColorVertex, shaderColorFragment, shared_from_this());
    ieMaterial::setShader(m_shader);
    ieMaterial::setBlending(false);
    ieMaterial::setCulling(false);
    
    glm::vec4 frame = glm::vec4(((m_frame.x * 2.0f) / m_stage->m_frame.z) - 1.0f,
                                ((m_frame.y * 2.0f) / m_stage->m_frame.w) - 1.0f,
                                ((m_frame.z * 2.0f) / m_stage->m_frame.z) - 1.0f,
                                ((m_frame.w * 2.0f) / m_stage->m_frame.w) - 1.0f);
    m_shape = std::make_shared<ieShape>(frame);
    static f32 r = 0.0;
    m_color = glm::vec4(r, 1.0f, 1.0f, 1.0f);
    r++;
}

void ieDisplayObject::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::removeEventListener(kEVENT_ON_UPDATE, m_functionOnUpdate);
    ieDisplayObject::removeEventListener(kEVENT_ON_DRAW, m_functionOnDraw);
    ieDisplayObject::removeEventListener(kEVENT_ON_ENTER_FRAME, m_functionOnEnterFrame);
    ieDisplayObject::removeEventListener(kEVENT_ON_EXIT_FRAME, m_functionOnExitFrame);
    
    m_shader->removeOwner(shared_from_this());
    m_shader = nullptr;
    m_shape = nullptr;
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
