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
#include "ieVertexBuffer.h"
#include "ieColor.h"

ieDisplayObject::ieDisplayObject(const glm::vec4& frame) :
m_shape(nullptr),
m_shader(nullptr),
m_resourceAccessor(nullptr),
m_stage(nullptr),
m_camera(nullptr),
m_frame(frame),
m_parent(nullptr),
m_modelview(1.0f),
m_position(glm::vec2(0.0f, 0.0f)),
m_rotation(0.0f),
m_scale(1.0f, 1.0f),
m_pivot(0.0f),
m_color(std::make_shared<ieColor>(255, 255, 255, 255)),
m_drawMode(E_DRAW_OBJECT_MODE_V2C4)
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

void ieDisplayObject::setTextureFrame(const glm::vec4 &frame)
{
    ieVertex *vertexData = m_shape->getVertexBuffer()->lock();
    vertexData[0].m_texcoord = ieVertexBuffer::compressVec2(glm::vec2(frame.x, frame.y));
    vertexData[1].m_texcoord = ieVertexBuffer::compressVec2(glm::vec2(frame.x, frame.w));
    vertexData[2].m_texcoord = ieVertexBuffer::compressVec2(glm::vec2(frame.z, frame.y));
    vertexData[3].m_texcoord = ieVertexBuffer::compressVec2(glm::vec2(frame.z, frame.w));
    m_shape->getVertexBuffer()->unlock();
}

void ieDisplayObject::setShapeFrame(const glm::vec4 &frame)
{
    ieVertex* vertexData = m_shape->getVertexBuffer()->lock();
    vertexData[0].m_position = glm::vec2(frame.x, frame.y);
    vertexData[1].m_position = glm::vec2(frame.x, frame.w);
    vertexData[2].m_position = glm::vec2(frame.z, frame.y);
    vertexData[3].m_position = glm::vec2(frame.z, frame.w);
    m_shape->getVertexBuffer()->unlock();
}

void ieDisplayObject::setColor(const std::shared_ptr<ieColor> &color)
{
    ieVertex *vertexData = m_shape->getVertexBuffer()->lock();
    for(ui32 i = 0; i < m_shape->getVertexBuffer()->getSize(); ++i)
    {
        vertexData[i].m_color = glm::ivec4(color->getRedChannel(),
                                           color->getGreenChannel(),
                                           color->getBlueChannel(),
                                           color->getAlphaChannel());
    }
    m_shape->getVertexBuffer()->unlock();
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
}

glm::vec2 ieDisplayObject::getPivot(void) const
{
    return m_pivot;
}

void ieDisplayObject::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    std::shared_ptr<ieDisplayObjectContainer> parent = m_parent;
    glm::mat4x4 parentMatrix(1.0f);
    while(parent != nullptr)
    {
        glm::vec2 position = parent->m_position;
        f32 rotation = parent->m_rotation;
        glm::vec4 frame = parent->m_frame;
        glm::mat4x4 forwardTranslationMatrix = glm::translate(glm::mat4x4(1.0f), glm::vec3(position.x + frame.z * 0.5f,
                                                                                           position.y + frame.w * 0.5f, 0.0f));
        glm::mat4x4 rotationMatrix = glm::rotate(glm::mat4x4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4x4 backwardTranslationMatrix = glm::translate(glm::mat4x4(1.0f), glm::vec3(-frame.z * 0.5f,
                                                                                            -frame.w * 0.5f, 0.0f));
        parentMatrix = parentMatrix * forwardTranslationMatrix * rotationMatrix * backwardTranslationMatrix;
        
        parent = parent->m_parent;
    }
    
    glm::mat4x4 translationMatrix = glm::translate(glm::mat4x4(1.0f), glm::vec3(m_position.x + m_frame.z * 0.5f,
                                                                                m_position.y + m_frame.w * 0.5f, 0.0f));
    glm::mat4x4 rotationMatrix = glm::rotate(glm::mat4x4(1.0f), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4x4 scaleMatrix = glm::scale(glm::mat4x4(1.0f), glm::vec3(m_frame.z, m_frame.w, 1.0));
    glm::mat4x4 customScaleMatrix = glm::scale(glm::mat4x4(1.0f), glm::vec3(m_scale.x, m_scale.y, 1.0f));
    glm::mat4x4 translationPivotMatrix = glm::translate(glm::mat4x4(1.0f), glm::vec3(-m_pivot.x, -m_pivot.y, 0.0f));
    m_modelview = parentMatrix * translationMatrix * rotationMatrix * translationPivotMatrix * customScaleMatrix* scaleMatrix;
}

void ieDisplayObject::onDraw(const std::shared_ptr<ieEvent>& event)
{
    assert(m_camera != nullptr);
    ieMaterial::bind();
    
    m_shader->setMatrix4x4(m_modelview, E_SHADER_UNIFORM_MODELVIEW);
    m_shader->setMatrix4x4(m_camera->getProjection(), E_SHADER_UNIFORM_PROJECTION);
    m_shape->bind(m_shader->getAttributes());
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
    
    m_camera = std::static_pointer_cast<ieCamera>(event->getObjectWithKey("camera"));
    assert(m_camera != nullptr);
    
    ieMaterial::setBlending(true);
    ieMaterial::setBlendingFunctionSource(GL_SRC_ALPHA);
    ieMaterial::setBlendingFunctionDestination(GL_ONE_MINUS_SRC_ALPHA);
    ieMaterial::setCulling(false);
    ieMaterial::setDepthTest(false);
    
    switch (m_drawMode) {
        case E_DRAW_OBJECT_MODE_V2C4:
        {
            m_shader = m_resourceAccessor->getShader(ieShaderV2C4_vert, ieShaderV2C4_frag, shared_from_this());
            ieMaterial::setShader(m_shader);
        }
            break;
            
        case E_DRAW_OBJECT_MODE_V2T2C4:
        {
            m_shader = m_resourceAccessor->getShader(ieShaderV2T2C4_vert, ieShaderV2T2C4_frag, shared_from_this());
            ieMaterial::setShader(m_shader);
        }
            break;
            
        case E_DRAW_OBJECT_MODE_CUSTOM:
        {
            std::cout<<"custom draw mode"<<std::endl;
        }
            break;
            
        default:
            break;
    }
    
    m_shape = std::make_shared<ieShape>(glm::vec4(-0.5f, 0.5f, 0.5f, -0.5f));
    ieDisplayObject::setColor(m_color);
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
