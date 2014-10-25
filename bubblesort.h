#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <cstdlib>
#include <array>

using std::array;

namespace sorting {
  namespace bubblesort {
  template <typename T, size_t S>
    void sort(std::array<T,S> &a) {
      size_t index = 0;
      size_t d;
      T swap;

      for(; index < (S - 1); ++index)
        for(d = 0; d < (S - index - 1); ++d)
          if(a[d] > a[d + 1])
          {
            swap = a[d];
            a[d] = a[d + 1];
            a[d + 1] = swap;
          }
    }
  }
}

#endif // BUBBLESORT_H
