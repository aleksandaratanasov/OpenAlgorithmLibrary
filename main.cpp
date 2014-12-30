#include <iostream>       // for user interaction
#include <string>
#include <array>          // the container used to store the elements that are sorted
#include <algorithm>      // for the random shuffle before calling quicksort
//#include <cstdlib>
#include <chrono>         // for measuring execution time
#include <sys/resource.h>
//#include <gtest/gtest.h>  // Google Test C++ Framework

#include "bubblesort.h"
#include "insertionsort.h"
#include "quicksort.h"
#include "mergesort.h"
#include "heapsort.h"
#include "shellsort.h"
#include "randomstring.h"

/*
 * SOURCES:
 * - Rosettacode - for most of the pseudocode
 * - Wikibooks - in-place heapsort
 * - Algorithms (4th Edition) by Robert Sedgewick and Kevin Wayne - optimization, porting from Java
 * - other resources on the Internet - various literature on optimization of the algorithms
 *
 * TODO:
 * - add the optimizations proposed in the exercises in the book mentioned above
 *
 * STATUS:
 * - WORKING (tested with integer and string using 10, 100, 1000, 100000 and 1000000 elements)
 * - not implemented
 * - else - some bug or unable to proceed
 */

#define INTEGER
//#define STRING
//#define DOUBLE
//#define OUTPUT
#define DEBUG
#define CHECK_SORT
#define SIZE 100000//1000000
#define STRING_LENGTH_RANGE 32
// sorting choices
#define BUBBLE                      1   // WORKING
#define INSERTION_NORMAL            2   // WORKING
#define INSERTION_WITHGUARD         3   // not implemented
#define INSERTION_WITHGUARDIDXTRANS 4   // not implemented (guard+index transformation)
#define SHELL                       5   // WORKING
#define MERGE_TOPDOWN               6   // for >4500 integer (probably also double) elements fails (incorrectly sorted) - works for strings
#define MERGE_BOTTOMUP              7   // WORKING
#define QUICK_NORMAL                8   // WORKING (implementation by Sedgwick is for some reason not working)
#define QUICK_NORMAL_BITSHIFT       9   // WORKING
#define QUICK_3WAYPARTITION         10  // WORKING
#define QUICK_HYBRID                11  // not implemented
#define HEAP_INPLACE                12  // WORKING

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::string;
using std::array;
using std::chrono::high_resolution_clock;

/*
 * TODOs and ISSUEs:
 *  (ISSUE) Mergesort topdown is not working for large INTEGER arrays (only arrays with up to incl. 4500 elements are okay O_o); haven't checked with doubles
 *  (TODO) Replace own swap(T& a, T& b) with std::swap
 *  (TODO) Make mergesort use insertion sort from the insertionsort-namespace (the 3-argument method!)
 *  (TODO) See if copyArray has a standard implementation part of the C/C++ standards
 */

int main(int argc, char *argv[]) {
  int min, max;
#ifndef DEBUG
  cout << "Enter minimum integer value for the range of random numbers:";
  cin >> min;
  cout << "Enter maximum integer value for the range of random numbers:";
  cin >> max;
#else
  min = -100000;
  max = 100000;
#endif

#ifdef INTEGER
  array<int, SIZE> *a;
  a = new array<int, SIZE>();
#endif
#ifdef STRING
  array<string, SIZE> *a;
  a = new array<string, SIZE>();
#endif
#ifdef DOUBLE
  array<double, SIZE> *a;
  a = new array<double, SIZE>();
  cout << a->size() << endl;
#endif

  size_t i;
  for(i = 0; i < a->size(); ++i){
#ifdef INTEGER
    (*a)[i] = min + (rand() % (max - min + 1));
#endif
#ifdef STRING
    (*a)[i] = rand(STRING_LENGTH_RANGE);
#endif
#ifdef DOUBLE
    (*a)[i] = min + (rand() % (max - min +1));
#endif
#ifdef OUTPUT
    cout << "a[" << i << "]" << a->at(i) << endl;
#endif
  }
  cout << "\n#array_size:" << a->size() << endl;
//  cout << "********Unsorted********" << endl;
//  for(size_t i = 0; i < a.size(); ++i)
//    cout << *a[i] << endl;

  int choice;

#ifndef DEBUG
  cout << "\nList of available sorting algorithms:\n"
       << "1 - bubble\n"
       << "2 - insertion (normal)\n"
       << "3 - insertion (with guard)\n"
       << "4 - insertion (with guard and index transformation)\n"
       << "5 - shell\n"
       << "6 - merge (top-down)\n"
       << "7 - merge (bottom-up)\n"
       << "8 - quick (normal)\n"
       << "9 - quick (normal with bitshift)\n"
       << "10 - quick (3-way-partition)\n"
       << "11   quick (hybrid: 3-way-partition with insertion sort and left/right weighing)\n"
       << "12 - heap (in-place)\n\n"
       << "WARNING: Especially with algorithms such as bubblesort sorting large arrays is strongly discouraged!"
       << "Note: quicksort "
       << endl;
  cout << "Your choice: ";
  cin >> choice;
  if(choice < 0 && choice > HEAP_INPLACE) {
    cout << "Selected option does not exist." << endl;
    exit(EXIT_FAILURE);
  }
#else
  choice = MERGE_TOPDOWN;
#endif

  cout << "Sorting using ";
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  switch(choice) {
    case BUBBLE:
      cout << "bubblesort" << endl;
#ifdef INTEGER
      sorting::bubblesort::sort<int, SIZE>(*a); // code complete
#endif
#ifdef STRING
      sorting::bubblesort::sort<string,SIZE>(*a);
#endif
#ifdef DOUBLE
      sorting::bubblesort::sort<double, SIZE>(*a);
#endif
      break;
    case QUICK_NORMAL:
      cout << "quicksort (normal)" << endl;
      // Shuffle the content of the array randomly before running quicksort
      std::random_shuffle(std::begin(*a), std::end(*a));
      t1 = high_resolution_clock::now();
#ifdef INTEGER
      sorting::quicksort::normal::sort<int, SIZE>(*a);  // segmentation fault (e.g. with 10000 but not with 1000)
#endif
#ifdef STRING
      sorting::quicksort::normal::sort<string, SIZE>(*a);
#endif
#ifdef DOUBLE
      sorting::quicksort::normal::sort<double, SIZE>(*a);
#endif
      break;
    case QUICK_NORMAL_BITSHIFT:
      cout << "quicksort (normal with bitshift)" << endl;
      // Shuffle the content of the array randomly before running quicksort
      std::random_shuffle(std::begin(*a), std::end(*a));
      t1 = high_resolution_clock::now();
#ifdef INTEGER
      sorting::quicksort::normalwithshift::sort<int, SIZE>(*a);  // segmentation fault (e.g. with 10000 but not with 1000)
#endif
#ifdef STRING
      sorting::quicksort::normalwithshift::sort<string, SIZE>(*a);
#endif
#ifdef DOUBLE
      sorting::quicksort::normalwithshift::sort<double, SIZE>(*a);
#endif
      break;
    case QUICK_3WAYPARTITION:
      cout << "quicksort (3-way-partition)" << endl;
      // Shuffle the content of the array randomly before running quicksort
      std::random_shuffle(std::begin(*a), std::end(*a));
      t1 = high_resolution_clock::now();
#ifdef INTEGER
      sorting::quicksort::threewaypartwithshift::sort<int, SIZE>(*a);  // segmentation fault (e.g. with 10000 but not with 1000)
#endif
#ifdef STRING
      sorting::quicksort::threewaypartwithshift::sort<string, SIZE>(*a);
#endif
#ifdef DOUBLE
      sorting::quicksort::threewaypartwithshift::sort<double, SIZE>(*a);
#endif
      break;
    case QUICK_HYBRID:
      cout << "quicksort (hybrid)" << endl;
      // Shuffle the content of the array randomly before running quicksort
      std::random_shuffle(std::begin(*a), std::end(*a));
      t1 = high_resolution_clock::now();
#ifdef INTEGER
      sorting::quicksort::hybrid::sort<int, SIZE>(*a);  // segmentation fault (e.g. with 10000 but not with 1000)
#endif
#ifdef STRING
      sorting::quicksort::hybrid::sort<string, SIZE>(*a);
#endif
#ifdef DOUBLE
      sorting::quicksort::hybrid::sort<double, SIZE>(*a);
#endif
      break;
    case MERGE_BOTTOMUP:
      cout << "mergesort bottom up" << endl;
#ifdef INTEGER
      sorting::mergesort::bottomup::sort<int, SIZE>(*a);
#endif
#ifdef STRING
      sorting::mergesort::bottomup::sort<string, SIZE>(*a); // WORKS
#endif
#ifdef DOUBLE
      sorting::mergesort::bottomup::sort<double, SIZE>(*a);   // WORKS
#endif
      break;
    case MERGE_TOPDOWN:
      cout << "mergesort top down" << endl;
#ifdef INTEGER
      sorting::mergesort::topdown::sort<int, SIZE>(*a); // WORKS
#endif
#ifdef STRING
      sorting::mergesort::topdown::sort<string, SIZE>(*a);  // WORKS
#endif
#ifdef DOUBLE
      sorting::mergesort::topdown::sort<double, SIZE>(*a);
#endif
      break;
    case HEAP_INPLACE:
      cout << "heapsort" << endl;
#ifdef INTEGER
      sorting::heapsort::sort<int, SIZE>(*a);
#endif
#ifdef STRING
      sorting::heapsort::sort<string, SIZE>(*a);
#endif
#ifdef DOUBLE
      sorting::heapsort::sort<double, SIZE>(*a);
#endif
      break;
    case INSERTION_NORMAL:
      cout << "insertionsort" << endl;
#ifdef INTEGER
      sorting::insertionsort::normal::sort<int, SIZE>(*a);
#endif
#ifdef STRING
      sorting::insertionsort::normal::sort<string, SIZE>(*a);
#endif
#ifdef DOUBLE
      sorting::insertionsort::normal::sort<double, SIZE>(*a);
#endif
      break;
    case SHELL: // WORKS but see note in header file
      cout << "shellsort" << endl;
#ifdef INTEGER
        sorting::shellsort::sort<int,SIZE>(*a);
#endif
#ifdef STRING
      sorting::shellsort::sort<string, SIZE>(*a);
#endif
#ifdef DOUBLE
      sorting::shellsort::sort<double, SIZE>(*a);
#endif
      break;
  }
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  bool sorted = true;
#ifdef CHECK_SORT
  for(i = 0; i < a->size()-1; ++i)
    if(a->at(i) > a->at(++i)) { //ascending order only!
      cout << "Bad element at index " << i << endl;
      sorted = false;
    }
  if(sorted) cout << "Array sorted correctly!" << endl;
  else cout << "Array not sorted correctly!" << endl;
#endif
#ifdef OUTPUT
  cout << "********Sorted********" << endl;
  for(i = 0; i < a->size(); ++i) {
    cout << a->at(i) << endl;
  }
#endif

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
  cout << "Sorting completed in " << (double)duration << "ms" << endl;

  delete a;

  return 0;
}
