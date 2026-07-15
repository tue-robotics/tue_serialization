#include "tue/serialization/conversions.h"
#include "tue/serialization/archive.h"
#include "tue/serialization/output_archive.h"

#include <cstring> // std::memcpy
#include <ios>
#include <istream>
#include <ostream>
#include <vector>

namespace tue::serialization
{

// ----------------------------------------------------------------------------------------------------

void convert(Archive& a, std::vector<unsigned char>& data)
{
    int version = a.version();
    convert(a.stream(), data, sizeof(version));

    // Fill version bytes
    std::memcpy(data.data(), &version, sizeof(version));
}

// ----------------------------------------------------------------------------------------------------

void convert(const Archive& a, std::ostream& out)
{
    // Write the version to out
    [[maybe_unused]] OutputArchive a_out(out);

    // Write data to out
    out << a.stream().rdbuf();
}

// ----------------------------------------------------------------------------------------------------

void convert(std::istream& s, Archive& a)
{
    std::vector<unsigned char> data;
    convert(s, data);
    convert(data, a);
}

// ----------------------------------------------------------------------------------------------------

void convert(std::istream& s, std::vector<unsigned char>& data, int d_offset)
{
    // get its size:
    s.seekg(0, std::ios::end);
    const std::streamsize size = s.tellg();
    s.seekg(0, std::ios::beg);

    data.resize(size + d_offset);
    s.read(reinterpret_cast<char*>(data.data() + d_offset), size);
}

// ----------------------------------------------------------------------------------------------------

void convert(std::vector<unsigned char>& data, Archive& a)
{
    // Read version (int)
    std::memcpy(&a.version_, data.data(), sizeof(a.version_));

    // Read the rest
    convert(data, a.stream(), sizeof(a.version_));
}

// ----------------------------------------------------------------------------------------------------

void convert(const std::vector<unsigned char>& data, std::ostream& s, int d_offset)
{
    s.write(reinterpret_cast<const char*>(data.data() + d_offset),
            static_cast<std::streamsize>(data.size() - d_offset));
}

} // namespace tue::serialization
