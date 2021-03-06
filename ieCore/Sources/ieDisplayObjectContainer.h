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
    
    std::set<std::shared_ptr<ieDisplayObjectContainer>> m_uniqueChilds;
    std::vector<std::shared_ptr<ieDisplayObjectContainer>> m_childs;
    
protected:
    
    virtual void onUpdate(const std::shared_ptr<ieEvent>& event);
    virtual void onDraw(const std::shared_ptr<ieEvent>& event);
    virtual void onEnterFrame(const std::shared_ptr<ieEvent>& event);
    virtual void onExitFrame(const std::shared_ptr<ieEvent>& event);
    
    virtual void onAdded(const std::shared_ptr<ieEvent>& event);
    virtual void onRemoved(const std::shared_ptr<ieEvent>& event);
    virtual void onUpdateTouchMask(const std::shared_ptr<ieEvent>& event);
    
    ieDisplayObjectContainer(const glm::vec4& frame);
    
public:
    
    virtual ~ieDisplayObjectContainer(void);
    
    void addChild(const std::shared_ptr<ieDisplayObjectContainer>& child);
    void addChildAt(const std::shared_ptr<ieDisplayObjectContainer>& child, i32 index);
    
    void setVisible(bool value);
    void setBatched(bool value);
    
    void setShader(ieSharedShaderRef shader, bool isUpdateHierarchy = false);
    
    bool contains(const std::shared_ptr<ieDisplayObjectContainer>& child) const;
    
    std::shared_ptr<ieDisplayObjectContainer> getChildAt(i32 index) const;
    std::shared_ptr<ieDisplayObjectContainer> getChildByName(const std::string& name) const;
    
    i32 getChildIndex(const std::shared_ptr<ieDisplayObjectContainer>& child) const;
    std::vector<std::shared_ptr<ieDisplayObjectContainer>> getObjectsUnderPoint(const glm::vec2& point) const;
    
    void removeChild(const std::shared_ptr<ieDisplayObjectContainer>& child);
    void removeChildAt(i32 index);
    void removeChildren(i32 startIndex, i32 endIndex);
    
    void setChildIndex(const std::shared_ptr<ieDisplayObjectContainer>& child, i32 index);
    void swapChildren(const std::shared_ptr<ieDisplayObjectContainer>& child_01,
                      const std::shared_ptr<ieDisplayObjectContainer>& child_02);
    void swapChildrenAt(i32 index_01, i32 index_02);
    void sortChildrens(void);
    
};

#endif
