#pragma once
#include <fstream>
#include <vector>
#include <iostream>

#include "filter.h"
#include "bmp_headers.h"

class BMP {
public:
    BMPHeader bmp_header;
    DIBHeader dib_header;
    std::vector <std::vector <Color> > pixel_array;

    BMP(const std::string& filename);
    void Read(const std::string& filename);
    void Write(const std::string& filename);

    void ApplyFilter(const Filter& fl);
    
private:

};