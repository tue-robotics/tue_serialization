#ifndef TUE_SERIALIZATION_OUTPUT_ARCHIVE_H_
#define TUE_SERIALIZATION_OUTPUT_ARCHIVE_H_

#include <iostream>

namespace tue
{
namespace serialization
{

class OutputArchive {

public:

    OutputArchive(std::ostream& stream, int version) : stream_(stream) {
        stream_.write((char*)&version, sizeof(version));
    }

    virtual ~OutputArchive() {}

    inline OutputArchive& operator<<(float f) { stream_.write((char*)&f, sizeof(f)); return *this; }

    inline OutputArchive& operator<<(double d) { stream_.write((char*)&d, sizeof(d)); return *this; }

    inline OutputArchive& operator<<(int i) { stream_.write((char*)&i, sizeof(i)); return *this; }

    inline OutputArchive& operator<<(std::string s) { stream_.write(s.c_str(), s.size() + 1); return *this; }

    inline std::ostream& getStream() { return stream_; }

protected:

    std::ostream& stream_;

};

}

}

#endif
