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
    
public:
    ieSprite(const glm::vec4& frame,
             const std::shared_ptr<ieColor>& color);
    ieSprite(const glm::vec4& frame,
             const std::string& filename,
             const std::shared_ptr<ieColor>& color = nullptr);
    
    virtual ~ieSprite(void);
    
};

#endif
