#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <array>
#include "swap.h"


#include <iostream>

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
        //http://algs4.cs.princeton.edu/21elementary/
        size_t i = S-1, j = 0;

        for (; i > 0; i--) {
          if (a[i] < a[i - 1]) {
            swap(a[i], a[i-1]);
          }
        }

//        std::cout << "Loop one over" << std::endl;

        for (i = 2; i < S; i++) {
//          std::cout << "outer[" << i << "] : inner[" << j << "]" << std::endl;
          for (j = i; a[j] < a[j - 1]; j--) {
//            std::cout << "outer[" << i << "] : inner[" << j << "]" << std::endl;
            swap(a[j], a[j-1]);
          }
//            if(i >= 4500)
//              std::cout << "outer[" << i << "] : inner[" << j << "]" << std::endl;
        }
      }
    }

    // STATUS: not implemented
//    namespace withguardidxtransform {
//      template <typename T, size_t S>
//      void sort(std::array<T,S>& a) {
//        //http://coderevisited.com/insertion-sort/
//        size_t i, j = 0;

//        T tmp;
//        for(i = 1; i < S; ++j) {
//          tmp = a[i];
//          for(j = i-1; (j > 0) && (a[j] < tmp); --j)
//            a[j+1] = a[j];
//          a[j+1] = tmp;
//        }
//      }
//    }

    namespace withguardidxtransform {
      template <typename T, size_t S>
      void sort(std::array<T,S>& a) {
        size_t r = S, l = 0;
        if (r == 0) return;

        size_t min = l;

        for (size_t i = l+1; i < (r+1); ++i)
          if (a[i] < a[min]) min = i;

        std::swap(a[l], a[min]);

        for (size_t i = l+2; i < r + 1; ++i) {
          T tmp = a[i];
          for (size_t j = i; tmp < a[--j];)
               swap(a[j + 1], a[j]);
        }
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
