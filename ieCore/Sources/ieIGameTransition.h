//
//  ieIGameTransition.h
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieIGameTransition__
#define __ieCore__ieIGameTransition__

#include "ieCommon.h"
#include "ieStage.h"

class ieResourceAccessor;
class ieIOGLWindow;
class ieIGraphicsContext;
class ieIGameTransition : public ieStage
{
private:
    
    ieEventDispatcherFunctionShared m_functionOnTransitionRegister;
    ieEventDispatcherFunctionShared m_functionOnTransitionUnregister;
    
    ieEventDispatcherFunctionShared m_functionOnTransitionEnter;
    ieEventDispatcherFunctionShared m_functionOnTransitionExit;
    
    ieEventDispatcherFunctionShared m_functionOnPresentFrame;
    
    std::shared_ptr<ieShape> m_shape;
    std::shared_ptr<ieShader> m_shader;
    std::shared_ptr<ieMaterial> m_material;
    
protected:
    
    std::string m_name;
    std::shared_ptr<ieIOGLWindow> m_window;
    std::shared_ptr<ieIGraphicsContext> m_graphicsContext;
    std::shared_ptr<ieResourceAccessor> m_resourceAccessor;
    
    virtual void onRegistered(const std::shared_ptr<ieEvent>& event);
    virtual void onUnregistered(const std::shared_ptr<ieEvent>& event);
    
    virtual void onEnter(const std::shared_ptr<ieEvent>& event);
    virtual void onExit(const std::shared_ptr<ieEvent>& event);
    
    virtual void onUpdate(const std::shared_ptr<ieEvent>& event);
    virtual void onDraw(const std::shared_ptr<ieEvent>& event);
    virtual void onEnterFrame(const std::shared_ptr<ieEvent>& event);
    virtual void onExitFrame(const std::shared_ptr<ieEvent>& event);
    virtual void onPresentFrame(const std::shared_ptr<ieEvent>& event);
    
public:
    
    ieIGameTransition(const std::string& name,
                      const std::shared_ptr<ieIOGLWindow>& window);
    virtual ~ieIGameTransition(void);
    
    std::string getName(void) const;
    
};

#endif
