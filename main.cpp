#include <iostream>       // for console output
#include <string>
#include <array>          // the container used to store the elements that are sorted
#include <algorithm>      // for the random shuffle before calling quicksort
#include <random>         // use this for generation of random numbers instead of CSTDLIB
#include <chrono>         // for measuring execution time

// Library headers
#include "bubblesort.h"
#include "insertionsort.h"
#include "quicksort.h"
#include "mergesort.h"
#include "heapsort.h"
#include "shellsort.h"

//10000, 20000, 40000, 80000, 160000, 320000, 640000,...
//#define SIZE 10
//#define SIZE 100
//#define SIZE 1000
//#define SIZE 10000
//#define SIZE 20000
//#define SIZE 40000
//#define SIZE 80000
//#define SIZE 160000
//#define SIZE 320000
//#define SIZE 640000
#define SIZE 1280000
//#define SIZE 2560000
//#define SIZE 5120000
//#define SIZE 10240000
//#define SIZE 20480000

#define MU "\u03BC"

using std::cout;
using std::cin;
using std::array;
using std::endl;
using std::string;
using std::chrono::high_resolution_clock;

// Following two methods can be converted to templates in order to be able to measure times not only for doubles but for integers and strings too

/// Measures the time for a given algorithm for a single case we have to cover (see description of getFullTime(...))
/// @param sortFunc - pointer to the sorting algorithm that we want to measure the time for
/// @param a - the array that will be sorted
/// @param elementOrder - (just for the visual output) in which order the elements are ordered originally (ascending, descending, randomized)
/// @param sortFuncName - (just for the visual output) name of the sorting algorithm
/// @param workWithCopy - if set to TRUE a copy of a (see parameter description above) will be created and the sorting along with the time measurement will be done using the copy
void getTime(void (*sortFunc)(array<double,SIZE>&), array<double,SIZE>& a, string sortFuncName, string elementOrder, bool workWithCopy=true) {
  cout << sortFuncName << " | " << elementOrder << " : ";
  high_resolution_clock::time_point begin, end;

  // If enabled make a copy and work with it; useful if a single array has to be used with multiple sorting algorithms for testing purposes, which is our case ;)
  if(workWithCopy) {
    array<double,SIZE> *aCpy = new array<double,SIZE>();
    std::copy_n(a.begin(), SIZE, (*aCpy).begin());
    begin = high_resolution_clock::now();
    sortFunc(*aCpy);
    end = high_resolution_clock::now();
    delete aCpy;
  }
  // Else work with the original array
  else {
    begin = high_resolution_clock::now();
    sortFunc(a);
    end = high_resolution_clock::now();
  }

  // Print durations in milli-, micro- and nanoseconds (for small arrays micro- and nanoseconds are useful, for large arrays - microseconds)
  double durationMil = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
  double durationMic = (double)std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
  double durationNan = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
  cout << "[" << durationMil << "ms | " << durationMic <<  MU << "s" << " | " << durationNan << "ns]" << endl;
}

/// Measures the time for a given algorithm for all three cases we have to cover - ascending (ergo sorted), descending and randomized
/// @param sortFunc - pointer to the sorting algorithm that we want to measure the time for
/// @param asc - array with all elements in ascending order
/// @param des - array with all elements in descending order
/// @param ran - array with all elements in random order
/// @param sortFuncName - (just for the visual output) name of the sorting algorithm
void getFullTime(void (*sortFunc)(array<double,SIZE>&), array<double,SIZE>& asc, array<double,SIZE>& des, array<double,SIZE>& ran, string sortFuncName) {
  cout << "Time measurement for \"" << sortFuncName << "\":" << endl;
  // Call each test case
  getTime(sortFunc, asc, sortFuncName, "asc");  // ascending
  getTime(sortFunc, des, sortFuncName, "des");  // descending
  getTime(sortFunc, ran, sortFuncName, "ran");  // randomized
  cout << "**********************************************************************" << endl;
}

int main(int argc, char *argv[]) {

  // Prepare the test data used for the time measurements
  size_t i = 0;
  array<double,SIZE> *asc = new array<double,SIZE>(), *des = new array<double, SIZE>(), *ran = new array<double, SIZE>();

  // The original array contains elements in ascending order thus it's already sorted, which is the best case scenario
  double startVal = -(SIZE/2);
  for(; i < SIZE; ++i, startVal += 1.123456789) (*asc)[i] = startVal;
  std::copy_n((*asc).begin(), SIZE, (*des).begin()); std::reverse((*des).begin(), (*des).end());

  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(-123456.78901234,123456.78901234);
  for(i = 0; i < SIZE; ++i) (*ran)[i] = (double)distribution(generator);

  cout << "Following time measurements are done on an array with " << SIZE << " elements" << endl;

// We can do it with more but it gets insanely slow for large arrays
#if SIZE <= 40000
  // INSERTION SORT
  getFullTime(&(sorting::insertionsort::normal::sort), *asc, *des, *ran, "Insertion sort (normal)");
  getFullTime(&(sorting::insertionsort::withguard::sort), *asc, *des, *ran, "Insertion sort (guard)");
  // still some issues with index transformation
  getFullTime(&(sorting::insertionsort::withguardidxtransform::sort), *asc, *des, *ran, "Insertion sort (guard + idx.trans)");
#endif

  // MERGE SORT
  getFullTime(&(sorting::mergesort::bottomup::sort), *asc, *des, *ran, "Merge sort (bottom-up)");
  getFullTime(&(sorting::mergesort::natural::sort), *asc, *des, *ran, "Merge sort (natural)");

  // QUICK SORT
  getFullTime(&(sorting::quicksort::normal::sort), *asc, *des, *ran, "Quick sort (normal)");
  getFullTime(&(sorting::quicksort::normalwithshift::sort), *asc, *des, *ran, "Quick sort (normal + bitshift)");
  getFullTime(&(sorting::quicksort::threewaypartwithshift::sort), *asc, *des, *ran, "Quick sort (3-way-partition + bitshift)");
  getFullTime(&(sorting::quicksort::hybrid::sort), *asc, *des, *ran, "Quick sort (hybrid: 3-way-partition + bitshift + insertion sort)");
  getFullTime(&(sorting::quicksort::hybridFull::sort), *asc, *des, *ran, "Quick sort (hybrid: 3-way-partition + bitshift + insertion sort + merge sort)");

  // HEAP SORT
  getFullTime(&(sorting::heapsort::sort), *asc, *des, *ran, "Heap sort");

  // SHELL SORT
  getFullTime(&(sorting::shellsort::sort), *asc, *des, *ran, "Shell sort");

//  cout << "TEST TEST TEST TEST TEST TEST" << endl;
//  for(i = 0; i < SIZE; ++i) cout << (*des)[i] << endl;
//  sorting::quicksort::hybridFull::sort(*des);
//  cout << "RESULT RESULT RESULT RESULT" << endl;
//  for(i = 0; i < SIZE; ++i) cout << (*des)[i] << endl;

  delete asc;
  delete des;
  delete ran;

  return 0;
}
