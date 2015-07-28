#ifndef TUE_SERIALIZATION_FILE_H_
#define TUE_SERIALIZATION_FILE_H_

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

namespace tue
{

// ----------------------------------------------------------------------------------------------------

class Binary
{

public:

    virtual const char* ptr() const = 0;
    virtual unsigned int size() const = 0;
    virtual char* allocate(unsigned int size) = 0;

};

// ----------------------------------------------------------------------------------------------------

typedef boost::shared_ptr<Binary> BinaryPtr;
typedef boost::shared_ptr<const Binary> BinaryConstPtr;

// ----------------------------------------------------------------------------------------------------

class VectorBinary : public Binary
{

public:

    const char* ptr() const
    {
        return &data_[0];
    }

    unsigned int size() const
    {
        return data_.size();
    }

    char* allocate(unsigned int size)
    {
        data_.resize(data_.size() + size);
        return &data_.back() - size + 1;
    }

    std::vector<char>& vector() { return data_; }

    const std::vector<char>& vector() const { return data_; }

private:

    std::vector<char> data_;

};

// ----------------------------------------------------------------------------------------------------

class Package
{

public:

    void set_meta_data(const std::string meta_data) { meta_data_ = meta_data; }

    const std::string& meta_data() const { return meta_data_; }

    unsigned int addBinary(const BinaryConstPtr& bin) { binaries_.push_back(bin); return binaries_.size() - 1; }

    const std::vector<BinaryConstPtr>& binaries() const { return binaries_; }

private:

    std::string meta_data_;

    std::vector<BinaryConstPtr> binaries_;

};


} // end namespace tue

#endif
