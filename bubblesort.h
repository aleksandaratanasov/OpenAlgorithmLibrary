#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <cstdlib>
#include <array>

using std::array;

namespace oal {
  namespace sorting {
    namespace bubblesort {
      template <typename T, size_t S>
      void sort(array<T,S>& a) {
        if(S < 2)
          return;

        size_t index = 0;
        size_t d;
        T pivot;

        for(; index < a.size()-1; ++index)
          for(d = 0; d < (S - index - 1); ++d)
            if(a[d] > a[d + 1]) {
              pivot = a[d];
              a[d] = a[d + 1];
              a[d + 1] = pivot;
            }
      }
    }
  }
}

#endif // BUBBLESORT_H
