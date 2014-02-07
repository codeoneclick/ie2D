//
//  ieShape.h
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieShape__
#define __ieCore__ieShape__

#include "ieCommon.h"

class ieVertexBuffer;
class ieIndexBuffer;

class ieShape
{
private:
    
protected:
    
    std::shared_ptr<ieVertexBuffer> m_vertexBuffer;
    std::shared_ptr<ieIndexBuffer> m_indexBuffer;
    
public:
    
    ieShape(void);
    ~ieShape(void);
    
    std::shared_ptr<ieVertexBuffer> getVertexBuffer(void) const;
    std::shared_ptr<ieIndexBuffer> getIndexBuffer(void) const;
    
    const ui32 getNumVertexes(void) const;
    const ui32 getNumIndexes(void) const;
    
    void bind(const i32* attributes);
    void draw(void);
    void unbind(const i32* attributes);
};

#endif
