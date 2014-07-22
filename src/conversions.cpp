#include "tue/serialization/conversions.h"

namespace tue
{
namespace serialization
{

// ----------------------------------------------------------------------------------------------------

void convert(std::istream& s, std::vector<unsigned char>& data)
{
    // get its size:
    s.seekg(0, std::ios::end);
    int size = s.tellg();
    s.seekg(0, std::ios::beg);

    data.resize(size);
    s.read((char*)&data[0], size);
}

// ----------------------------------------------------------------------------------------------------

void convert(const std::vector<unsigned char>& data, std::ostream& s)
{
    s.write((char*)&data[0], data.size());
}

}

}
