//
//  ieSprite.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieSprite.h"
#include "ieColor.h"
#include "ieTexture.h"
#include "ieShader.h"
#include "ieSequence.h"
#include "ieResourceAccessor.h"

ieSprite::ieSprite(const glm::vec4& frame,
                   const std::shared_ptr<ieColor>& color) :
ieDisplayObjectContainer(frame),
m_texture(nullptr),
m_imageFilename(""),
m_sequenceFilename("")
{
    m_description = "ieSprite";
    m_color = color;
}

ieSprite::ieSprite(const glm::vec4& frame,
                   const std::string& filename,
                   const std::shared_ptr<ieColor>& color) :
ieDisplayObjectContainer(frame),
m_texture(nullptr)
{
    m_description = "ieSprite";
    m_color = color != nullptr ? color : std::make_shared<ieColor>(255, 255, 255, 255);
    if(filename.find(".png") != std::string::npos)
    {
        m_imageFilename = filename;
        m_sequenceFilename = "";
        m_drawMode = E_DRAW_OBJECT_MODE_V2T2C4;
    } else if(filename.find(".json") != std::string::npos ||
              filename.find(".xml") != std::string::npos)
    {
        m_sequenceFilename = filename;
        m_imageFilename = "";
        m_drawMode = E_DRAW_OBJECT_MODE_V2C4;
    } else {
        assert(false);
    }
    
}

ieSprite::~ieSprite(void)
{
    
}

void ieSprite::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onUpdate(event);
}

void ieSprite::onDraw(const std::shared_ptr<ieEvent>& event)
{
    ieMaterial::bind();
    ieMaterial::setTexture(m_texture, E_SHADER_SAMPLER_01);
    ieDisplayObjectContainer::onDraw(event);
}

void ieSprite::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onEnterFrame(event);
}

void ieSprite::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onExitFrame(event);
}

void ieSprite::onAdded(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onAdded(event);
    if(m_imageFilename.length() != 0 &&
       m_imageFilename.find(".png") != std::string::npos)
    {
        m_texture = m_resourceAccessor->getTexture(m_imageFilename);
    }  else if(m_sequenceFilename.length() != 0 &&
               (m_sequenceFilename.find(".json") != std::string::npos ||
                m_sequenceFilename.find(".xml") != std::string::npos))
    {
        std::shared_ptr<ieColor> color = std::make_shared<ieColor>(255, 255, 255, 0);
        ieSprite::setColor(color);
        m_sequence = m_resourceAccessor->getSequence(m_sequenceFilename);
        size_t found = m_sequenceFilename.find_last_of("/\\");
        std::string path = m_sequenceFilename.substr(0, found);
        std::for_each(m_sequence->getSequenceTextures().begin(),
                      m_sequence->getSequenceTextures().end(),
                      [this, path](const std::pair<ui32, ieSequenceTexture>& iterator){
                          m_texture = m_resourceAccessor->getTexture(path + "/" + iterator.second.m_imageFilename);
                      });
        
        std::for_each(m_sequence->getSequenceElements().begin(),
                      m_sequence->getSequenceElements().end(),
                      [this, path](const std::pair<std::string, ieSequenceElement>& iterator)
                      {
                          ui32 sequenceTextureId = iterator.second.m_sequenceTextureId;
                          auto sequenceTexture = m_sequence->getSequenceTextures().find(sequenceTextureId);
                          assert(sequenceTexture != m_sequence->getSequenceTextures().end());
                          std::string imageFilename = sequenceTexture->second.m_imageFilename;
                          std::shared_ptr<ieSprite> sprite = std::make_shared<ieSprite>(glm::vec4(0, 0,
                                                                                                  iterator.second.m_size.x,
                                                                                                  iterator.second.m_size.y),
                                                                                        path + "/" + imageFilename);
                          
                          glm::vec4 textureCoords =
                          glm::vec4(static_cast<f32>(iterator.second.m_position.x) / static_cast<f32>(m_texture->getWidth()),
                                    1.0f - static_cast<f32>(iterator.second.m_position.y + iterator.second.m_size.y) / static_cast<f32>(m_texture->getHeight()),
                                    static_cast<f32>(iterator.second.m_position.x + iterator.second.m_size.x) / static_cast<f32>(m_texture->getWidth()),
                                    1.0f - static_cast<f32>(iterator.second.m_position.y) / static_cast<f32>(m_texture->getHeight()));
                          sprite->setTextureCoords(textureCoords);
                          sprite->setPivot(glm::vec2(iterator.second.m_pivot.x,
                                                     iterator.second.m_pivot.y));
                          m_uniqueSpriteElements.insert(std::make_pair(iterator.first, sprite));
                      });
        
        auto sequenceFrame = m_sequence->getSequenceFrames().find(1);
        assert(sequenceFrame != m_sequence->getSequenceFrames().end());
        
        std::vector<std::tuple<std::shared_ptr<ieSprite>, ui32, glm::vec2, f32, glm::vec2>> sprites;
        std::for_each((*sequenceFrame).second.m_states.begin(),
                      (*sequenceFrame).second.m_states.end(),
                      [this, path, &sprites](const std::pair<std::string, ieSequenceFrameState>& iterator)
                      {
                          std::string stateId = iterator.first;
                          auto sequenceAnimatedElement = m_sequence->getSequenceAnimatedElements().find(stateId);
                          assert(sequenceAnimatedElement != m_sequence->getSequenceAnimatedElements().end());
                          std::string sequenceElementId = sequenceAnimatedElement->second;
                          
                          auto spriteElement = m_uniqueSpriteElements.find(sequenceElementId);
                          assert(spriteElement != m_uniqueSpriteElements.end());
                          
                          glm::vec2 scale = glm::vec2(sqrtf((iterator.second.m_matrix.a * iterator.second.m_matrix.a) +
                                                            (iterator.second.m_matrix.c * iterator.second.m_matrix.c)),
                                                      sqrtf((iterator.second.m_matrix.b * iterator.second.m_matrix.b) +
                                                            (iterator.second.m_matrix.d * iterator.second.m_matrix.d)));
                          
                          scale.x *= iterator.second.m_matrix.a > 0.0f ? 1.0f : -1.0f;
                          scale.y *= iterator.second.m_matrix.d > 0.0f ? 1.0f : -1.0f;
                          
                          f32 sign = atanf(-iterator.second.m_matrix.c / iterator.second.m_matrix.a);
                          f32 radians  = acosf(iterator.second.m_matrix.a / scale.x);
                          f32 degrees  = glm::degrees(radians);
                          f32 rotation = 0.0f;
                          
                          if (degrees > 90.0f && sign > 0)
                          {
                              rotation = glm::radians(360.0f - degrees);
                          } else if (degrees < 90.0f && sign < 0) {
                              rotation = glm::radians(360.0f - degrees);
                          } else {
                              rotation = radians;
                          }
                          rotation = glm::degrees(rotation);
                          glm::vec2 position = glm::vec2(iterator.second.m_matrix.tx,
                                                         iterator.second.m_matrix.ty);
                          sprites.push_back(std::make_tuple(spriteElement->second,
                                                            iterator.second.index,
                                                            position,
                                                            rotation,
                                                            scale));
                          m_addedSpriteElements.insert(std::make_pair(stateId,
                                                                      spriteElement->second));
                          m_spriteElementsTransformations.insert(std::make_pair(stateId,
                                                                                std::make_tuple(iterator.second.index,
                                                                                                position,
                                                                                                rotation,
                                                                                                scale)));
                      });
        
        std::sort(sprites.begin(), sprites.end(), []
                  (const std::tuple<std::shared_ptr<ieSprite>, ui32, glm::vec2, f32, glm::vec2>& iterator_01,
                   const std::tuple<std::shared_ptr<ieSprite>, ui32, glm::vec2, f32, glm::vec2>& iterator_02)
                  {
                      return std::get<1>(iterator_01) < std::get<1>(iterator_02);
                  });
        
        std::for_each(sprites.begin(), sprites.end(),  [this]
                      (const std::tuple<std::shared_ptr<ieSprite>, ui32, glm::vec2, f32, glm::vec2>& iterator)
                      {
                          ieSprite::addChild(std::get<0>(iterator));
                          std::get<0>(iterator)->setPosition(std::get<2>(iterator));
                          std::get<0>(iterator)->setRotation(std::get<3>(iterator));
                          std::get<0>(iterator)->setScale(std::get<4>(iterator));
                      });
    }
}

void ieSprite::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onRemoved(event);
}
