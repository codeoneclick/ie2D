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
#include "ieCamera.h"
#include "ieResourceAccessor.h"
#include "ieBatchMgr.h"
#include "ieColor.h"
#include "ieVertexBuffer.h"

ieDisplayObject::ieDisplayObject(const glm::vec4& frame) :
m_shape(nullptr),
m_resourceAccessor(nullptr),
m_batchMgr(nullptr),
m_stage(nullptr),
m_camera(nullptr),
m_frame(frame),
m_parent(nullptr),
m_localTransformation(1.0f),
m_externalTransformation(1.0f),
m_position(glm::vec2(0.0f, 0.0f)),
m_rotation(0.0f),
m_scale(1.0f, 1.0f),
m_pivot(0.0f),
m_texCoord(0.0f, 0.0f, 1.0f, 1.0f),
m_visible(true),
m_active(true),
m_batched(false),
m_zIndex(0)
{
    m_description = "ieDisplayObject";
    m_functionOnUpdate = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObject::onUpdate,
                                                                               this, std::placeholders::_1));
    m_functionOnDraw = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObject::onDraw,
                                                                             this, std::placeholders::_1));
    m_functionOnEnterFrame = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObject::onEnterFrame,
                                                                                   this, std::placeholders::_1));
    m_functionOnExitFrame = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObject::onExitFrame,
                                                                                  this, std::placeholders::_1));
    m_functionOnAdded = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObject::onAdded,
                                                                              this, std::placeholders::_1));
    m_functionOnRemoved = std::make_shared<ieEventDispatcherFunction>(std::bind(&ieDisplayObject::onRemoved,
                                                                                this, std::placeholders::_1));
    
    ieDisplayObject::addEventListener(kEVENT_ON_ADDED, m_functionOnAdded);
    ieDisplayObject::addEventListener(kEVENT_ON_REMOVED, m_functionOnRemoved);
}

ieDisplayObject::~ieDisplayObject(void)
{
    ieDisplayObject::removeEventListener(kEVENT_ON_ADDED, m_functionOnAdded);
    ieDisplayObject::removeEventListener(kEVENT_ON_REMOVED, m_functionOnRemoved);
}

glm::vec4 ieDisplayObject::createShapePositionAttributes(void)
{
    glm::vec2 size = glm::vec2(m_frame.z - m_pivot.x, m_frame.w - m_pivot.y);
    glm::vec2 position = glm::vec2(size.x - m_frame.z, size.y - m_frame.w);
    return glm::vec4(position.x, size.y, size.x, position.y);
}

void ieDisplayObject::updateShapePositionAttributes(const std::shared_ptr<ieShape>& shape)
{
    glm::vec4 frame = ieDisplayObject::createShapePositionAttributes();
    ieVertex* vertexData = shape->getVertexBuffer()->lock();
    vertexData[0].m_position = glm::vec2(frame.x, frame.z);
    vertexData[1].m_position = glm::vec2(frame.x, frame.w);
    vertexData[2].m_position = glm::vec2(frame.y, frame.z);
    vertexData[3].m_position = glm::vec2(frame.y, frame.w);
    shape->getVertexBuffer()->unlock();
}

void ieDisplayObject::updateShapeTexcoordAttributes(const std::shared_ptr<ieShape>& shape)
{
    ieVertex *vertexData = shape->getVertexBuffer()->lock();
    vertexData[0].m_texcoord = ieVertexBuffer::compressVec2(glm::vec2(m_texCoord.x, m_texCoord.y));
    vertexData[1].m_texcoord = ieVertexBuffer::compressVec2(glm::vec2(m_texCoord.x, m_texCoord.w));
    vertexData[2].m_texcoord = ieVertexBuffer::compressVec2(glm::vec2(m_texCoord.z, m_texCoord.y));
    vertexData[3].m_texcoord = ieVertexBuffer::compressVec2(glm::vec2(m_texCoord.z, m_texCoord.w));
    shape->getVertexBuffer()->unlock();
}

void ieDisplayObject::updateShapeColorAttributes(const std::shared_ptr<ieShape>& shape)
{
    assert(m_material != nullptr);
    
    ieVertex *vertexData = shape->getVertexBuffer()->lock();
    for(ui32 i = 0; i < shape->getVertexBuffer()->getSize(); ++i)
    {
        vertexData[i].m_color = glm::ivec4(m_material->getColor()->getRedChannel(),
                                           m_material->getColor()->getGreenChannel(),
                                           m_material->getColor()->getBlueChannel(),
                                           m_material->getColor()->getAlphaChannel());
    }
    shape->getVertexBuffer()->unlock();
}

void ieDisplayObject::setPosition(const glm::vec2& position)
{
    m_position = position;
}

glm::vec2 ieDisplayObject::getPosition(void) const
{
    return m_position;
}

void ieDisplayObject::setRotation(f32 rotation)
{
    m_rotation = rotation;
}

f32 ieDisplayObject::getRotation(void) const
{
    return m_rotation;
}

void ieDisplayObject::setScale(const glm::vec2& scale)
{
    m_scale = scale;
}

glm::vec2 ieDisplayObject::getScale(void) const
{
    return m_scale;
}

void ieDisplayObject::setPivot(const glm::vec2 &pivot)
{
    m_pivot = pivot;
    if(m_shape != nullptr)
    {
        ieDisplayObject::updateShapePositionAttributes(m_shape);
    }
}

glm::vec2 ieDisplayObject::getPivot(void) const
{
    return m_pivot;
}

ui32 ieDisplayObject::getZIndex(void)
{
    return m_zIndex;
}

void ieDisplayObject::setZIndex(ui32 zIndex)
{
    m_zIndex = zIndex;
}

void ieDisplayObject::setActive(bool value)
{
    m_active = value;
}

bool ieDisplayObject::isActive(void) const
{
    return m_active;
}

void ieDisplayObject::setVisible(bool value)
{
    m_visible = value;
}

bool ieDisplayObject::isVisible(void) const
{
    return m_visible;
}

void ieDisplayObject::setBatched(bool value)
{
    m_batched = value;
}

bool ieDisplayObject::isBatched(void) const
{
    return m_batched;
}

void ieDisplayObject::setTexCoordsFromFrame(const glm::vec4& texCoordsFrame, const glm::ivec2& textureSize)
{
    m_texCoord = glm::vec4(static_cast<f32>(texCoordsFrame.x) / static_cast<f32>(textureSize.x),
                           1 - static_cast<f32>(texCoordsFrame.y + texCoordsFrame.w) / static_cast<f32>(textureSize.y),
                           static_cast<f32>(texCoordsFrame.x + texCoordsFrame.z) / static_cast<f32>(textureSize.x),
                           1 - static_cast<f32>(texCoordsFrame.y) / static_cast<f32>(textureSize.y));
    if(m_shape != nullptr)
    {
        ieDisplayObject::updateShapeTexcoordAttributes(m_shape);
    }
}

void ieDisplayObject::setupShader(const std::string& vsSourceCode,
                                  const std::string& fsSourceCode)
{
    assert(m_material != nullptr);
    if(m_material->getShader() != nullptr)
    {
        m_material->getShader()->removeOwner(ieDisplayObject::shared_from_this());
        m_material->setShader(nullptr);
    }
    ieSharedShader shader = m_resourceAccessor->getShader(vsSourceCode,
                                                          fsSourceCode,
                                                          ieDisplayObject::shared_from_this());
    m_material->setShader(shader);
}

std::shared_ptr<ieDisplayObjectContainer> ieDisplayObject::getParent(void) const
{
    return m_parent;
}

void ieDisplayObject::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    std::shared_ptr<ieDisplayObjectContainer> parent = m_parent;
    glm::mat4x4 parentMatrix(1.0f);
    while(parent != nullptr)
    {
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f),
                                                     glm::vec3(parent->m_position.x,
                                                               parent->m_position.y, 0.0f));
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f),
                                               glm::radians(parent->m_rotation),
                                               glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f),
                                           glm::vec3(parent->m_scale.x,
                                                     parent->m_scale.y,
                                                     0.0f));
        parentMatrix = parentMatrix * translationMatrix * rotationMatrix * scaleMatrix;
        parent = parent->m_parent;
    }
    
    glm::mat4x4 translationMatrix = glm::translate(glm::mat4x4(1.0f),
                                                   glm::vec3(m_position.x,
                                                             m_position.y, 0.0f));
    glm::mat4x4 rotationMatrix = glm::rotate(glm::mat4x4(1.0f),
                                             glm::radians(m_rotation),
                                             glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4x4 scaleMatrix = glm::scale(glm::mat4x4(1.0f),
                                         glm::vec3(m_scale.x,
                                                   m_scale.y, 1.0f));
    
    m_localTransformation = parentMatrix * translationMatrix * rotationMatrix * scaleMatrix * m_externalTransformation;
}

void ieDisplayObject::onDraw(const std::shared_ptr<ieEvent>& event)
{
    if(m_visible && m_active)
    {
        if(m_batched)
        {
            assert(m_batchMgr != nullptr);
            m_batchMgr->batch(this, m_shape, m_localTransformation);
        } else {
            assert(m_camera != nullptr);
            ieMaterial::bind();
            
            m_shader->setMatrix4x4(m_localTransformation, E_SHADER_UNIFORM_MODELVIEW);
            m_shader->setMatrix4x4(m_camera->getProjection(), E_SHADER_UNIFORM_PROJECTION);
            m_shape->bind(m_shader->getAttributes());
            m_shape->draw();
            
            ieMaterial::unbind();
            m_shape->unbind(m_shader->getAttributes());
        }
    }
}

void ieDisplayObject::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    
}

void ieDisplayObject::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    
}

void ieDisplayObject::onAdded(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::addEventListener(kEVENT_ON_UPDATE, m_functionOnUpdate);
    ieDisplayObject::addEventListener(kEVENT_ON_DRAW, m_functionOnDraw);
    ieDisplayObject::addEventListener(kEVENT_ON_ENTER_FRAME, m_functionOnEnterFrame);
    ieDisplayObject::addEventListener(kEVENT_ON_EXIT_FRAME, m_functionOnExitFrame);
    
    m_resourceAccessor = std::static_pointer_cast<ieResourceAccessor>(event->getObjectWithKey("resourceAccessor"));
    assert(m_resourceAccessor != nullptr);
    
    m_batchMgr = std::static_pointer_cast<ieBatchMgr>(event->getObjectWithKey("batchMgr"));
    assert(m_batchMgr != nullptr);
    
    m_stage = std::static_pointer_cast<ieStage>(event->getObjectWithKey("stage"));
    assert(m_stage != nullptr);
    
    m_camera = std::static_pointer_cast<ieCamera>(event->getObjectWithKey("camera"));
    assert(m_camera != nullptr);
    
    ieMaterial::setBlending(true);
    ieMaterial::setBlendingFunctionSource(GL_SRC_ALPHA);
    ieMaterial::setBlendingFunctionDestination(GL_ONE_MINUS_SRC_ALPHA);
    ieMaterial::setCulling(false);
    ieMaterial::setDepthTest(false);
    ieMaterial::setDepthMask(false);
    
    glm::vec4 frame = ieDisplayObject::createShapePositionAttributes();
    m_shape = std::make_shared<ieShape>(frame);
    ieDisplayObject::updateShapeTexcoordAttributes(m_shape);
    ieDisplayObject::updateShapeColorAttributes(m_shape);
}

void ieDisplayObject::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::removeEventListener(kEVENT_ON_UPDATE, m_functionOnUpdate);
    ieDisplayObject::removeEventListener(kEVENT_ON_DRAW, m_functionOnDraw);
    ieDisplayObject::removeEventListener(kEVENT_ON_ENTER_FRAME, m_functionOnEnterFrame);
    ieDisplayObject::removeEventListener(kEVENT_ON_EXIT_FRAME, m_functionOnExitFrame);
    
    m_shader->removeOwner(ieObject::shared_from_this());
    m_shader = nullptr;
    m_shape = nullptr;
    ieMaterial::setShader(nullptr);
}

#pragma mark -
#pragma mark ieIMaterial - setters

void ieDisplayObject::setCulling(bool value)
{
    assert(m_material != nullptr);
    m_material->setCulling(value);
}

void ieDisplayObject::setCullingMode(GLenum value)
{
    assert(m_material != nullptr);
    m_material->setCullingMode(value);
}

void ieDisplayObject::setBlending(bool value)
{
    assert(m_material != nullptr);
    m_material->setBlending(value);
}

void ieDisplayObject::setBlendingFunctionSource(GLenum value)
{
    assert(m_material != nullptr);
    m_material->setBlendingFunctionSource(value);
}

void ieDisplayObject::setBlendingFunctionDestination(GLenum value)
{
    assert(m_material != nullptr);
    m_material->setBlendingFunctionDestination(value);
}

void ieDisplayObject::setDepthTest(bool value)
{
    assert(m_material != nullptr);
    m_material->setDepthTest(value);
}

void ieDisplayObject::setDepthMask(bool value)
{
    assert(m_material != nullptr);
    m_material->setDepthMask(value);
}

void ieDisplayObject::setShader(ieSharedShaderRef shader)
{
    assert(m_material != nullptr);
    m_material->setShader(shader);
}

void ieDisplayObject::setTexture(ieSharedTextureRef texture,
                                 E_SHADER_SAMPLER sampler)
{
    assert(m_material != nullptr);
    m_material->setTexture(texture, sampler);
}

void ieDisplayObject::setColor(ieSharedColorRef color)
{
    assert(m_material != nullptr);
    m_material->setColor(color);
    if (m_shape != nullptr)
    {
        ieDisplayObject::updateShapeColorAttributes(m_shape);
    }
}

#pragma mark -
#pragma mark ieIMaterial - getters

bool ieDisplayObject::isCulling(void) const
{
    assert(m_material != nullptr);
    return m_material->isCulling();
}

GLenum ieDisplayObject::getCullingMode(void) const
{
    assert(m_material != nullptr);
    return m_material->getCullingMode();
}

bool ieDisplayObject::isBlending(void) const
{
    assert(m_material != nullptr);
    return m_material->isBlending();
}

GLenum ieDisplayObject::getBlendingFunctionSource(void) const
{
    assert(m_material != nullptr);
    return m_material->getBlendingFunctionSource();
}

GLenum ieDisplayObject::getBlendingFunctionDestination(void) const
{
    assert(m_material != nullptr);
    return m_material->getBlendingFunctionDestination();
}

bool ieDisplayObject::isDepthTest(void) const
{
    assert(m_material != nullptr);
    return m_material->isDepthTest();
}

bool ieDisplayObject::isDepthMask(void) const
{
    assert(m_material != nullptr);
    return m_material->isDepthMask();
}

ieSharedShader ieDisplayObject::getShader(void) const
{
    assert(m_material != nullptr);
    return m_material->getShader();
}

ieSharedTexture ieDisplayObject::getTexture(E_SHADER_SAMPLER sampler) const
{
    assert(m_material != nullptr);
    return m_material->getTexture(sampler);
}

ieSharedColor ieDisplayObject::getColor(void) const
{
    assert(m_material != nullptr);
    return m_material->getColor();
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
