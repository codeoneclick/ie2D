//
//  ieMask.h
//  ieCore
//
//  Created by sergey.sergeev on 3/21/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieMask__
#define __ieCore__ieMask__

#include "ieDisplayObject.h"

class ieMask : public ieDisplayObject
{
private:
    
    std::shared_ptr<ieShape> m_shape;
    
    std::string m_imageFilename;
    std::shared_ptr<ieTexture> m_texture;
    
    friend class ieSprite;
    
protected:
    
    virtual void onUpdate(const std::shared_ptr<ieEvent>& event);
    virtual void onDraw(const std::shared_ptr<ieEvent>& event);
    virtual void onEnterFrame(const std::shared_ptr<ieEvent>& event);
    virtual void onExitFrame(const std::shared_ptr<ieEvent>& event);
    
    virtual void onAdded(const std::shared_ptr<ieEvent>& event);
    virtual void onRemoved(const std::shared_ptr<ieEvent>& event);
    
public:
    
    ieMask(const glm::vec4& frame,
           const std::string& filename);
    
    ~ieMask(void);
    
    void begin(const std::shared_ptr<ieDisplayObjectContainer>& parent);
    void end(void);
};

#endif
