//
//  ieTile.h
//  ieEngine
//
//  Created by sergey.sergeev on 3/28/14.
//  Copyright (c) 2014 sergey.sergeev. All rights reserved.
//

#ifndef __ieEngine__ieTile__
#define __ieEngine__ieTile__

#include "ieSprite.h"

class ieTile : public ieSprite
{
private:
    
protected:
    
    virtual void onUpdate(const std::shared_ptr<ieEvent>& event);
    virtual void onDraw(const std::shared_ptr<ieEvent>& event);
    virtual void onEnterFrame(const std::shared_ptr<ieEvent>& event);
    virtual void onExitFrame(const std::shared_ptr<ieEvent>& event);
    
    virtual void onAdded(const std::shared_ptr<ieEvent>& event);
    virtual void onRemoved(const std::shared_ptr<ieEvent>& event);
    
    glm::vec4 m_tileTexCoordFrame;
    std::string m_tilesetImageName;
    
public:
    ieTile(const std::string& imageFilename,
           const glm::vec4& frame,
           const glm::vec4& texCoordFrame);
    ~ieTile(void);
};


#endif
