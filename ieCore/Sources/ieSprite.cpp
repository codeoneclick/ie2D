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
        m_sequence = m_resourceAccessor->getSequence(m_sequenceFilename);
        size_t found = m_sequenceFilename.find_last_of("/\\");
        std::string path = m_sequenceFilename.substr(0, found);
        std::for_each( m_sequence->getSequenceTextures().begin(),  m_sequence->getSequenceTextures().end(), [this, path](const std::pair<ui32, ieSequenceTexture>& iterator){
            m_texture = m_resourceAccessor->getTexture(path + "/" + iterator.second.m_imageFilename);
        });
        
        auto sequenceFrame = m_sequence->getSequenceFrames().find(1);
        assert(sequenceFrame != m_sequence->getSequenceFrames().end());
        std::for_each((*sequenceFrame).second.m_states.begin(), (*sequenceFrame).second.m_states.end(),  [this, path](const std::pair<std::string, ieSequenceFrameState>& iterator)
        {
            static f32 offset = 0;
            std::string stateId = iterator.first;
            auto sequenceAnimatedElement = m_sequence->getSequenceAnimatedElements().find(stateId);
            assert(sequenceAnimatedElement != m_sequence->getSequenceAnimatedElements().end());
            std::string sequenceElementId = sequenceAnimatedElement->second;
            auto sequenceElement = m_sequence->getSequenceElements().find(sequenceElementId);
            assert(sequenceElement != m_sequence->getSequenceElements().end());
            ui32 sequenceTextureId = sequenceElement->second.m_sequenceTextureId;
            auto sequenceTexture = m_sequence->getSequenceTextures().find(sequenceTextureId);
            assert(sequenceTexture != m_sequence->getSequenceTextures().end());
            std::string imageFilename = sequenceTexture->second.m_imageFilename;
            std::shared_ptr<ieSprite> sprite = std::make_shared<ieSprite>(glm::vec4(0, 0, sequenceElement->second.m_size.x, sequenceElement->second.m_size.y), path + "/" + imageFilename);
            ieSprite::addChild(sprite);
            glm::vec4 frame = glm::vec4(sequenceElement->second.m_position.x / static_cast<f32>(m_texture->getWidth()),
                                        1.0f - (sequenceElement->second.m_position.y + sequenceElement->second.m_size.y) / static_cast<f32>(m_texture->getHeight()),
                                        (sequenceElement->second.m_position.x + sequenceElement->second.m_size.x) / static_cast<f32>(m_texture->getWidth()),
                                        1.0f - sequenceElement->second.m_position.y / static_cast<f32>(m_texture->getHeight()));
            sprite->setTextureFrame(frame);
            glm::vec2 position = glm::vec2(iterator.second.m_matrix[3][0], iterator.second.m_matrix[3][1]);
            sprite->setPosition(position);
            offset += 150;
        });
        
        /*std::for_each(m_sequence->getSequenceElements().begin(), m_sequence->getSequenceElements().end(), [this, path](const std::pair<std::string, ieSequenceElement>& iterator){
            
            auto sequenceTexture = m_sequence->getSequenceTextures().find(iterator.second.m_sequenceTextureId);
            assert(sequenceTexture != m_sequence->getSequenceTextures().end());
            std::string imageFilename = (*sequenceTexture).second.m_imageFilename;
         
            glm::vec4 frame = glm::vec4(iterator.second.m_position.x / static_cast<f32>(m_texture->getWidth()),
                                        1.0f - (iterator.second.m_position.y + iterator.second.m_size.y) / static_cast<f32>(m_texture->getHeight()),
                                        (iterator.second.m_position.x + iterator.second.m_size.x) / static_cast<f32>(m_texture->getWidth()),
                                        1.0f - iterator.second.m_position.y / static_cast<f32>(m_texture->getHeight()));
            sprite->setTextureFrame(frame);
            auto sequenceFrame = m_sequence->getSequenceFrames().find(1);
            assert(sequenceFrame != m_sequence->getSequenceFrames().end());
            std::string sequenceElementId = iterator.second.m_name;
            auto sequenceAnimatedElement = m_sequence->getSequenceAnimatedElements().find(sequenceElementId);
            assert(sequenceAnimatedElement != m_sequence->getSequenceAnimatedElements().end());
            std::string stateId = (*sequenceAnimatedElement).second;
            auto sequenceFrameState = (*sequenceFrame).second.m_states.find(stateId);
            assert(sequenceFrameState != (*sequenceFrame).second.m_states.end());
            glm::vec2 position = glm::vec2((*sequenceFrameState).second.m_matrix[3][0], (*sequenceFrameState).second.m_matrix[3][1]);
            sprite->setPosition(position);
        });*/
    }
}

void ieSprite::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObjectContainer::onRemoved(event);
}
