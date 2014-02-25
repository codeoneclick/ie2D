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
    
    std::set<std::shared_ptr<ieDisplayObject>> m_uniqueChilds;
    std::vector<std::shared_ptr<ieDisplayObject>> m_childs;
    
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
    
    void addChild(const std::shared_ptr<ieDisplayObject>& child);
    void addChildAt(const std::shared_ptr<ieDisplayObject>& child, i32 index);
    
    bool contains(const std::shared_ptr<ieDisplayObject>& child) const;
    
    std::shared_ptr<ieDisplayObject> getChildAt(i32 index) const;
    std::shared_ptr<ieDisplayObject> getChildByName(const std::string& name) const;
    
    i32 getChildIndex(const std::shared_ptr<ieDisplayObject>& child) const;
    std::vector<std::shared_ptr<ieDisplayObject>> getObjectsUnderPoint(const glm::vec2& point) const;
    
    void removeChild(const std::shared_ptr<ieDisplayObject>& child);
    void removeChildAt(i32 index);
    void removeChildren(i32 startIndex, i32 endIndex);
    
    void setChildIndex(const std::shared_ptr<ieDisplayObject>& child, i32 index);
    void swapChildren(const std::shared_ptr<ieDisplayObject>& child_01,
                      const std::shared_ptr<ieDisplayObject>& child_02);
    void swapChildrenAt(i32 index_01, i32 index_02);
    
};

#endif
