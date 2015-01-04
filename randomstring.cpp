#include <cstdlib>
#include "randomstring.h"

namespace testing {
  std::string randstr(size_t range) {
    size_t length = rand() % range + 1; // this includes even empty strings!
    char str[length];
    str[length-1] = '\0';
    size_t i = 0;
    int r;

    for(i = 0; i < length-1; ++i) { //length-1 for the '\0' at the end
      for(;;) {
        r = rand() % 57 + 65; //interval between 65 ('A') and 65+57=122 ('z')
        if((r >= 65 && r <= 90) || (r >= 97 && r <= 122)) { // exclude all characters between '[' and '`'
          str[i] = (char)r;
          break;
        }
      }
    }

    return std::string(str);
  }

  std::string randstr(size_t range, unsigned int seed) {
    // Make sure that following rand() calls generate values from a set based on the given seed
    srand(seed);

    size_t length = rand() % range + 1; // this includes even empty strings!
    char str[length];
    str[length-1] = '\0';
    size_t i = 0;
    int r;

    for(i = 0; i < length-1; ++i) { //length-1 for the '\0' at the end
      for(;;) {
        r = rand() % 57 + 65; //interval between 65 ('A') and 65+57=122 ('z')
        if((r >= 65 && r <= 90) || (r >= 97 && r <= 122)) { // exclude all characters between '[' and '`'
          str[i] = (char)r;
          break;
        }
      }
    }

    return std::string(str);
  }
}
