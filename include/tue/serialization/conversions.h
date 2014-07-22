#ifndef TUE_SERIALIZATION_CONVERSIONS_H_
#define TUE_SERIALIZATION_CONVERSIONS_H_

#include <istream>
#include <vector>

#include "input_archive.h"
#include "output_archive.h"

namespace tue
{
namespace serialization
{

void convert(std::istream& s, std::vector<unsigned char>& data);

void convert(const std::vector<unsigned char>& data, std::ostream& s);

}

}

#endif
