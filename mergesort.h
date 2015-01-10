#ifndef MERGESORT_H
#define MERGESORT_H

#include <array>
#include "swap.h"
#include "insertionsort.h"
#define CUTOFF 7 // used to cut off the insertion sort, which is great for small arrays only

using std::array;

namespace sorting {
  namespace mergesort {

    // STATUS: working (natural = non-optimized top-down?)
    namespace natural {
      template <typename T, size_t S>
      void copyArray(array<T,S>& src, size_t startPosSrc, array<T,S>& dst, size_t startPosDst, size_t length) {
        for(size_t i = startPosSrc, j = startPosDst; i < length && j < length; ++i,++j)
          dst[j] = src[i];
      }

      template <typename T, size_t S>
      void merge(array<T,S>& a, array<T,S>& aux, size_t lo, size_t mid, size_t hi) {
        size_t k = lo;
        for (; k <= hi; ++k) aux[k] = a[k];

        // merge back to a[]
        size_t i = lo, j = mid+1;
        for (k = lo; k <= hi; ++k) {
          if(i > mid) a[k] = aux[j++];   // this copying is unnecessary
          else if (j > hi) a[k] = aux[i++];
          else if(aux[j] < aux[i]) a[k] = aux[j++];
          else a[k] = aux[i++];
        }
      }

      template <typename T, size_t S>
      void sort(array<T,S>& a, array<T,S>& aux, size_t lo, size_t hi) {
        if (hi <= lo) return;
        size_t mid = lo + (hi - lo) / 2;
        sort(a, aux, lo, mid);
        sort(a, aux, mid + 1, hi);
        merge(a, aux, lo, mid, hi);
      }

      template <typename T, size_t S>
      void sort(array<T,S>& a) {
        if(S < 2)
          return;

        array<T,S> *tmp = new array<T,S>(); //NEW
//        array<T,S> tmp = a; //OLD
//        sort(tmp, a, 0, S-1); //OLD
        copyArray(a,0,*tmp,0,S); //NEW
        sort(*tmp, a, 0, S-1);  //NEW
        delete tmp; //NEW
      }
    }

    // STATUS: not working (only for up to 4500 elements)
    // Optimized top-down mergesort
    //  - use insertion sort for the small subarrays
    //  - TODO: test if array that is to be sorted isn't already sorted
    //  - eliminate the copy of the auxiliary array
    namespace topdown {
//      template <typename T, size_t S>
//      void insertionSort(array<T,S>& a, size_t lo, size_t hi) {
//        size_t i = lo, j;

//        for (; i <= hi; ++i)
//          for (j = i; j > lo && a[j] < a[j-1]; --j)
//            swap(a, j, j-1);
//      }

      template <typename T, size_t S>
      void merge(array<T,S>& src, array<T,S>& dst, size_t lo, size_t mid, size_t hi) {
        size_t i = lo, j = mid+1, k = lo;

        for (; k <= hi; ++k) {
            if (i > mid) dst[k] = src[j++];
            else if (j > hi) dst[k] = src[i++];
            else if (src[j] < src[i]) dst[k] = src[j++];   // to ensure stability
            else dst[k] = src[i++];
        }
      }

      template <typename T, size_t S>
      void copyArray(array<T,S>& src, size_t startPosSrc, array<T,S>& dst, size_t startPosDst, size_t length) {
        for(size_t i = startPosSrc, j = startPosDst; i < length && j < length; ++i,++j)
          dst[j] = src[i];
      }

      template <typename T, size_t S>
      void sort(array<T,S>& src, array<T,S>& dst, size_t lo, size_t hi) {
        // if (hi <= lo) return;
        if (hi <= lo + CUTOFF) {
//          insertionSort(dst, lo, hi);
          insertionsort::sortRange(dst, lo, hi);
          return;
        }
        size_t mid = lo + ((hi - lo) >> 1);
        sort(dst, src, lo, mid);
        sort(dst, src, mid+1, hi);

        if (!(src[mid+1] < src[mid])) {
          copyArray(src, lo, dst, lo, hi - lo + 1);
          return;
        }

        merge(src, dst, lo, mid, hi);
      }


      template <typename T, size_t S>
      void sort(array<T,S>& a) {
        if(S < 2)
          return;

        array<T,S> *tmp = new array<T,S>(); //NEW
//        array<T,S> tmp = a; //OLD
//        sort(tmp, a, 0, S-1); //OLD
        copyArray(a,0,*tmp,0,S); //NEW
        sort(*tmp, a, 0, S-1);  //NEW
        delete tmp; //NEW
      }
    }

    // STATUS: working
    namespace bottomup {
      template <typename T, size_t S>
      void merge(array<T,S>& a, array<T,S>& tmp, size_t lo, size_t mi, size_t hi) {
        size_t i = lo, j = mi+1, k;

        for (k = lo; k <= hi; ++k)
          tmp[k] = a[k];

        for (k = lo; k <= hi; ++k) {
            if(i > mi)
              a[k] = tmp[j++];
            else if(j > hi)
              a[k] = tmp[i++];
            else if (tmp[j] < tmp[i])
              a[k] = tmp[j++];
            else
              a[k] = tmp[i++];
        }
      }

      template <typename T, size_t S>
      void sort(array<T,S>& a) {
        if(S < 2)
          return;

        array<T,S> *ap,*tmp;
        tmp = new array<T,S>(); // auxiliary array tmp
        ap = &a;

        size_t i,j,lo,mi,hi;

        for (i = 1; i < S; i = i+i) {
          for (j = 0; j < S-i; j += i+i) {
            lo = j;
            mi = j+i-1;
            hi = ((j+i+i-1) < S-1) ? j+i+i-1 : S-1;

            merge(*ap, *tmp, lo, mi, hi);
          }
        }

        delete tmp;
      }
    }
  }
}

#endif // MERGESORT_H
