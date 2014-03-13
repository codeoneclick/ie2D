//
//  ieSequence.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieSequence.h"

struct tokens : std::ctype<char>
{
    tokens() : std::ctype<char>(get_table()) {}
    
    static std::ctype_base::mask const* get_table()
    {
        typedef std::ctype<char> cctype;
        static const cctype::mask *const_rc = cctype::classic_table();
        
        static cctype::mask rc[cctype::table_size];
        std::memcpy(rc, const_rc, cctype::table_size * sizeof(cctype::mask));
        
        rc[','] = std::ctype_base::space;
        return &rc[0];
    }
};

static void split(const std::string& value, const std::string& delimeter, std::vector<std::string>& out)
{
    std::stringstream stringstream(value);
    stringstream.imbue(std::locale(std::locale(), new tokens()));
    std::istream_iterator<std::string> begin(stringstream);
    std::istream_iterator<std::string> end;
    out.assign(begin, end);
}

ieSequence::ieSequence(const std::string& filename) :
ieResource(E_RESOURCE_TYPE_SEQUENSE),
m_animationFrameCount(0)
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
    Json::Value animationFrames = root["animationConfigFrames"];
    
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
            sequenceTexture.m_width = 0;
            sequenceTexture.m_height = 0;
            m_sequenceTextures.insert(std::make_pair(sequenceTexture.m_id, sequenceTexture));
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
            sequenceElement.m_pivot.x = elements[j]["pivotX"].asInt();
            sequenceElement.m_pivot.y = elements[j]["pivotY"].asInt();
            m_sequenceElements.insert(std::make_pair(sequenceElement.m_name, sequenceElement));
        }
    }
    
    for(ui32 i = 0; i < animationFrames.size(); ++i)
    {
        Json::Value sequenceFrameStateJSON = animationFrames[i]["state"];
        Json::Value::Members sequenceFrameStateMembers = sequenceFrameStateJSON.getMemberNames();
        ieSequenceFrame sequenceFrame;
        for(ui32 j = 0; j < sequenceFrameStateMembers.size(); ++j)
        {
            ieSequenceFrameState sequenceFrameState;
            std::string stateId = sequenceFrameStateMembers[j];
            std::string state = sequenceFrameStateJSON[stateId]["st"].asString();
    
            i32 begin = state.find('{');
            i32 end = state.find('}');
            if (begin == std::string::npos ||
                end == std::string::npos || end < begin)
            {
                assert(false);
                return;
            }
            std::string temp = state.substr(0, begin - 1);
            sequenceFrameState.m_index = atoi(temp.c_str());
            temp = state.substr(end + 2, state.length() - end - 2);
            temp = state.substr(begin + 1, end - begin - 1);

            std::vector<std::string> transform;
            transform.reserve(6);
            split(temp, ",", transform);

            if (6 != transform.size())
            {
                assert(false);
            }

            sequenceFrameState.m_matrix.a = static_cast<f32>(atof(transform[0].c_str()));
            sequenceFrameState.m_matrix.b = static_cast<f32>(atof(transform[1].c_str()));
            sequenceFrameState.m_matrix.c = static_cast<f32>(atof(transform[2].c_str()));
            sequenceFrameState.m_matrix.d = static_cast<f32>(atof(transform[3].c_str()));
            sequenceFrameState.m_matrix.tx = static_cast<f32>(atof(transform[4].c_str()));
            sequenceFrameState.m_matrix.ty = static_cast<f32>(atof(transform[5].c_str()));
            
            sequenceFrame.m_states.insert(std::make_pair(stateId, sequenceFrameState));
        }
        ui32 frameNumber = animationFrames[i]["frameNumber"].asUInt();
        m_sequenceFrames.insert(std::make_pair(frameNumber, sequenceFrame));
    }
    
    Json::Value::Members sequenceAnimatedElementsMembers = animationObjects.getMemberNames();
    for(ui32 i = 0; i < sequenceAnimatedElementsMembers.size(); ++i)
    {
        std::string stateId = sequenceAnimatedElementsMembers[i];
        std::string animatedElementId = animationObjects[sequenceAnimatedElementsMembers[i]].asString();
        m_sequenceAnimatedElements.insert(std::make_pair(stateId, animatedElementId));
    }
    
    m_animationFrameCount = root["animationFrameCount"].asUInt();
    
    std::cout<<"done"<<std::endl;
}

ieSequence::~ieSequence(void)
{
    
}

const std::unordered_map<ui32, ieSequenceTexture>& ieSequence::getSequenceTextures(void) const
{
    return m_sequenceTextures;
}

const std::unordered_map<std::string, ieSequenceElement>& ieSequence::getSequenceElements(void) const
{
    return m_sequenceElements;
}

const std::unordered_map<ui32, ieSequenceFrame>& ieSequence::getSequenceFrames(void) const
{
    return m_sequenceFrames;
}

const std::unordered_map<std::string, std::string>& ieSequence::getSequenceAnimatedElements(void) const
{
    return m_sequenceAnimatedElements;
}

ui32 ieSequence::getAnimationFrameCount(void) const
{
    return m_animationFrameCount;
}
