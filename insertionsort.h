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
        //http://www.stoimen.com/blog/2012/02/13/computer-algorithms-insertion-sort/
      }
    }

    /*template <typename T, size_t S>
    void sortRange(std::array<T,S>& a, size_t l, size_t h) {
      size_t i,j;
      for (i = l; i < h; ++i) {
        for (j = i; j > 0 && a[j] < a[j - 1]; --j)
          swap(a[j], a[j-1]);
      }
    }*/
  }
}

#endif // INSERTIONSORT_H
