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
class ieMask;

typedef struct
{
    ui32 m_index;
    f32 m_alpha;
    std::string m_maskName;
    glm::mat4 m_matrixTransformation;
} ieSpriteElementTransformation;

typedef struct
{
    std::string m_imageFilename;
    glm::vec2 m_size;
    glm::vec2 m_pivot;
    glm::vec4 m_texCoord;
} ieSpriteElementUniqueSettings;

typedef std::shared_ptr<ieMask> ieSharedMask;
typedef std::shared_ptr<ieSprite> ieSharedSprite;
typedef const std::pair<std::string, ieSharedSprite>& ieSpriteElementPair;
typedef const std::unordered_map<std::string, ieSharedSprite>::const_iterator& ieSpriteElementIterator;
typedef std::unordered_map<std::string, ieSpriteElementTransformation> ieSpriteAnimationFrame;
typedef const std::pair<std::string, ieSpriteElementTransformation>& ieSpriteAnimationFramePair;

class ieColor;
class ieTexture;
class ieSequence;
class ieSprite : public ieDisplayObjectContainer
{
private:
    
    std::string m_imageFilename;
    std::shared_ptr<ieTexture> m_texture;
    std::shared_ptr<ieMask> m_mask;
    
protected:
    
    virtual void onUpdate(const std::shared_ptr<ieEvent>& event);
    virtual void onDraw(const std::shared_ptr<ieEvent>& event);
    virtual void onEnterFrame(const std::shared_ptr<ieEvent>& event);
    virtual void onExitFrame(const std::shared_ptr<ieEvent>& event);
    
    virtual void onAdded(const std::shared_ptr<ieEvent>& event);
    virtual void onRemoved(const std::shared_ptr<ieEvent>& event);

    std::string m_sequenceFilename;
    std::shared_ptr<ieSequence> m_sequence;
    
    std::unordered_map<std::string, ieSpriteElementUniqueSettings> m_spriteElementUniqueSettings;
    std::unordered_map<std::string, ieSharedSprite> m_activeSpriteElements;
    std::unordered_map<std::string, ieSharedMask> m_activeMaskElementsWithElementsIds;
    std::unordered_map<std::string, ieSharedMask> m_activeMaskElementsWithStateIds;
    std::vector<ieSpriteAnimationFrame> m_spriteAnimationFrames;
    
    glm::ivec2 getSpriteElementTextureSize(const std::string& imageFilename);
    void createSpriteElements(void);
    void createSpriteAnimationFrame(ui32 index, ieSpriteAnimationFrame& previosSpriteAnimationFrame);
    
    ieSharedSprite createUniqueSprite(const std::string& name);
    ieSharedSprite getActiveSprite(const std::string& name);
    
    ieSharedMask createUniqueMask(const std::string& name);
    ieSharedMask getActiveMaskWithStateId(const std::string& name);
    ieSharedMask getActiveMaskWithElementId(const std::string& name);
    
    virtual void setMask(const std::shared_ptr<ieMask>& mask);
    
    virtual void gotoAndStop(ui32 index);
    
public:
    ieSprite(const glm::vec4& frame,
             const std::shared_ptr<ieColor>& color);
    ieSprite(const glm::vec4& frame,
             const std::string& filename,
             const std::shared_ptr<ieColor>& color = nullptr);
    
    virtual ~ieSprite(void);
};

#endif
