//
//  ieMovieClip.h
//  ieCore
//
//  Created by sergey.sergeev on 2/3/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieMovieClip__
#define __ieCore__ieMovieClip__

#include "ieSprite.h"

class ieMovieClip : public ieSprite
{
private:
    
protected:
    
    virtual void onUpdate(const std::shared_ptr<ieEvent>& event);
    virtual void onDraw(const std::shared_ptr<ieEvent>& event);
    virtual void onEnterFrame(const std::shared_ptr<ieEvent>& event);
    virtual void onExitFrame(const std::shared_ptr<ieEvent>& event);
    
    virtual void onAdded(const std::shared_ptr<ieEvent>& event);
    virtual void onRemoved(const std::shared_ptr<ieEvent>& event);
    
    std::string m_animationName;
    ui32 m_namedAnimationStartFrameIndex;
    ui32 m_namedAnimationEndFrameIndex;
    ui32 m_currentAnimationFrameIndex;
    bool m_isLooped;
    bool m_isStoped;
    
    void invokeAnimation(void);
    bool gotoNextFrame(void);
    
public:
    ieMovieClip(const glm::vec4& frame,
                const std::string& filename,
                const std::shared_ptr<ieColor>& color = nullptr);
    
    ~ieMovieClip(void);
    
    void gotoAndStop(ui32 index);
    void gotoAndPlay(bool isLooped = false, const std::string& animationName = "");
};

#endif
