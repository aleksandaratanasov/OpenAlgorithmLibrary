#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <cstdlib>
#include <array>

namespace sorting {
  namespace insertionsort {
    namespace normal{
      template <typename T, size_t S>
      void sort(std::array<T,S>& a) {
        size_t i,j;
        T value;

      }
    }

    namespace withguard {
      template <typename T, size_t S>
      void sort(std::array<T,S>& a) {
        size_t i,j;
        T guard;
        for (i = 1; i < S; ++i) {
          guard = a[i];
          for (j = i; j > 0 && guard < a[j - 1]; --j)
            a[j] = a[j - 1];
          a[j] = guard;
        }
      }
    }
  }
}

#endif // INSERTIONSORT_H
