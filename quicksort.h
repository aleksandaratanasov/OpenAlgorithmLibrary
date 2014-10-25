#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <cstdlib>
#include <cstdio>
#include <array>

using std::array;

namespace sorting {
  namespace quicksort {
    template <typename T>
    void swap(T& t1, T& t2) {
      printf("Swapping [%d] and [%d]\n", t1, t2);
      T temp = t1;
      t1 = t2;
      t2 = temp;
    }

    template <typename T, size_t S>
    size_t partition(std::array<T,S> &a, size_t low, size_t high) {
      size_t left, right;
      T pivot;

      left = low;
      right = high;
      pivot = a[low];

      while( left < right ) {
        while(a[right] > pivot)
          right--;
        while((left < right) && (a[left] <= pivot))
          left++;

        if(left < right) {
          swap(a[left], a[right]);
        }
      }

      a[low] = a[right];
      a[right] = pivot;

      return right;
    }

    template <typename T, size_t S>
    void qsort(std::array<T,S> &a, size_t low, size_t high){
      size_t pivotPos = -1;

      if(low < high) {
        pivotPos = partition<T>(a, low, high);
        qsort<T>(a, low, pivotPos-1);
        qsort<T>(a, pivotPos+1, high);
      }
    }

    template <typename T, size_t S>
    void sort(std::array<T,S> &a) {
      size_t low = 0;
      size_t high = sizeof(a)/sizeof(a[0])-1;
      qsort<T,S>(a, low, high);
    }
  }
}

#endif // QUICKSORT_H
