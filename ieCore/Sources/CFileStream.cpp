//
//  CFileStream.cpp
//  ieCore
//
//  Created by sergey.sergeev on 1/27/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "CFileStream.h"


namespace std
{
    memstream::memstream(char* _data, size_t _size):
    std::istream(&m_buffer),
    m_buffer(_data, _size),
    m_data(_data),
    m_size(_size)
    {
        rdbuf(&m_buffer);
    }
    
    size_t memstream::size(void)
    {
        return m_size;
    }
    
    i8* memstream::data(void)
    {
        return m_data;
    }
};

extern std::function<std::shared_ptr<std::istream>(const std::string& _filename)> kCommonRawFileStream = [](const std::string& _filename)
{
    return nullptr;
};

extern std::function<std::stringstream(const std::string& _filename)> kCommonStringFileStream;
extern std::function<std::shared_ptr<std::istream>(const std::string& _filename)> kNDKRawFileStream;
extern std::function<std::stringstream(const std::string& _filename)> kNDKStringFileStream;
extern std::function<std::shared_ptr<std::istream>(const std::string& _filename)> kQTRawFileStream;
extern std::function<std::stringstream(const std::string& _filename)> kQTStringFileStream;
