#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <cstdlib>
#include <array>

using std::array;

namespace oal {
  namespace sorting {
    namespace heapsort {
      /*template <typename T, size_t S>
      void swap2(std::array<T,S>& a, size_t i, size_t j) {
        T swap = a[i-1];
        a[i-1] = a[j-1];
        a[j-1] = swap;
      }

      // p.316
      template <typename T, size_t S>
      void sink(std::array<T,S>& a, size_t k, size_t len) {
        size_t i = 0;
        while (2*k <= len) {
          i = 2*k;
          if (i < len && (a[i] < a[i+1])) i++;
          if (!(a[k] < a[i])) break;
          swap2(a, k, i);
          k = i;
        }
      }

      // p.324
      template <typename T, size_t S>
      void sort(std::array<T,S>& a) {
        size_t len = S, k = len/2;
        for (;k >= 1; --k)
          sink(a, k, len);
        while (len > 1) {
          swap2(a, 1, len--);
          sink(a, 1, len);
        }
      }*/

      template <typename T, size_t S>
      void sort(std::array<T,S>& a) {
        size_t N = S;
        T t; /* the temporary value */
        size_t n = N, parent = N/2, index, child; /* heap indexes */
        while (true) {
          if (parent > 0)
            /* first stage - Sorting the heap */
            t = a[--parent];  /* save old value to t */
          else {
            /* second stage - Extracting elements in-place */
            n--;                /* make the heap smaller */
            if (n == 0) return; /* When the heap is empty, we are done */
            t = a[n];         /* save lost heap entry to temporary */
            a[n] = a[0];    /* save root entry beyond heap */
          }
          /* insert operation - pushing t down the heap to replace the parent */
          index = parent; /* start at the parent index */
          child = index * 2 + 1; /* get its left child index */
          while (child < n) {
            /* choose the largest child */
            if (child + 1 < n  &&  a[child + 1] > a[child]) {
              child++; /* right child exists and is bigger */
            }
            /* is the largest child larger than the entry? */
            if (a[child] > t) {
              a[index] = a[child]; /* overwrite entry with child */
              index = child; /* move index to the child */
              child = index * 2 + 1; /* get the left child and go around again */
            } else break; /* t's place is found */
          }
          /* store the temporary value at its new location */
          a[index] = t;
        }
      }
    }
  }
}

#endif // HEAPSORT_H
