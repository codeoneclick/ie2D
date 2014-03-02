//
//  ieSequence.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieSequence.h"

ieSequence::ieSequence(const std::string& filename) :
ieResource(E_RESOURCE_TYPE_SEQUENSE)
{
    Json::Value root;
    Json::Reader reader;
    std::ifstream stream(filename, std::ifstream::binary);
    bool success = reader.parse(stream, root, false);
    if (!success)
    {
        std::cout<<reader.getFormatedErrorMessages()<<std::endl;
    }
}

ieSequence::~ieSequence(void)
{
    
}