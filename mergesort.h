#ifndef MERGESORT_H
#define MERGESORT_H

#include <array>
#include "swap.h"
#include "insertionsort.h"
#define CUTOFF 32 // used to cut off the insertion sort, which is great for small arrays only

using std::array;

namespace sorting {
  namespace mergesort {

    template<typename T, size_t SIZE>
    void merge(std::array<T, SIZE> &a, std::array<T, SIZE> &b, long int lo, long int m, long int hi)
    {
      long int i = lo;
      long int j = hi;
      long int k = lo;

      // vordere Hälfte in Array b kopieren
      while (i <= m) b[k++] = a[i++];

      // hintere Hälfte in umgekehrter Reihenfolge in Array b kopieren
      while (j > m) b[k++] = a[j--];

      i = lo;
      j = hi;
      k = lo;

      // jeweils das nächstgrößte Element zurückkopieren, bis i und j sich überkreuzen
      while (i <= j)
      {
        if (b[i] <= b[j])
          a[k++] = b[i++];
        else
          a[k++] = b[j--];
      }
    }

    // STATUS: not working - for some reason a shifting of one element occurs
    //http://www.iti.fh-flensburg.de/lang/algorithmen/sortieren/merge/natmerge.htm
    //http://www.algorithmist.com/index.php/Merge_sort#Natural_mergesort PSEUDOCODE
//    namespace natural {
//      template <typename T, size_t S>
//      void copyArray(array<T,S>& src, size_t startPosSrc, array<T,S>& dst, size_t startPosDst, size_t length) {
//        for(size_t i = startPosSrc, j = startPosDst; i < length && j < length; ++i,++j)
//          dst[j] = src[i];
//      }

//      template <typename T, size_t S>
//      void merge(array<T,S>& a, array<T,S>& aux, size_t lo, size_t hi, bool asc) {
//        size_t k = asc ? lo : hi;
//        size_t c = asc ? 1 : -1;
//        size_t i = lo, j = hi;

//        // jeweils das nächstgrößte Element zurückkopieren,
//        // bis i und j sich überkreuzen
//        while (i <= j ){
//            if (a[i] <= a[j]) aux[k] = a[i++];
//            else aux[k] = a[j--];
//            k += c;
//        }
//      }

//      template <typename T, size_t S>
//      bool mergeruns(array<T,S>& a, array<T,S>& aux) {
//        size_t i = 0, k = 0;
//        T pivot;
//        bool asc = true;

//        while (i < S) {
//          k = i;
//          do pivot=a[i++]; while (i < S && pivot <= a[i]);  // ascending part
//          while (i < S && pivot >= a[i]) pivot = a[i++];  //descending part
//          merge (a, aux, k, i-1, asc);
//          asc = !asc;
//        }

//        return k == 0;
//      }

//      template <typename T, size_t S>
//      void naturalmergesort(array<T,S>& a, array<T,S>& aux) {
//        while(!mergeruns(a,aux) & !mergeruns(aux,a));
//      }

//      template <typename T, size_t S>
//      void sort(array<T,S>& a) {
//        if(S < 2)
//          return;

//        array<T,S> *tmp = new array<T,S>(); //NEW
////        array<T,S> tmp = a; //OLD
////        sort(tmp, a, 0, S-1); //OLD
////        copyArray(a,0,*tmp,0,S); //replaced by std::copy_n
//        std::copy_n(a.begin(), S, (*tmp).begin()); //NEW

//        naturalmergesort(a, *tmp);  //NEW
//        delete tmp; //NEW
//      }
//    }

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

//    namespace natural {
//      template <typename T, size_t SIZE>
//      void sort(std::array<T, SIZE>& a) {
//        std::array<T, SIZE> *b = new std::array<T, SIZE>();
//        size_t h, i, j, k, l, d;
//        bool sd_i, sd_j, sorted;

//        do {
//          d = 1;
//          i = k = 0;
//          j = l = SIZE;
//          sd_i = sd_j = false;
//          sorted=true;

//          while (i <= j) {
//            if ((!sd_i && sd_j && a[i] <= a[j]) || (!sd_i && sd_j)) {
//              (*b)[k] = a[i ++];
//              k = k + d;
//              if (i <= j && a[i - 1] > a[i]) sd_i = true;
//            }
//            else if ((!sd_i && !sd_j && a[i] > a[j]) || (sd_i && !sd_j)) {
//              (*b)[k] = a[j --];
//              k = k+d;
//              if (i <= j && a[j] < a[j+1]) sd_j = true;
//            }
//            else {
//                h = k; k = l; l = h;
//                d = -d;
//                sd_i = sd_j = sorted = false;
//            }
//          }

//          for (size_t m = 0; m <= SIZE; ++m) a[m] = (*b)[m];
//        } while (!sorted);
//        delete b;
//      }
//    }

//    namespace natural {
//      template<typename T, size_t SIZE>
//      void merge_natural(std::array<T, SIZE>& a, std::array<T, SIZE>& b, size_t lo, size_t hi, bool asc) {
//        for (size_t k = lo; k <= hi; ++k) b[k] = a[k];
//        size_t k = asc ? lo : hi;
//        size_t c = asc ? 1 : -1;
//        size_t i = lo, j = hi;
//        while (i <= j) {
//          if (b[i] <= b[j]) a[k] = b[i++];
//          else a[k] = b[j--];
//        }
//        k += c;
//      }

//      template<typename T, size_t SIZE>
//      bool mergeruns(std::array<T, SIZE>& a, std::array<T, SIZE>& b)
//      {
//        size_t i=0, k=0;
//        T x;
//        bool asc = true;
//        while (i < SIZE) {
//          k = i;
//          do {
//            x = a[i++];
//          } while (i < SIZE && x <= a[i]);
//          while( i < SIZE && x >= a[i])
//          x = a[i++];
//          merge_natural(a, b, k, i-1, asc);
//          asc = !asc;
//        }
//        return k == 0;
//      }

//      template <typename T, size_t SIZE>
//      void sort(std::array<T, SIZE>& a)
//      {
//        std::array<T, SIZE> *b = new std::array<T, SIZE>();
//        while (!mergeruns(a, *b));
//        delete b;
//      }
//    }

    // STATUS: not working (only for up to 4500 NUMERIC elements)
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
//        copyArray(a,0,*tmp,0,S); //replaced by std::copy_n
        std::copy_n(a.begin(), S, (*tmp).begin());
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

#endif // MERGESORT_H
