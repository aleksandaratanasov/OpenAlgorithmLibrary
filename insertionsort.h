#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <array>
#include "swap.h"

namespace sorting {
  namespace insertionsort {
    namespace normal{
      template <typename T, size_t S>
      void sort(std::array<T,S>& a) {
        size_t i,j;
        for (i = 1; i < S; ++i) {
          for (j = i; j > 0 && a[j] < a[j - 1]; --j)
            swap(a[j], a[j-1]);
        }
      }
    }

    namespace withguard {
      template <typename T, size_t S>
      void sort(std::array<T,S>& a) {
        //http://coderevisited.com/insertion-sort/
        size_t i = S-1, j = 0;

        for(; i > 0; --i)
          if(a[i] < a[i-1]) swap(a[i], a[i-1]);

        for(i = 2; i < S; ++i)
          for(j = i; a[j] < a[j-1]; --j)
            swap(a[j], a[j-1]);
      }
    }

    // STATUS: not implemented
    namespace withguardidxtransform {
      template <typename T, size_t S>
      void sort(std::array<T,S>& a) {

      }
    }

    template <typename T, size_t S>
    void sortRange(array<T,S>& a, size_t lo, size_t hi) {
      size_t i = lo, j;

      for (; i <= hi; ++i)
        for (j = i; j > lo && a[j] < a[j-1]; --j)
          swap(a, j, j-1);
    }
  }
}

#endif // INSERTIONSORT_H
