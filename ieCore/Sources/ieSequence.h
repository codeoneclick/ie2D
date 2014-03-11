//
//  ieSequence.h
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieSequence__
#define __ieCore__ieSequence__

#include "ieResource.h"

typedef struct
{
    ui32 m_id;
    std::string m_imageFilename;
    ui32 m_width;
    ui32 m_height;
} ieSequenceTexture;

typedef struct
{
    ui32 m_sequenceTextureId;
    std::string m_name;
    glm::ivec2 m_position;
    glm::ivec2 m_size;
    glm::ivec2 m_pivot;
} ieSequenceElement;

typedef struct
{
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 tx;
    f32 ty;
} ieSequenceFrameTransformation;

typedef struct
{
    i32 index;
    ieSequenceFrameTransformation m_matrix;
} ieSequenceFrameState;

typedef struct
{
    std::unordered_map<std::string, ieSequenceFrameState> m_states;
} ieSequenceFrame;

class ieSequence : public ieResource
{
private:
    
protected:
    
    std::unordered_map<ui32, ieSequenceTexture> m_sequenceTextures;
    std::unordered_map<std::string, ieSequenceElement> m_sequenceElements;
    std::unordered_map<ui32, ieSequenceFrame> m_sequenceFrames;
    std::unordered_map<std::string, std::string> m_sequenceAnimatedElements;
    ui32 m_animationFrameCount;
    
public:
    
    ieSequence(const std::string& filename);
    ~ieSequence(void);
    
    const std::unordered_map<ui32, ieSequenceTexture>& getSequenceTextures(void) const;
    const std::unordered_map<std::string, ieSequenceElement>& getSequenceElements(void) const;
    const std::unordered_map<ui32, ieSequenceFrame>& getSequenceFrames(void) const;
    const std::unordered_map<std::string, std::string>& getSequenceAnimatedElements(void) const;
    ui32 getAnimationFrameCount(void) const;
};

#endif
