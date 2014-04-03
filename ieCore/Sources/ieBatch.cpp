//
//  ieBatch.cpp
//  ieCore
//
//  Created by sergey.sergeev on 3/24/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieBatch.h"
#include "ieVertexBuffer.h"
#include "ieIndexBuffer.h"
#include "ieShape.h"
#include "ieMaterial.h"
#include "ieShader.h"
#include "ieCamera.h"

const ui32 kMaxVertices = 65535 / 4; // 16k vertices
const ui32 kMaxIndices = 65535 / 2;  // 32k indices

ieBatch::ieBatch(const std::shared_ptr<ieCamera>& camera,
                 ieSharedMaterialRef material) :
m_material(material),
m_camera(camera),
m_numActiveVertices(0),
m_numActiveIndices(0)
{
    m_vertexBuffer = std::make_shared<ieVertexBuffer>(kMaxVertices, GL_STREAM_DRAW);
    ieVertex* vertexData = m_vertexBuffer->lock();
    memset(vertexData, 0x0, kMaxVertices * sizeof(ieVertex));
    m_vertexBuffer->unlock();
    
    m_indexBuffer = std::make_shared<ieIndexBuffer>(kMaxIndices, GL_STREAM_DRAW);
    ui16* indexData = m_indexBuffer->lock();
    memset(indexData, 0x0, kMaxIndices * sizeof(ui16));
    m_indexBuffer->unlock();
}

ieBatch::~ieBatch(void)
{
    
}

void ieBatch::begin(void)
{
    m_numActiveVertices = 0;
    m_numActiveIndices = 0;
    
    m_shapes.clear();
    m_matrices.clear();
}

void ieBatch::end(void)
{
    ui32 numVertices = 0;
    ui32 numIndices = 0;
    
    assert(m_shapes.size() == m_matrices.size());
    
    ui16 *mainIndexData = m_indexBuffer->lock();
    ieVertex *mainVertexData = m_vertexBuffer->lock();
    
    for(ui32 i = 0; i < m_shapes.size(); ++i)
    {
        std::shared_ptr<ieShape> shape = m_shapes[i];
        glm::mat4& matrix = m_matrices[i];
        
        ui16 *currentIndexData = shape->getIndexBuffer()->lock();
        ieVertex *currentVertexData = shape->getVertexBuffer()->lock();
        
        for(ui32 j = 0; j < shape->getIndexBuffer()->getSize(); ++j)
        {
            mainIndexData[numIndices + j] = currentIndexData[j] + numVertices;
        }
        
        for(ui32 j = 0; j < shape->getVertexBuffer()->getSize(); ++j)
        {
            mainVertexData[numVertices + j].m_position = glm::transform(currentVertexData[j].m_position, matrix);
            mainVertexData[numVertices + j].m_texcoord = currentVertexData[j].m_texcoord;
            mainVertexData[numVertices + j].m_color = currentVertexData[j].m_color;
        }
        numVertices += shape->getVertexBuffer()->getSize();
        numIndices += shape->getIndexBuffer()->getSize();
    }
    m_numActiveVertices = numVertices;
    m_numActiveIndices = numIndices;
    
    m_vertexBuffer->unlock(m_numActiveVertices);
    m_indexBuffer->unlock(m_numActiveIndices);
}

void ieBatch::batch(ieSharedShapeRef shape, const glm::mat4& matrix)
{
    m_shapes.push_back(shape);
    m_matrices.push_back(matrix);
}

void ieBatch::draw(void)
{
    assert(m_camera != nullptr);
    assert(m_material != nullptr);
    m_material->bind();
    
    m_material->getShader()->setMatrix4x4(glm::mat4(1.0), E_SHADER_UNIFORM_MODELVIEW);
    m_material->getShader()->setMatrix4x4(m_camera->getProjection(), E_SHADER_UNIFORM_PROJECTION);
    
    m_vertexBuffer->bind(m_material->getShader()->getAttributes());
    m_indexBuffer->bind();
    
    glDrawElements(GL_TRIANGLES, m_numActiveIndices, GL_UNSIGNED_SHORT, 0);
    
    m_material->unbind();
    
    m_vertexBuffer->unbind(m_material->getShader()->getAttributes());
    m_indexBuffer->unbind();
}