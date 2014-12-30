#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <cstdlib>
#include <cstdio>
#include <array>
//#include <algorithm> // if std::swap is used
#include "swap.h"

#define CUTOFF 7 // used to cut off the insertion sort, which is great for small arrays only

using std::array;

namespace sorting {
  namespace quicksort {
    namespace hybrid {
      //Following implementation uses treeway partitioning, bit shifting, insertion sort (p.296) for small partitions and weighing if left or right branch are smaller/larger
      template <typename T, size_t S>
      void sort(std::array<T,S>& a, long int l, long int r) {
        long int i = l-1, j = r, p = l-1, q = r;

        if (r <= l + CUTOFF) {
          insertionsort::withguard::sortRange(a,l,r); // Segmentation fault here
          return;
        }
        T pivot = a[r];
        while(true)
        {
          while (a[++i] < pivot) ;
          while (pivot < a[--j])
            if (j == l) break;
          if (i >= j) break;
          swap(a[i], a[j]);
          if (a[i] == pivot) {
            p++;
            swap(a[p], a[i]);
          }
          if (pivot == a[j]) {
            q--;
            swap(a[j], a[q]);
          }
        }
        swap(a[i], a[r]); j = i-1; i = i+1;
        long int k;
        for (k = l; k < p; ++k, --j)
          swap(a[k], a[j]);
        for (k = r-1; k > q; --k, ++i)
          swap(a[i], a[k]);
        sort(a, l, j);
        sort(a, i, r);

      }

      template <typename T, size_t S>
      void sort(std::array<T,S> &a) {
        sort(a, 0, S-1);
      }
    }

    namespace threewaypartwithshift {
      template <typename T, size_t S>
      void sort(std::array<T,S>& a, long int l, long int r) {
        long int i = l-1, j = r, p = l-1, q = r;

        if (r <= l) return; // WARNING! This has to be placed before the pivot is assigned! Otherwise r becomes -1, which leads to segmentation fault
        T pivot = a[r];
        while(true)
        {
          while (a[++i] < pivot) ;
          while (pivot < a[--j])
            if (j == l) break;
          if (i >= j) break;
          swap(a[i], a[j]);
          if (a[i] == pivot) {
            p++;
            swap(a[p], a[i]);
          }
          if (pivot == a[j]) {
            q--;
            swap(a[j], a[q]);
          }
        }
        swap(a[i], a[r]); j = i-1; i = i+1;
        long int k;
        for (k = l; k < p; ++k, --j)
          swap(a[k], a[j]);
        for (k = r-1; k > q; --k, ++i)
          swap(a[i], a[k]);
        sort(a, l, j);
        sort(a, i, r);

      }

      template <typename T, size_t S>
      void sort(std::array<T,S> &a) {
        sort(a, 0, S-1);
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
      /*template <typename T, size_t S>
      size_t partition(std::array<T,S>& a, size_t l, size_t r) {
        size_t i = l, j = r+1;
//        T pivot = a[(l+(r-l))/2];
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
      }*/

      //Using size_t is rediculious in case when we have to compare numeric values!!! It results in undefined behaviour (using size_t below leads to segmentation fault)
      template <typename T, size_t S>
      void sort(std::array<T,S>& a, long int l, long int r) {
        long int i = l-1, j = r;
        if (r <= l) return;
        T pivot = a[r]; //Using (l+r)/2 results in not entirely correct sorting! => version using shift is therefore impossible
        while(true)
        {
          while (a[++i] < pivot) ;
          while (pivot < a[--j])
            if (j == l) break;
          if (i >= j) break;
          swap(a[i], a[j]);
        }
        swap(a[i], a[r]);
        sort(a, l, i-1);
        sort(a, i+1, r);
      }

      template <typename T, size_t S>
      void sort(std::array<T,S> &a) {
        sort(a, 0, S-1);
      }
    }
  }
}

#endif // QUICKSORT_H
