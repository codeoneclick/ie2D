//
//  ieDisplayObjectContainer.h
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieDisplayObjectContainer__
#define __ieCore__ieDisplayObjectContainer__

#include "ieInteractiveObject.h"

class ieDisplayObjectContainer : public ieInteractiveObject
{
private:
    
    std::shared_ptr<ieDisplayObjectContainer> m_parent;
    std::set<std::shared_ptr<ieDisplayObjectContainer>> m_childs;
    
protected:
    
    virtual void onUpdate(const std::shared_ptr<ieEvent>& event);
    virtual void onDraw(const std::shared_ptr<ieEvent>& event);
    virtual void onEnterFrame(const std::shared_ptr<ieEvent>& event);
    virtual void onExitFrame(const std::shared_ptr<ieEvent>& event);
    
    virtual void onAdded(const std::shared_ptr<ieEvent>& event);
    virtual void onRemoved(const std::shared_ptr<ieEvent>& event);
    
public:
    
    ieDisplayObjectContainer(const glm::vec4& frame);
    ~ieDisplayObjectContainer(void);
    
};

#endif
