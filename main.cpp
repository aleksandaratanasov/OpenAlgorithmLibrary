#include <iostream>       // for user interaction
#include <string>
#include <array>          // the container used to store the elements that are sorted
#include <algorithm>      // for the random shuffle before calling quicksort
//#include <cstdlib>
#include <chrono>         // for measuring execution time
#include <sys/resource.h>
#include <gtest/gtest.h>  // Google Test C++ Framework
#include "bubblesort.h"
#include "insertionsort.h"
#include "quicksort.h"
#include "mergesort.h"
#include "heapsort.h"
#include "shellsort.h"
#include "randomstring.h"

#define INTEGER
//#define STRING
//#define DOUBLE
#define OUTPUT
#define DEBUG
#define SIZE 100//1000000
#define STRING_LENGTH_RANGE 100
// sorting choices
#define BUBBLE                      1
#define INSERTION_WITHGUARD         2 // currently only with guard
#define SHELL                       3
#define MERGE_TOPDOWN               4
#define MERGE_BOTTOMUP              5
#define QUICK_NORMAL                6
#define QUICK_NORMAL_BITSHIFT       7
#define QUICK_3WAYPARTITION         8
#define QUICK_HYBRID                9
#define HEAP                        10

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::string;
using std::array;
using std::chrono::high_resolution_clock;
//using std::vector;

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

  for(size_t i = 0; i < a->size(); ++i){
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
       << "2 - insertion\n"
       << "3 - shell\n"
       << "4 - merge (top down)\n"
       << "5 - merge (bottom up)\n"
       << "6 - quick (normal)\n"
       << "7 - quick (normal with shift)\n"
       << "8 - quick (3-way-partition)\n"
       << "9 - quick (hybrid)\n"
       << "10 - heap"
       << endl;
  cout << "Your choice: ";
  cin >> choice;
  if(choice < 0 && choice > HEAP) {
    cout << "Selected option does not exist." << endl;
    exit(EXIT_FAILURE);
  }
#else
  choice = QUICK_NORMAL;
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
    case HEAP:
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
    case INSERTION_WITHGUARD:
      cout << "insertionsort" << endl;
#ifdef INTEGER
      sorting::insertionsort::withguard::sort<int, SIZE>(*a); // code complete
#endif
#ifdef STRING
      sorting::insertionsort::withguard::sort<string, SIZE>(*a);
#endif
#ifdef DOUBLE
      sorting::insertionsort::withguard::sort<double, SIZE>(*a);
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

#ifdef OUTPUT
  cout << "********Sorted********" << endl;
  for(size_t i = 0; i < a->size(); ++i) {
    cout << a->at(i) << endl;
  }
#endif

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
  cout << "Sorting completed in " << (double)duration << "ms" << endl;

  delete a;

  return 0;
}
