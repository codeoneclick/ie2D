//
//  CFileStream.h
//  ieCore
//
//  Created by sergey.sergeev on 1/27/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#ifndef CFileStream_h
#define CFileStream_h

#include "HCommon.h"

namespace std
{
    class memstream: public std::istream
    {
    private:
        
        class membuf : public std::streambuf
        {
        public:
            
            membuf(char* _data, size_t _size)
            {
                setp(_data, _data + _size);
                setg(_data, _data, _data + _size);
            };
        };
        membuf m_buffer;
        
    protected:
        
        char* m_data;
        size_t m_size;
        
    public:
        
        memstream(char* _data, size_t _size);
        
        size_t size(void);
        i8* data(void);
    };
};

namespace CFileStream
{
    extern std::function<std::shared_ptr<std::istream>(const std::string& _filename)> kCommonRawFileStream;
    extern std::function<std::stringstream(const std::string& _filename)> kCommonStringFileStream;
    extern std::function<std::shared_ptr<std::istream>(const std::string& _filename)> kNDKRawFileStream;
    extern std::function<std::stringstream(const std::string& _filename)> kNDKStringFileStream;
    extern std::function<std::shared_ptr<std::istream>(const std::string& _filename)> kQTRawFileStream;
    extern std::function<std::stringstream(const std::string& _filename)> kQTStringFileStream;
};

#endif
