#ifndef TUE_SERIALIZATION_FILESYSTEM_H_
#define TUE_SERIALIZATION_FILESYSTEM_H_

#include <istream>
#include <string>
#include <vector>

#include "archive.h"
#include "input_archive.h"
#include "output_archive.h"

namespace tue
{
namespace serialization
{

bool toFile(const Archive& a, const std::string& filename);

bool fromFile(const std::string& filename, Archive& a);

} // namespace serialization

} // namespace tue

#endif
