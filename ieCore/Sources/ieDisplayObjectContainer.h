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
    
    ieEventDispatcherFunctionShared m_functionOnUpdate;
    ieEventDispatcherFunctionShared m_functionOnDraw;
    ieEventDispatcherFunctionShared m_functionOnEnterFrame;
    ieEventDispatcherFunctionShared m_functionOnExitFrame;
    
    ieEventDispatcherFunctionShared m_functionOnAdded;
    ieEventDispatcherFunctionShared m_functionOnRemoved;
    
protected:
    
    virtual void onUpdate(const std::shared_ptr<ieEvent>& event);
    virtual void onDraw(const std::shared_ptr<ieEvent>& event);
    virtual void onEnterFrame(const std::shared_ptr<ieEvent>& event);
    virtual void onExitFrame(const std::shared_ptr<ieEvent>& event);
    
    virtual void onAdded(const std::shared_ptr<ieEvent>& event);
    virtual void onRemoved(const std::shared_ptr<ieEvent>& event);
    
public:
    
    ieDisplayObjectContainer(void);
    ~ieDisplayObjectContainer(void);
    
};

#endif
