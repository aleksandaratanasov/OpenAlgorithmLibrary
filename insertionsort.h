#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <cstdlib>
#include <array>

namespace sorting {
  namespace insertionsort {
    template <typename T>
    void swap(T& t1, T& t2) {
      //printf("Swapping [%d] and [%d]\n", *t1, *t2);
      T temp = t1;
      t1 = t2;
      t2 = temp;
    }

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
        for (i = 1; i < S; ++i) {
          for (j = i; j > 0 && a[j] < a[j - 1]; --j)
            swap(a[j], a[j-1]);
        }
      }

      template <typename T, size_t S>
      void sortRange(std::array<T,S>& a, size_t l, size_t h) {
        size_t i,j;
        for (i = l; i < h; ++i) {
          for (j = i; j > 0 && a[j] < a[j - 1]; --j)
            swap(a[j], a[j-1]);
        }
      }
    }
  }
}

#endif // INSERTIONSORT_H
