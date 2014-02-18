//
//  ieResourceAccessor.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieResourceAccessor.h"
#include "ieShader.h"
#include "ieTexture.h"
#include "ieSequence.h"

ieResourceAccessor::ieResourceAccessor(void)
{
    m_description = "ieResourceAccessor";
}

ieResourceAccessor::~ieResourceAccessor(void)
{
    m_resources.clear();
}

std::shared_ptr<ieShader> ieResourceAccessor::getShader(const std::string& vsFilename,
                                                        const std::string& fsFilename,
                                                        const std::shared_ptr<ieObject>& owner)
{
    std::shared_ptr<ieShader> shader = nullptr;
    std::string key = "";
    key.append(vsFilename).append(fsFilename);
    const auto& iterator = m_resources.find(key);
    if(iterator == m_resources.end())
    {
        shader = std::make_shared<ieShader>(vsFilename, fsFilename);
        m_resources.insert(std::make_pair(key, shader));
    } else {
        shader = std::static_pointer_cast<ieShader>(iterator->second);
    }
    if(owner != nullptr)
    {
        shader->addOwner(owner);
    }
    return shader;
}

std::shared_ptr<ieTexture> ieResourceAccessor::getTexture(const std::string& filename,
                                                          const std::shared_ptr<ieObject>& owner)
{
    std::shared_ptr<ieTexture> texture = nullptr;
    const auto& iterator = m_resources.find(filename);
    if(iterator == m_resources.end())
    {
        texture = std::make_shared<ieTexture>(filename);
        m_resources.insert(std::make_pair(filename, texture));
    } else {
        texture = std::static_pointer_cast<ieTexture>(iterator->second);
    }
    if(owner != nullptr)
    {
        texture->addOwner(owner);
    }
    return texture;
}

std::shared_ptr<ieSequence> ieResourceAccessor::getSequence(const std::string& filename,
                                                            const std::shared_ptr<ieObject>& owner)
{
    std::shared_ptr<ieSequence> sequence = nullptr;
    const auto& iterator = m_resources.find(filename);
    if(iterator == m_resources.end())
    {
        sequence = std::make_shared<ieSequence>(filename);
        m_resources.insert(std::make_pair(filename, sequence));
    } else {
        sequence = std::static_pointer_cast<ieSequence>(iterator->second);
    }
    if(owner != nullptr)
    {
        sequence->addOwner(owner);
    }
    return sequence;
}

