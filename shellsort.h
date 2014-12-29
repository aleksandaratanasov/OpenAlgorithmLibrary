#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <cstdlib>
#include <array>

using std::array;

// TODO: Use a different implementation. The current one requires signed values for the looping
// which makes it impossible to use size_t because the resulting sorted array is sorted in a weird way
// (first come the positive sorted values, then - the negative sorted values)

namespace sorting {
  namespace shellsort {
    /*template <typename T>
    void swap(T& t1, T& t2) {
      T temp = t1;
      t1 = t2;
      t2 = temp;
    }

    template <typename T, size_t S>
    void sink(std::array<T,S> &a, size_t i, size_t len) {
      while (2*i <= len) {
          size_t j = 2*i;
          if (j < len && a[j-1] < a[j])
            j++;
          if (!(a[i] < a[j]))
            break;
          swap(a[i-1], a[j-1]);
          i = j;
      }
    }

    template <typename T, size_t S>
    void sort(std::array<T,S> &a) {
      for(size_t i = S/2; i > 0; --i)
        sink(a, i, S);

      size_t s = S;
      while(s > 1) {
        swap(a[0], a[--s]);
        sink(a, 1, s);
      }
    }*/

    template <typename T, size_t S>
    void sort(std::array<T,S> &a) {
      T k;
      size_t h = S, i, j;
      for (; h /= 2;)
//      for(; h >> 1;)
        for (i = h; i < S; ++i) {
          k = a[i];
          for (j = i; j >= h && k < a[j - h]; j -= h)
              a[j] = a[j - h];
          a[j] = k;
        }
    }
  }
}

#endif // SHELLSORT_H
