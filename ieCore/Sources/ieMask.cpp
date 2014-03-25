//
//  ieMask.cpp
//  ieCore
//
//  Created by sergey.sergeev on 3/21/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieMask.h"
#include "ieEvent.h"
#include "ieShape.h"
#include "ieShader.h"
#include "ieStage.h"
#include "ieCamera.h"
#include "ieResourceAccessor.h"

ieMask::ieMask(const glm::vec4& frame,
               const std::string& filename) :
ieDisplayObject(frame),
m_texture(nullptr),
m_imageFilename(filename)
{
    
}

ieMask::~ieMask(void)
{
    
}

void ieMask::begin(const std::shared_ptr<ieDisplayObjectContainer>& parent)
{
    m_parent = parent;
    ieMask::onUpdate(nullptr);
    
    if(m_active &&
       m_visible)
    {
        glEnable(GL_STENCIL_TEST);
        glClear(GL_STENCIL_BUFFER_BIT);
        
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glStencilFunc(GL_NEVER, 0xFF, 0xFF);
        glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
    }
}

void ieMask::end(void)
{
    if(m_active &&
       m_visible)
    {
        glDisable(GL_STENCIL_TEST);
    }
}

void ieMask::onUpdate(const std::shared_ptr<ieEvent>& event)
{
    ieDisplayObject::onUpdate(event);
}

void ieMask::onDraw(const std::shared_ptr<ieEvent>& event)
{
    if(m_active &&
       m_visible)
    {
        assert(m_camera != nullptr);
        
        ieMaterial::bind();
        
        m_shader->setMatrix4x4(m_localTransformation, E_SHADER_UNIFORM_MODELVIEW);
        m_shader->setMatrix4x4(m_camera->getProjection(), E_SHADER_UNIFORM_PROJECTION);
        m_shape->bind(m_shader->getAttributes());
        m_shape->draw();
        m_shape->unbind(m_shader->getAttributes());
        
        ieMaterial::unbind();
        
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glStencilFunc(GL_EQUAL, 0xFF, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    }
}

void ieMask::onEnterFrame(const std::shared_ptr<ieEvent>& event)
{
    
}

void ieMask::onExitFrame(const std::shared_ptr<ieEvent>& event)
{
    
}

void ieMask::onAdded(const std::shared_ptr<ieEvent>& event)
{
    m_resourceAccessor = std::static_pointer_cast<ieResourceAccessor>(event->getObjectWithKey("resourceAccessor"));
    assert(m_resourceAccessor != nullptr);
    
    m_stage = std::static_pointer_cast<ieStage>(event->getObjectWithKey("stage"));
    assert(m_stage != nullptr);
    
    m_camera = std::static_pointer_cast<ieCamera>(event->getObjectWithKey("camera"));
    assert(m_camera != nullptr);
    
    ieMaterial::setBlending(false);
    ieMaterial::setBlendingFunctionSource(GL_SRC_ALPHA);
    ieMaterial::setBlendingFunctionDestination(GL_ONE_MINUS_SRC_ALPHA);
    ieMaterial::setCulling(false);
    ieMaterial::setDepthTest(false);
    
    m_shader = m_resourceAccessor->getShader(ieShaderV2T2M_vert, ieShaderV2T2M_frag, ieObject::shared_from_this());
    ieMaterial::setShader(m_shader);
    
    glm::vec4 frame = ieDisplayObject::createShapePositionAttributes();
    m_shape = std::make_shared<ieShape>(frame);
    ieDisplayObject::updateShapeTexcoordAttributes(m_shape);
    ieDisplayObject::updateShapeColorAttributes(m_shape);
}

void ieMask::onRemoved(const std::shared_ptr<ieEvent>& event)
{
    m_shader->removeOwner(ieObject::shared_from_this());
    m_shader = nullptr;
    m_shape = nullptr;
    ieMaterial::setShader(nullptr);

}