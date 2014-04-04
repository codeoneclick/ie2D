//
//  ieTouchRecognizer.h
//  ieCore
//
//  Created by sergey.sergeev on 4/4/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieTouchRecognizer__
#define __ieCore__ieTouchRecognizer__

#include "ieObject.h"
#include "iePredefined.h"

class ieTouchRecognizer : public ieObject
{
private:
    
protected:
    
    std::set<ieSharedInteractiveObject> m_interactiveObjects;
    ieSharedShader m_shader;
    
public:
    
    ieTouchRecognizer(void);
    ~ieTouchRecognizer(void);
    
    void registerInteractiveObject(ieSharedInteractiveObjectRef interactiveObject);
    void unregisterInteractiveObject(ieSharedInteractiveObjectRef interactiveObject);
    
    void updateTouchMask(void);
};

#endif
