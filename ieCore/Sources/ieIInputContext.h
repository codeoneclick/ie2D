//
//  ieIInputContext.h
//  ieCore
//
//  Created by sergey.sergeev on 4/4/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieIInputContext__
#define __ieCore__ieIInputContext__

#include "ieCommon.h"
#include "ieEnums.h"

class ieIOGLWindow;
class ieTouchRecognizer;

class ieIInputContext
{
private:
    
protected:
    
    std::shared_ptr<ieTouchRecognizer> m_touchRecognizer;
    
public:
    
    ieIInputContext();
    virtual ~ieIInputContext(void);
    
    static std::shared_ptr<ieIInputContext> createInputContext(const std::shared_ptr<ieIOGLWindow>& window,
                                                               E_PLATFORM_API api);
    
    void tapRecognizerPressed(const glm::ivec2& _point);
    void tapRecognizerMoved(const glm::ivec2& _point);
    void tapRecognizerReleased(const glm::ivec2& _point);
    
    std::shared_ptr<ieTouchRecognizer> getTouchRecognizer(void);
};

#endif
