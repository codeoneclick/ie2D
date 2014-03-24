//
//  ieBatchMgr.h
//  ieCore
//
//  Created by sergey.sergeev on 3/24/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef __ieCore__ieBatchMgr__
#define __ieCore__ieBatchMgr__

#include "ieObject.h"

class ieBatch;
class ieMaterial;
class ieShape;
class ieCamera;

class ieBatchMgr : public ieObject
{
private:
    
protected:
    
    std::unordered_map<std::string, std::shared_ptr<ieBatch>> m_batches;
    std::shared_ptr<ieCamera> m_camera;
    
public:
    ieBatchMgr(const std::shared_ptr<ieCamera>& camera);
    ~ieBatchMgr(void);
    
    void begin(void);
    void end(void);
    void draw(void);
    
    void batch(const ieMaterial* material,
               const std::shared_ptr<ieShape>& shape,
               const glm::mat4& matrix);
};

#endif
