//
//  ieSprite.h
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieSprite__
#define __ieCore__ieSprite__

#include "ieDisplayObjectContainer.h"

class ieSprite;

typedef struct
{
    ui32 m_index;
    glm::vec2 m_position;
    f32 m_rotation;
    glm::vec2 m_scale;
    f32 m_alpha;
    glm::mat4 m_matrix;
} ieSpriteElementTransformation;

typedef struct
{
    std::string m_imageFilename;
    glm::vec2 m_size;
    glm::vec2 m_pivot;
    glm::vec4 m_texCoord;
} ieSpriteElementUniqueSettings;

typedef std::shared_ptr<ieSprite> ieSharedSprite;
typedef const std::pair<std::string, ieSharedSprite>& ieSpriteElementPair;
typedef std::unordered_map<std::string, ieSharedSprite>::const_iterator ieSpriteElementIterator;
typedef std::unordered_map<std::string, ieSpriteElementTransformation> ieSpriteAnimationFrame;
typedef const std::pair<std::string, ieSpriteElementTransformation>& ieSpriteAnimationFramePair;

class ieColor;
class ieTexture;
class ieSequence;
class ieSprite : public ieDisplayObjectContainer
{
private:
    
protected:
    
    virtual void onUpdate(const std::shared_ptr<ieEvent>& event);
    virtual void onDraw(const std::shared_ptr<ieEvent>& event);
    virtual void onEnterFrame(const std::shared_ptr<ieEvent>& event);
    virtual void onExitFrame(const std::shared_ptr<ieEvent>& event);
    
    virtual void onAdded(const std::shared_ptr<ieEvent>& event);
    virtual void onRemoved(const std::shared_ptr<ieEvent>& event);
    
    std::string m_imageFilename;
    std::string m_sequenceFilename;
    std::shared_ptr<ieTexture> m_texture;
    std::shared_ptr<ieSequence> m_sequence;
    
    std::unordered_map<std::string, ieSpriteElementUniqueSettings> m_spriteElementUniqueSettings;
    std::unordered_map<std::string, ieSharedSprite> m_activeSpriteElements;
    std::vector<ieSpriteAnimationFrame> m_spriteAnimationFrames;
    
    ieSharedSprite createUniqueSprite(const std::string& name);
    ieSharedSprite getActiveSprite(const std::string& name);
    
public:
    ieSprite(const glm::vec4& frame,
             const std::shared_ptr<ieColor>& color);
    ieSprite(const glm::vec4& frame,
             const std::string& filename,
             const std::shared_ptr<ieColor>& color = nullptr);
    
    virtual ~ieSprite(void);
    
    void gotoAndStop(ui32 index);
};

#endif
