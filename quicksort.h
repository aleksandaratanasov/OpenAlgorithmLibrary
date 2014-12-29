#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <cstdlib>
#include <cstdio>
#include <array>
//#include <algorithm> // if std::swap is used
#include "swap.h"

using std::array;

namespace sorting {
  namespace quicksort {
    namespace hybrid {
      //Following implementation uses treeway partitioning, bit shifting, insertion sort for small partitions and weighing if left or right branch are smaller/larger
      template <typename T, size_t S>
      void sort(std::array<T,S> &a) {
      }
    }

    namespace threewaypartwithshift {
      template <typename T, size_t S>
      void sort(std::array<T,S> &a) {
      }
    }

    namespace normalwithshift {
      template <typename T, size_t S>
      void sort(std::array<T,S>& a, size_t l, size_t r) {
        size_t i = l;
        size_t j = r;
        T pivot = a[(l+(r-l)) >> 1];  // the only difference is that we use bit shifting here instead of /2

        if(r <= l) return;

        for(;;) {
          while(a[++i] < pivot);

          while(a[--j] > pivot)
            if(j == i) break;

          if(i >= j) break;

          swap(a[i], a[j]);
        }

        swap(a[i], a[r]);
        sort(a, l, i-1);
        sort(a, i+1, r);
      }

      template <typename T, size_t S>
      void sort(std::array<T,S> &a) {
//        std::random_shuffle(std::begin(a), std::end(a));
        sort(a, 0, a.size());
      }
    }

    namespace normal {
//    template <typename T, size_t S>
//    size_t partition (std::array<T,S> &a, size_t lo, size_t hi) {
//      size_t i = lo, j = hi+1;
//      //T *v = new T(*a[lo]);
//      T pivot = a[(lo+hi)/2];

//      while(true) {
//        while(*a[++i] < *pivot);
////          if(i == hi) break;
//        while(*pivot < *a[--j])
////          if(j == lo) break;
//          if(j == i) break;
//        if(i >= j) break;
//        swap(a[i], a[j]);
//      }

//      swap(a[lo], a[j]);
//      return j;
//    }

//    template <typename T, size_t S>
//    void qsort(std::array<T,S> &a, size_t lo, size_t hi){

//      if(hi <= lo) return;
//      size_t j = partition(a, lo, hi);
//      qsort(a, lo, j-1);
//      qsort(a, j+1, hi);
//    }

      /*
      template <typename T>
      void swap(T& t1, T& t2) {
        //printf("Swapping [%d] and [%d]\n", *t1, *t2);
        T temp = t1;
        t1 = t2;
        t2 = temp;
      }

      template <typename T, size_t S>
      void sort(std::array<T,S>& a, size_t l, size_t r) {
        size_t i = l;
        size_t j = r;
        T pivot = a[(l+(r-l))/2];

        if(r <= l) return;

        for(;;) {
          while(a[++i] < pivot);

          while(a[--j] > pivot)
            if(j == i) break;

          if(i >= j) break;

          swap(a[i], a[j]);
        }

        swap(a[i], a[r]);
        sort(a, l, i-1);
        sort(a, i+1, r);
      }
      */
      template <typename T, size_t S>
      size_t partition(std::array<T,S>& a, size_t l, size_t r) {
        size_t i = l, j = r+1;
        T pivot = a[l];
        while(true) {
          while(a[++i] < pivot)
            if(i == r) break;
          while(pivot < a[--j])
            if(j == l) break;
          if(i >= j) break;
          swap(a, i, j);
        }
        swap(a, l, j);
        return j;
      }

      template <typename T, size_t S>
      void sort(std::array<T,S>& a, size_t l, size_t r) {
        if(r <= l) return;

        size_t j = partition(a, l, r);
        sort(a, l, j-1);
        sort(a, j+1, r);
      }

      template <typename T, size_t S>
      void sort(std::array<T,S> &a) {
        sort(a, 0, S-1);
      }
    }
  }
}

#endif // QUICKSORT_H
