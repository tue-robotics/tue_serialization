#include "tue/serialization/filesystem.h"

#include "tue/serialization/conversions.h"

#include <fstream>

namespace tue
{
namespace serialization
{

// ----------------------------------------------------------------------------------------------------

bool toFile(const Archive& a, const std::string& filename)
{
    // Open filestream
    std::ofstream f_out;
    f_out.open(filename.c_str(), std::ifstream::binary);

    if (!f_out.is_open())
        return false;

    // Copy archive content to file
    convert(a, f_out);

    // Close file
    f_out.close();

    return true;
}

// ----------------------------------------------------------------------------------------------------

bool fromFile(const std::string& filename, Archive& a)
{
    std::ifstream f_in;
    f_in.open(filename.c_str(), std::ifstream::binary);

    if (!f_in.is_open())
        return false;

    // Copy file content into archive
    convert(f_in, a);

    // Close file
    f_in.close();

    return true;
}

// ----------------------------------------------------------------------------------------------------

bool toFile(const Package& p, const std::string& filename)
{
    // Open filestream
    std::ofstream f_out;
    f_out.open(filename.c_str(), std::ifstream::binary);

    if (!f_out.is_open())
        return false;

    // Write version (4 byte unsigned int)
    unsigned int version = 0;
    f_out.write((char*)&version, sizeof(version));

    // Write meta-data size
    unsigned int meta_data_size = p.meta_data().size();
    f_out.write((char*)&meta_data_size, sizeof(meta_data_size));

    // Write meta-data (including trailing \0)
    f_out.write(p.meta_data().c_str(), p.meta_data().size() + 1);

    // Write binary table index size
    const std::vector<BinaryConstPtr>& binaries = p.binaries();
    unsigned int table_size = binaries.size();
    f_out.write((char*)&table_size, sizeof(table_size));

    // Write binary table index
    unsigned int offset = 0;
    for(unsigned int i = 0; i < binaries.size(); ++i)
    {
        offset += binaries[i]->size();
        f_out.write((char*)&offset, sizeof(offset));
    }

    // Write binaries
    for(unsigned int i = 0; i < binaries.size(); ++i)
    {
        const BinaryConstPtr& b = binaries[i];
        f_out.write(b->ptr(), b->size());
    }
}

// ----------------------------------------------------------------------------------------------------

bool fromFile(const std::string& filename, Package& p)
{
    std::ifstream f_in;
    f_in.open(filename.c_str(), std::ifstream::binary);

    if (!f_in.is_open())
        return false;

    // Read version
    unsigned int version;
    f_in.read((char*)&version, sizeof(version));

    // Read meta-data size
    unsigned int meta_data_size;
    f_in.read((char*)&meta_data_size, sizeof(meta_data_size));

    // Read meta-data (including trailing \0)
    char* buff = new char[meta_data_size + 1];
    f_in.read(buff, meta_data_size + 1);
    p.set_meta_data(buff);
    delete buff;  // TODO: get rid of temporary buffer

    // Read binary table index size
    unsigned int table_size;
    f_in.read((char*)&table_size, sizeof(table_size));

    // Read binary table index
    std::vector<unsigned int> bin_sizes(table_size);
    unsigned int offset = 0;
    for(unsigned int i = 0; i < table_size; ++i)
    {
        unsigned int next_offset;
        f_in.read((char*)&next_offset, sizeof(next_offset));

        bin_sizes[i] = next_offset - offset;
        offset = next_offset;
    }

    // Read binaries
    for(unsigned int i = 0; i < bin_sizes.size(); ++i)
    {
        unsigned int bin_size = bin_sizes[i];

        BinaryPtr bin(new VectorBinary);
        char* ptr = bin->allocate(bin_size);

        f_in.read(ptr, bin_size);

        p.addBinary(bin);
    }
}

// ----------------------------------------------------------------------------------------------------

}

}
