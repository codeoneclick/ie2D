//
//  ieImage.cpp
//  ieCore
//
//  Created by sergey.sergeev on 2/5/14.
//  Copyright (c) 2014 Sergey Sergeev. All rights reserved.
//

#include "ieImage.h"


ieImage::ieImage(const std::string& filename) :
m_data(nullptr),
m_width(0),
m_height(0)
{
    png_byte header[8];
    FILE *imagefile = fopen(filename.c_str(), "rb");
    assert(imagefile != 0);
    fread(header, 1, 8, imagefile);
    if (png_sig_cmp(header, 0, 8))
    {
        assert(false);
        std::cout<<"error: "<<"filename"<<"is not a PNG."<<std::endl;
        fclose(imagefile);
        return;
    }
    
    png_structp pngstruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!pngstruct)
    {
        std::cout<<"error: png_create_read_struct returned 0."<<std::endl;
        fclose(imagefile);
        return;
    }
    
    png_infop pnginfo = png_create_info_struct(pngstruct);
    if (!pnginfo)
    {
        std::cout<<"error: png_create_info_struct returned 0."<<std::endl;
        png_destroy_read_struct(&pngstruct, (png_infopp)NULL, (png_infopp)NULL);
        fclose(imagefile);
        return;
    }
    
    png_infop pngendinfo = png_create_info_struct(pngstruct);
    if (!pngendinfo)
    {
        std::cout<<"error: png_create_info_struct returned 0."<<std::endl;
        png_destroy_read_struct(&pngstruct, &pnginfo, (png_infopp) NULL);
        fclose(imagefile);
        return;
    }
    
    if (setjmp(png_jmpbuf(pngstruct)))
    {
        std::cout<<"error from libpng."<<std::endl;
        png_destroy_read_struct(&pngstruct, &pnginfo, &pngendinfo);
        fclose(imagefile);
        return;
    }
    
    png_init_io(pngstruct, imagefile);
    png_set_sig_bytes(pngstruct, 8);
    png_read_info(pngstruct, pnginfo);
    i32 bitdepth, colortype;
    
    png_get_IHDR(pngstruct, pnginfo, &m_width, &m_height, &bitdepth, &colortype,
                 NULL, NULL, NULL);
    m_format = colortype;

    png_read_update_info(pngstruct, pnginfo);
    i32 rowbytes = png_get_rowbytes(pngstruct, pnginfo);
    rowbytes += 3 - ((rowbytes - 1) % 4);
    
    m_data = (png_byte *)malloc(rowbytes * m_height * sizeof(png_byte) + 15);
    if (m_data == nullptr)
    {
        std::cout<<"error: could not allocate memory for PNG image data."<<std::endl;
        png_destroy_read_struct(&pngstruct, &pnginfo, &pngendinfo);
        fclose(imagefile);
        return;
    }
    
    png_bytep *rowpointers = (png_bytep *)malloc(m_height * sizeof(png_bytep));
    if (rowpointers == nullptr)
    {
        std::cout<<"error: could not allocate memory for PNG row pointers."<<std::endl;
        png_destroy_read_struct(&pngstruct, &pnginfo, &pngendinfo);
        free(m_data);
        fclose(imagefile);
        return;
    }
    for (ui32 i = 0; i < m_height; ++i)
    {
        rowpointers[m_height - 1 - i] = m_data + i * rowbytes;
    }
    png_read_image(pngstruct, rowpointers);
    png_destroy_read_struct(&pngstruct, &pnginfo, &pngendinfo);
    free(rowpointers);
    fclose(imagefile);
}

ieImage::~ieImage(void)
{
    
}

const png_byte* ieImage::getData(void) const
{
    assert(m_data != nullptr);
    return m_data;
}

const ui32 ieImage::getWidth(void) const
{
    assert(m_width != 0);
    return m_width;
}

const ui32 ieImage::getHeight(void) const
{
    assert(m_height != 0);
    return m_height;
}

const ui32 ieImage::getFormat(void) const
{
    ui32 format = GL_RGB;
    switch (m_format) {
        case PNG_COLOR_TYPE_RGB:
        {
            format = GL_RGB;
        }
            break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
        {
            format = GL_RGBA;
        }
            break;
            
        default:
            assert(false);
            break;
    }
    return format;
}