//
//  ieInteractiveObject.h
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieInteractiveObject__
#define __ieCore__ieInteractiveObject__

#include "ieDisplayObject.h"

class ieTouchRecognizer;

class ieInteractiveObject : public ieDisplayObject
{
private:
    
protected:
    
    virtual void onUpdate(const std::shared_ptr<ieEvent>& event);
    virtual void onDraw(const std::shared_ptr<ieEvent>& event);
    virtual void onEnterFrame(const std::shared_ptr<ieEvent>& event);
    virtual void onExitFrame(const std::shared_ptr<ieEvent>& event);
    
    virtual void onAdded(const std::shared_ptr<ieEvent>& event);
    virtual void onRemoved(const std::shared_ptr<ieEvent>& event);
    
    bool m_isTouchable;
    std::shared_ptr<ieTouchRecognizer> m_touchRecognizer;
    
public:
    
    ieInteractiveObject(const glm::vec4& frame);
    ~ieInteractiveObject(void);
    
    void setTouchable(bool value);
    bool isTouchable(void) const;
};

#endif
