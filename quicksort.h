#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <cstdlib>
#include <cstdio>
#include <array>
//#include <algorithm> // if std::swap is used
#include "swap.h"
#include "insertionsort.h"
#include "mergesort.h"

#define CUTOFF 7 // used to cut off the insertion sort, which is great for small arrays only
#define FACTOR 6

namespace sorting {
  namespace quicksort {
    // STATUS: working
    namespace threewaypartwithshift {

      template <typename T, size_t S>
      size_t sortReturnIdx(std::array<T, S>& a, size_t l, size_t r) {
        size_t i = l - 1, j = r;
        size_t p = l - 1, q = r;
        size_t pi = (l + r) >> 1;
        T v = a[pi];
        std::swap(a[pi], a[r]);

        while (true) {
          while (a[++i] < v);
          while (v < a[--j])
            if (j == l) break;

          if (i >= j) break;
          std::swap(a[i], a[j]);

          if (a[i] == v) {
            p++;
            std::swap(a[p], a[i]);
          }
          if (v == a[j]) {
            q--;
            std::swap(a[j], a[q]);
          }
        }
        std::swap(a[i], a[r]);
        j = i - 1;
        i++;

        for (size_t k = l; k<p && p != size_t(-1); k++, j--) std::swap(a[k], a[j]);
        for (size_t k = r - 1; k>q; k--, i++) std::swap(a[i], a[k]);
        return j + 1;
      }

      template <typename T, size_t S>
      void sort(std::array<T,S>& a, long int l, long int r) {
        long int i = l-1, j = r, p = l-1, q = r;

        if (r <= l) return; // WARNING! This has to be placed before the pivot is assigned! Otherwise r becomes -1, which leads to segmentation fault

        swap(a[(l+r)>>1], a[r]);
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

    // STATUS: working
    namespace normalwithshift {
      template <typename T, size_t S>
      void sort(std::array<T,S>& a, size_t l, size_t r) {
        size_t i = l, j = r;

        swap(a[(l+r)>>1], a[r]);
        T pivot = a[r];

        while (i <= j) {
          while (a[i] < pivot) i++;
          while (a[j] > pivot) j--;
          if (i <= j) {
            swap(a[i],a[j]);
            i++;
            j--;
          }
        };
        if (l < j) sort(a, l, j);
        if (i < r) sort(a, i, r);
      }

      template <typename T, size_t S>
      void sort(std::array<T,S> &a) {
        sort(a, 0, S-1);
      }
    }

    // STATUS: working
    namespace normal {
      //Using size_t is rediculious in case when we have to compare numeric values!!! It results in undefined behaviour (using size_t below leads to segmentation fault)
      template <typename T, size_t S>
      void sort(std::array<T,S>& a, size_t l, size_t r) {
        size_t i = l, j = r;

        swap(a[(l+r)/2], a[r]);
        T pivot = a[r];

        while (i <= j) {
          while (a[i] < pivot) i++;
          while (a[j] > pivot) j--;
          if (i <= j) {
            swap(a[i],a[j]);
            i++;
            j--;
          }
        };
        if (l < j) sort(a, l, j);
        if (i < r) sort(a, i, r);
      }

      template <typename T, size_t S>
      void sort(std::array<T,S> &a) {
        sort(a, 0, S-1);
      }
    }

    // STATUS: not working
    namespace hybrid {
      //Following implementation uses 3-way partitioning, bit shifting, insertion sort (p.296) for small partitions and weighing if left or right branches are smaller/larger
  //      template <typename T, size_t S>
  //      void sort(std::array<T,S>& a, size_t l, size_t r) {
  //        size_t i = l, j = r;
  //        T pivot = a[(l+r)>>1];
  //        if(r <= l + CUTOFF) {
  //          insertionsort::sortRange(a, l, r);
  //          return;
  //        }

  //        while (i <= j) {
  //          while (a[i] < pivot) i++;
  //          while (a[j] > pivot) j--;
  //          if (i <= j) {
  //            swap(a[i],a[j]);
  //            i++;
  //            j--;
  //          }
  //        };
  //        if (l < j) sort(a, l, j);
  //        if (i < r) sort(a, i, r);
  //      }
  /////////////////////////////////////////////////////////// WORKING 3WAYPART AND INSERT BUT WITHOUT THE MERGE STEP
        template <typename T, size_t S>
        void sort(std::array<T,S>& a, long int l, long int r) {
          long int i = l-1, j = r, p = l-1, q = r;

          if (r <= l + CUTOFF) {
            insertionsort::sortRange(a, l, r);
            return;
          }

          swap(a[(l+r)>>1], a[r]);
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

          // Balancing trees (which one is greater)
          //          if((r-i) > 0 && (j-l) > 0 && ((r-i) << FACTOR < (j-l) || (j-l) << 6 < (r-i))) {
          //            quicksort(a,l,(l+r)>>1,b);
          //            quicksort(a,l,(l+r)>>1 + 1,r,b);
          //            mergesort::bottomup::merge(a, b, l,((l+r)>>1),r);
          //          }
          //          else {
          ////            sort(a, l, j);
          ////            sort(a, i, r);
          //            sort(a, b, l, j);
          //            sort(a, b, i, j);
          //          }


          // Remove lines below when the commented out code above is ready
          sort(a, l, j);
          sort(a, i, r);
        }

        template <typename T, size_t S>
        void sort(std::array<T,S> &a) {
          sort(a, 0, S-1);
        }
/////////////////////////////////////NOT WORKING, WITH MERGE STEP///////////////////////////
//      template <typename T, size_t N>
//      void quicksort_hybrid(std::array<T, N>& a, std::array<T, N>& b, size_t l, size_t r) {
//        if (r <= l || r == size_t(-1)) return;

//        if (r - l < CUTOFF) {
//          insertionsort::sortRange(a, l, r);
//        }
//        else {
//          size_t pivot_index = quicksort::threewaypartwithshift::sortReturnIdx(a, l, r);
//          size_t center = (l + r) >> 1;
//          if(pivot_index - l >= (FACTOR * (r-pivot_index))|| (r-pivot_index)>= (FACTOR * pivot_index - l)){
//            if (center > l)
//            quicksort_hybrid(a, b, l, center);
//            if (r > center + 1)
//            quicksort_hybrid(a, b, center + 1, r);
//            mergesort::natural::merge_natural(a, b, l, r, true);
//          }
//          else {
//            if (pivot_index - 1 > l) quicksort_hybrid(a, b, l, pivot_index - 1);
//            if (r > pivot_index + 1) quicksort_hybrid(a, b, pivot_index + 1, r);
//          }
//        }
//      }

//      template <typename T, size_t S>
//      void sort(std::array<T,S> &a) {
//        if(S < 2)
//          return;

//        array<T,S> *tmp = new array<T,S>();
//        std::copy_n(a.begin(), S, (*tmp).begin());
//        quicksort_hybrid(*tmp, a, 0, S-1);
//        delete tmp;
//      }
    }
  }
}

#endif // QUICKSORT_H
