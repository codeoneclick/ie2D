//
//  ieBatchMgr.cpp
//  ieCore
//
//  Created by sergey.sergeev on 3/24/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieBatchMgr.h"
#include "ieMaterial.h"
#include "ieBatch.h"

ieBatchMgr::ieBatchMgr(const std::shared_ptr<ieCamera>& camera) :
m_camera(camera)
{
    assert(m_camera != nullptr);
    m_description = "ieBatchMgr";
}

ieBatchMgr::~ieBatchMgr(void)
{
    m_batches.clear();
}

void ieBatchMgr::batch(const ieMaterial* material,
                       const std::shared_ptr<ieShape>& shape,
                       const glm::mat4& matrix)
{
    std::string guid = material->getBatchGUID();
    std::shared_ptr<ieBatch> batch = nullptr;
    const auto& iterator = m_batches.find(guid);
    if(iterator == m_batches.end())
    {
        batch = std::make_shared<ieBatch>(m_camera, material);
        m_batches.insert(std::make_pair(guid, batch));
    } else {
        batch = iterator->second;
    }
    batch->batch(shape, matrix);
}

void ieBatchMgr::begin(void)
{
    std::for_each(m_batches.begin(), m_batches.end(), [this](const std::pair<std::string, std::shared_ptr<ieBatch>> iterator){
        iterator.second->begin();
    });
}

void ieBatchMgr::end(void)
{
    std::for_each(m_batches.begin(), m_batches.end(), [this](const std::pair<std::string, std::shared_ptr<ieBatch>> iterator){
        iterator.second->end();
    });
}

void ieBatchMgr::draw(void)
{
    std::for_each(m_batches.begin(), m_batches.end(), [this](const std::pair<std::string, std::shared_ptr<ieBatch>> iterator){
        iterator.second->draw();
    });
}
