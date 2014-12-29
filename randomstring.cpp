#include <cstdlib>
#include "randomstring.h"

std::string rand(size_t range) {
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
