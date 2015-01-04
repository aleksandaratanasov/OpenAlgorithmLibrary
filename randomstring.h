#ifndef RANDOMSTRING_H
#define RANDOMSTRING_H

#include <string>

namespace testing {
  std::string randstr(size_t range);
  std::string randstr(size_t range, unsigned int seed);
}

#endif // RANDOMSTRING_H
