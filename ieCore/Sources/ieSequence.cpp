//
//  ieSequence.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieSequence.h"

typedef struct
{
    ui32 m_id;
    std::string m_imageFilename;
} ieSequenceTexture;

typedef struct
{
    ui32 m_sequenceTextureId;
    std::string m_name;
    glm::ivec2 m_position;
    glm::ivec2 m_size;
} ieSequenceElement;

ieSequence::ieSequence(const std::string& filename) :
ieResource(E_RESOURCE_TYPE_SEQUENSE)
{
    Json::Value root;
    Json::Reader reader;
    std::ifstream stream(filename, std::ifstream::binary);
    bool success = reader.parse(stream, root, false);
    if (!success)
    {
        std::cout<<reader.getFormatedErrorMessages()<<std::endl;
    }
    Json::Value animationSequences = root["animationSequences"];
    Json::Value animationObjects = root["animationObjects"];
    Json::Value textures = root["textureAtlas"];
    
    std::vector<ieSequenceTexture> sequenceTextures;
    std::vector<ieSequenceElement> sequenceElements;
    for(ui32 i = 0; i < textures.size(); ++i)
    {
        Json::Value atlases = textures[i]["atlases"];
        for(ui32 j = 0; j < atlases.size(); ++j)
        {
            ieSequenceTexture sequenceTexture;
            sequenceTexture.m_id = atlases[j]["id"].asUInt();
            Json::Value sources = atlases[j]["sources"];
            for(ui32 k = 0; k < sources.size(); ++k)
            {
                sequenceTexture.m_imageFilename = sources[k]["source"].asString();
            }
            sequenceTextures.push_back(sequenceTexture);
        }
        Json::Value elements = textures[i]["elements"];
        for(ui32 j = 0; j < elements.size(); ++j)
        {
            ieSequenceElement sequenceElement;
            sequenceElement.m_sequenceTextureId = elements[j]["atlasID"].asUInt();
            sequenceElement.m_name = elements[j]["name"].asString();
            sequenceElement.m_position.x= elements[j]["x"].asInt();
            sequenceElement.m_position.y = elements[j]["y"].asInt();
            sequenceElement.m_size.x = elements[j]["width"].asInt();
            sequenceElement.m_size.y = elements[j]["height"].asInt();
            sequenceElements.push_back(sequenceElement);
        }
    }
    std::cout<<"Image name: "<<std::endl;
}

ieSequence::~ieSequence(void)
{
    
}