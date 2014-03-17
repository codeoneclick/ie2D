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
                      [this, path](ieSequenceElementPair sequenceElementPair)
                      {
                          std::string sequenceElementName = sequenceElementPair.first;
                          ieSequenceElement sequenceElement = sequenceElementPair.second;
                          ui32 sequenceTextureId = sequenceElement.m_sequenceTextureId;
                          ieSequenceTextureIterator sequenceTextureIterator = m_sequence->getSequenceTextures().find(sequenceTextureId);
                          assert(sequenceTextureIterator != m_sequence->getSequenceTextures().end());
                          std::string imageFilename = sequenceTextureIterator->second.m_imageFilename;
                          
                          glm::vec4 texCoord =
                          glm::vec4(static_cast<f32>(sequenceElement.m_position.x) / static_cast<f32>(m_texture->getWidth()),
                                    1.0f - static_cast<f32>(sequenceElement.m_position.y + sequenceElement.m_size.y) / static_cast<f32>(m_texture->getHeight()),
                                    static_cast<f32>(sequenceElement.m_position.x + sequenceElement.m_size.x) / static_cast<f32>(m_texture->getWidth()),
                                    1.0f - static_cast<f32>(sequenceElement.m_position.y) / static_cast<f32>(m_texture->getHeight()));
                          
                          ieSpriteElementUniqueSettings spriteElementUniqueSettings;
                          spriteElementUniqueSettings.m_imageFilename = path + "/" + imageFilename;
                          spriteElementUniqueSettings.m_size = sequenceElement.m_size;
                          spriteElementUniqueSettings.m_pivot = sequenceElement.m_pivot;
                          spriteElementUniqueSettings.m_texCoord = texCoord;
                          m_spriteElementUniqueSettings.insert(std::make_pair(sequenceElementName, spriteElementUniqueSettings));
                      });
        
        ieSpriteAnimationFrame spriteAnimationFrame;
        m_spriteAnimationFrames.resize(m_sequence->getAnimationFrameCount());
        for (ui32 index = 0; index < m_sequence->getAnimationFrameCount(); ++index)
        {
            ieSequenceFrameIterator sequenceFrameIterator = m_sequence->getSequenceFrames().find(index + 1);
            if(index == 0 && sequenceFrameIterator == m_sequence->getSequenceFrames().end())
            {
                assert(false);
                break;
            } else if(sequenceFrameIterator == m_sequence->getSequenceFrames().end()) {
                m_spriteAnimationFrames[index] = spriteAnimationFrame;
                continue;
            }
            
            ieSpriteAnimationFrame currentSpriteAnimationFrame;
            ieSequenceFrame sequenceFrame = sequenceFrameIterator->second;
            std::for_each(sequenceFrame.m_states.begin(),
                          sequenceFrame.m_states.end(),
                          [this, path, &currentSpriteAnimationFrame](ieSequenceFrameStatePair sequenceFrameStatePair){
                              std::string stateId = sequenceFrameStatePair.first;
                              ieSequenceFrameState sequenceFrameState = sequenceFrameStatePair.second;
                              ieSequenceAnimatedElementIterator sequenceAnimatedElementIterator = m_sequence->getSequenceAnimatedElements().find(stateId);
                              assert(sequenceAnimatedElementIterator != m_sequence->getSequenceAnimatedElements().end());
                              std::string sequenceElementId = sequenceAnimatedElementIterator->second;
                              
                              glm::vec2 scale = glm::vec2(sqrtf((sequenceFrameState.m_matrix.a * sequenceFrameState.m_matrix.a) +
                                                                (sequenceFrameState.m_matrix.c * sequenceFrameState.m_matrix.c)),
                                                          sqrtf((sequenceFrameState.m_matrix.b * sequenceFrameState.m_matrix.b) +
                                                                (sequenceFrameState.m_matrix.d * sequenceFrameState.m_matrix.d)));
                              
                              scale.x *= sequenceFrameState.m_matrix.a > 0.0f ? 1.0f : -1.0f;
                              scale.y *= sequenceFrameState.m_matrix.d > 0.0f ? 1.0f : -1.0f;
                              
                              f32 sign = atanf(-sequenceFrameState.m_matrix.c / sequenceFrameState.m_matrix.a);
                              f32 radians  = acosf(sequenceFrameState.m_matrix.a / scale.x);
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
                              glm::vec2 position = glm::vec2(sequenceFrameState.m_matrix.tx,
                                                             sequenceFrameState.m_matrix.ty);
                              ieSpriteElementTransformation spriteElementTransformation;
                              spriteElementTransformation.m_index = sequenceFrameState.m_index;
                              spriteElementTransformation.m_alpha = sequenceFrameState.m_alpha;
                              spriteElementTransformation.m_position = position;
                              spriteElementTransformation.m_rotation = rotation;
                              spriteElementTransformation.m_scale = scale;
                              spriteElementTransformation.m_matrix = glm::mat4(sequenceFrameState.m_matrix.a, sequenceFrameState.m_matrix.b, 0.0f, 0.0f,
                                                                               sequenceFrameState.m_matrix.c, sequenceFrameState.m_matrix.d, 0.0f, 0.0f,
                                                                               0.0f, 0.0f, 1.0f, 0.0f,
                                                                               sequenceFrameState.m_matrix.tx, sequenceFrameState.m_matrix.ty, 0.0f, 1.0f);
                              currentSpriteAnimationFrame.insert(std::make_pair(stateId, spriteElementTransformation));
                          });
            spriteAnimationFrame = currentSpriteAnimationFrame;
            m_spriteAnimationFrames[index] = spriteAnimationFrame;
        }
        ieSprite::gotoAndStop(0);
    }
}

void ieSprite::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onRemoved(event);
}

ieSharedSprite ieSprite::createUniqueSprite(const std::string& name)
{
    const auto& iterator = m_spriteElementUniqueSettings.find(name);
    assert(iterator != m_spriteElementUniqueSettings.end());
    
    ieSpriteElementUniqueSettings spriteElementUniqueSettings = iterator->second;
    
    ieSharedSprite sprite = std::make_shared<ieSprite>(glm::vec4(0, 0,
                                                                 spriteElementUniqueSettings.m_size.x,
                                                                 spriteElementUniqueSettings.m_size.y),
                                                       spriteElementUniqueSettings.m_imageFilename);
    sprite->m_texCoord = spriteElementUniqueSettings.m_texCoord;
    sprite->setPivot(spriteElementUniqueSettings.m_pivot);
    return sprite;
}

ieSharedSprite ieSprite::getActiveSprite(const std::string& name)
{
    const auto& iterator = m_activeSpriteElements.find(name);
    return iterator != m_activeSpriteElements.end() ? iterator->second : nullptr;
}

void ieSprite::gotoAndStop(ui32 index)
{
    if(index < m_sequence->getAnimationFrameCount())
    {
        ieSpriteAnimationFrame spriteAnimationFrame = m_spriteAnimationFrames[index];
        std::for_each(spriteAnimationFrame.begin(),
                      spriteAnimationFrame.end(),
                      [this](ieSpriteAnimationFramePair spriteAnimationFramePair){
                          std::string stateId = spriteAnimationFramePair.first;
                          ieSpriteElementTransformation spriteElementTransformation = spriteAnimationFramePair.second;
                          ieSharedSprite activeSprite = ieSprite::getActiveSprite(stateId);
                          if(activeSprite == nullptr)
                          {
                              ieSequenceAnimatedElementIterator sequenceAnimatedElementIterator = m_sequence->getSequenceAnimatedElements().find(stateId);
                              assert(sequenceAnimatedElementIterator != m_sequence->getSequenceAnimatedElements().end());
                              std::string sequenceElementId = sequenceAnimatedElementIterator->second;
                              ieSharedSprite uniqueSprite = ieSprite::createUniqueSprite(sequenceElementId);
                              ieSprite::addChild(uniqueSprite);
                              m_activeSpriteElements.insert(std::make_pair(stateId, uniqueSprite));
                              activeSprite = uniqueSprite;
                          }
                          activeSprite->setVisible(spriteElementTransformation.m_alpha != 0.0f);
                          activeSprite->m_externalTransformation = spriteElementTransformation.m_matrix;
                      });
        std::for_each(spriteAnimationFrame.begin(),
                      spriteAnimationFrame.end(),
                      [this](ieSpriteAnimationFramePair spriteAnimationFramePair){
                          std::string stateId = spriteAnimationFramePair.first;
                          ieSpriteElementTransformation spriteElementTransformation = spriteAnimationFramePair.second;
                          ieSharedSprite activeSprite = ieSprite::getActiveSprite(stateId);
                          assert(activeSprite != nullptr);
                          ieSprite::setChildIndex(activeSprite, spriteElementTransformation.m_index);
                      });
    }
}
