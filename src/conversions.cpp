#include "tue/serialization/conversions.h"

namespace tue
{
namespace serialization
{

// ----------------------------------------------------------------------------------------------------

void convert(Archive& a, std::vector<unsigned char>& data)
{
    convert(a.stream(), data, 4);  // 4 = offset for the archive version (4-byte int)
}

// ----------------------------------------------------------------------------------------------------

void convert(std::vector<unsigned char>& data, Archive& a)
{
    convert(data, a.stream(), 4);  // 4 = offset for the archive version (4-byte int)
}

// ----------------------------------------------------------------------------------------------------

void convert(std::istream& s, std::vector<unsigned char>& data, int d_offset)
{   
    // get its size:
    s.seekg(0, std::ios::end);
    int size = s.tellg();
    s.seekg(0, std::ios::beg);

    data.resize(size + d_offset);
    s.read((char*)&data[d_offset], size);
}

// ----------------------------------------------------------------------------------------------------

void convert(const std::vector<unsigned char>& data, std::ostream& s, int d_offset)
{   
    s.write((char*)&data[d_offset], data.size() - d_offset);
}

}

}
