#ifndef MERGESORT_H
#define MERGESORT_H

#include <array>
#include "swap.h"
#include "insertionsort.h"
#define CUTOFF 32 // used to cut off the insertion sort, which is great for small arrays only

using std::array;

namespace oal {
  namespace sorting {
    namespace mergesort {

      template<typename T, size_t SIZE>
      void merge(std::array<T, SIZE> &a, std::array<T, SIZE> &b, long int lo, long int m, long int hi)
      {
        long int i = lo;
        long int j = hi;
        long int k = lo;

        // Copy first half in array b
        while (i <= m) b[k++] = a[i++];

        // Copy second half backwards in array b
        while (j > m) b[k++] = a[j--];

        i = lo;
        j = hi;
        k = lo;

        // Copy back next biggest element until i and j cross values
        while (i <= j)
        {
          if (b[i] <= b[j])
            a[k++] = b[i++];
          else
            a[k++] = b[j--];
        }
      }

    namespace natural {
      template<typename T, size_t S>
      void merge_natural(std::array<T, S>& a, std::array<T, S>& b, size_t lo, size_t hi, bool asc) {
        size_t k, c, i, j;
        for (k = lo; k <= hi; ++k) b[k] = a[k];

        k = asc ? lo : hi;
        c = asc ? 1 : -1;
        i = lo;
        j = hi;

        while (i <= j) {
          if (b[i] <= b[j]) a[k] = b[i++];
          else a[k] = b[j--];

          k += c;
        }
      }

      template<typename T, size_t S>
      bool mergeruns(std::array<T, S>& a, std::array<T, S>& b) {
        size_t i=0, k=0;
        T x;
        bool asc = true;
        while (i<S) {
          k = i;
          do {
            x = a[i++];
          } while (i<S && x<= a[i]);
          while( i<S && x>=a[i]) x = a[i++];
          merge_natural(a, b, k, i-1, asc);
          asc = !asc;
        }

        return k == 0;
      }

      template <typename T, size_t S>
      void sort(std::array<T, S>& a) {
        std::array<T, S> *b = new std::array<T, S>();
        while (!mergeruns(a, *b));
        delete b;
      }
    }

      namespace topdown {
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

          array<T,S> *tmp = new array<T,S>();
          std::copy_n(a.begin(), S, (*tmp).begin());
          sort(*tmp, a, 0, S-1);
          delete tmp;
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
              if(i > mi) a[k] = tmp[j++];
              else if(j > hi) a[k] = tmp[i++];
              else if (tmp[j] < tmp[i]) a[k] = tmp[j++];
              else a[k] = tmp[i++];
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
}

#endif // MERGESORT_H
