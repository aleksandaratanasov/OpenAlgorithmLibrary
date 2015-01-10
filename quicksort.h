#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <cstdlib>
#include <cstdio>
#include <array>
//#include <algorithm> // if std::swap is used
#include "swap.h"
#include "insertionsort.h"

#define CUTOFF 7 // used to cut off the insertion sort, which is great for small arrays only

namespace sorting {
  namespace quicksort {
    // STATUS: not working
    namespace hybrid {
      //Following implementation uses 3-way partitioning, bit shifting, insertion sort (p.296) for small partitions and weighing if left or right branches are smaller/larger
      /*template <typename T, size_t S>
      void sort(std::array<T,S>& a, size_t l, size_t r) {
        size_t i = l, j = r;
        T pivot = a[(l+r)>>1];
        if(r <= l + CUTOFF) {
          insertionsort::sortRange(a, l, r);
          return;
        }

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
      }*/

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
        sort(a, l, j);
        sort(a, i, r);

      }

      template <typename T, size_t S>
      void sort(std::array<T,S> &a) {
        sort(a, 0, S-1);
      }
    }

    // STATUS: working
    namespace threewaypartwithshift {
      template <typename T, size_t S>
      void sort(std::array<T,S>& a, long int l, long int r) {
        long int i = l-1, j = r, p = l-1, q = r;

        if (r <= l) return; // WARNING! This has to be placed before the pivot is assigned! Otherwise r becomes -1, which leads to segmentation fault

        swap(a[(l+r)/2], a[r]);
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
  }
}

#endif // QUICKSORT_H
