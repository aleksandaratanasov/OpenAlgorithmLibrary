#ifndef MERGESORT_H
#define MERGESORT_H

#include <cstdlib>
#include <array>
#include <cassert>
#include "swap.h"
#define CUTOFF 7 // used to cut off the insertion sort, which is great for small arrays only

using std::array;

namespace sorting {
  namespace mergesort {

    namespace natural {
      template <typename T, size_t S>
      void sort(array<T,S>& a) {
      }

      template <typename T, size_t S>
      void merge() {
      }
    }

    // Optimized top-down mergesort
    //  - use insertion sort for the small subarrays
    //  - TODO: test if array that is to be sorted isn't already sorted
    //  - eliminate the copy of the auxiliary array
    namespace topdown {
      /*template <typename T, size_t S>
      bool isSorted(array<T,S>& a, size_t lo, size_t hi) {
        for (size_t i = lo + 1; i <= hi; ++i)
          if (a[i] < a[i-1])
            return false;
        return true;
      }

      template <typename T, size_t S>
      bool isSorted(array<T,S>& a) {
        return isSorted(a, 0, S-1);
      }*/

      template <typename T, size_t S>
      void insertionSort(array<T,S>& a, size_t lo, size_t hi) {
        size_t i = lo, j;
        for (; i <= hi; ++i)
          for (j = i; j > lo && a[j] < a[j-1]; --j)
            swap(a, j, j-1);
      }

      template <typename T, size_t S>
      void merge(array<T,S>& src, array<T,S>& dst, size_t lo, size_t mid, size_t hi) {
        // precondition: src[lo .. mid] and src[mid+1 .. hi] are sorted subarrays
//        assert (isSorted(src, lo, mid));
//        assert (isSorted(src, mid+1, hi));

        size_t i = lo, j = mid+1, k = lo;
        for (; k <= hi; ++k) {
            if (i > mid)
              dst[k] = src[j++];
            else if (j > hi)
              dst[k] = src[i++];
            else if (src[j] < src[i])
              dst[k] = src[j++];   // to ensure stability
            else
              dst[k] = src[i++];
        }

        // postcondition: dst[lo .. hi] is sorted subarray
//        assert (isSorted(dst, lo, hi));
      }

      template <typename T, size_t S>
      void copyArray(array<T,S>& src, size_t startPosSrc, array<T,S>& dst, size_t startPosDst, size_t length) {
        for(size_t i = startPosSrc, j = startPosDst; i < length && j < length; ++i,++j)
          src[i] = dst[j];
      }

      template <typename T, size_t S>
      void sort(array<T,S>& src, array<T,S>& dst, size_t lo, size_t hi) {
        // if (hi <= lo) return;
        if (hi <= lo + CUTOFF) {
          insertionSort(dst, lo, hi);
          return;
        }
        size_t mid = lo + (hi - lo) / 2;
        sort(dst, src, lo, mid);
        sort(dst, src, mid+1, hi);

        // if (!less(src[mid+1], src[mid])) {
        //    for (int i = lo; i <= hi; i++) dst[i] = src[i];
        //    return;
        // }

        // using System.arraycopy() is a bit faster than the above loop
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

        // TODO: Need to allocate on heap here and not on stack! Change this
//        array<T,S> *tmp = new array<T,S>(); //NEW
        array<T,S> tmp = a; //OLD
        sort(tmp, a, 0, S-1); //OLD
//        copyArray(a,0,*tmp,0,S); //NEW
//        sort(*tmp, a, 0, S-1);  //NEW
//        delete tmp; //NEW
//        assert (isSorted(a));
      }
    }

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
        tmp = new array<T,S>();
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
