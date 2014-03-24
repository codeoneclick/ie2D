//
//  ieBatch.h
//  ieCore
//
//  Created by sergey.sergeev on 3/24/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieBatch__
#define __ieCore__ieBatch__

#include "ieCommon.h"

class ieMaterial;
class ieShape;
class ieVertexBuffer;
class ieIndexBuffer;
class ieCamera;

class ieBatch
{
private:
    
    std::shared_ptr<ieVertexBuffer> m_vertexBuffer;
    std::shared_ptr<ieIndexBuffer> m_indexBuffer;
    
    ui32 m_numActiveVertices;
    ui32 m_numActiveIndices;
    
    std::shared_ptr<ieCamera> m_camera;
    
protected:
    
    const ieMaterial* m_material;
    std::vector<std::shared_ptr<ieShape>> m_shapes;
    std::vector<glm::mat4> m_matrices;
    
public:
    ieBatch(const std::shared_ptr<ieCamera>& camera,
            const ieMaterial* material);
    ~ieBatch(void);
    
    void begin(void);
    void end(void);
    void draw(void);
    
    void batch(const std::shared_ptr<ieShape>& shape, const glm::mat4& matrix);
};

#endif
