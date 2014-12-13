#include <iostream>       // for user interaction
#include <string>
#include <array>
#include <cstdlib>
//#include <vector>
#include <sys/resource.h>
#include <gtest/gtest.h>  // Google Test C++ Framework

#include "bubblesort.h"
#include "insertionsort.h"
#include "quicksort.h"
#include "mergesort.h"
#include "heapsort.h"

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::string;
using std::array;
//using std::vector;

//#define OUTPUT
#define DEBUG
#define SIZE 1000000

/*
string rand(size_t length) {
  char str[length];
  str[length-1] = '\0';
  size_t i = 0;
  int r;

  for(i = 0; i < length-1; ++i) { //length-1 for the '\0' at the end
    for(;;) {
      r = rand() % 57 + 65; //interval between 65 ('A') and 65+57=122 ('z')
      if((r >= 65 && r <= 90) || (r >= 97 && r <= 122)) { // exclude '[' to '`'
        str[i] = (char)r;
        break;
      }
    }
  }

  return string(str);
}*/

string rand(size_t range) {
  int length = rand() % range + 1; // this includes even empty strings!
  char str[length];
  str[length-1] = '\0';
  size_t i = 0;
  int r;

  for(i = 0; i < length-1; ++i) { //length-1 for the '\0' at the end
    for(;;) {
      r = rand() % 57 + 65; //interval between 65 ('A') and 65+57=122 ('z')
      if((r >= 65 && r <= 90) || (r >= 97 && r <= 122)) { // exclude '[' to '`'
        str[i] = (char)r;
        break;
      }
    }
  }

  return string(str);
}

int main(int argc, char *argv[]) {
  char q[1];
  q[0] = '\0';
  string str(q);
  if(str.empty())
    cout << "EMPTY" << endl;


  for(int i = 0; i < 100; ++i) {
    cout << rand(100) << endl;
  }
  return 0;

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

  array<int, SIZE> *a;
  a = new array<int, SIZE>();
  cout << a->size() << endl;

  for(size_t i = 0; i < a->size(); ++i){
    (*a)[i] = min + (rand() % (max - min + 1));
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
       << "1 - bubble sort\n"
       << "2 - quicksort\n"
       << "3 - mergesort\n"
       << "4 - heapsort\n"
       << "5 - insertionsort"
       << endl;
  cout << "Your choice: ";
  cin >> choice;
#else
  choice = 3;
#endif

  /*array<string,5> *b;
  b = new array<string,5>();
  b->at(0) = "lucy";
  b->at(1) = "zack";
  b->at(2) = "clare";
  b->at(3) = "bob";
  b->at(4) = "alice";

  for(int i = 0; i < 5; ++i)
    cout << (*b)[i] << endl;*/

  cout << "Sorting using ";
  switch(choice) {
    case 1:
      cout << "bubblesort" << endl;
      sorting::bubblesort::sort<int, SIZE>(*a); // code complete
      //sorting::bubblesort::sort<string,5>(*b);
      break;
    case 2:
      cout << "quicksort" << endl;
      sorting::quicksort::sort<int, SIZE>(*a);  // segmentation fault (e.g. with 10000 but not with 1000)
      break;
    case 3:
      cout << "mergesort" << endl;
      // bottom-up
      //sorting::mergesort::bottomup::sort<int, SIZE>(*a);
      sorting::mergesort::topdown::sort<int, SIZE>(*a);
      break;
    case 4:
      cout << "heapsort" << endl;
      sorting::heapsort::sort<int, SIZE>(*a);
      break;
    case 5:
      cout << "insertionsort" << endl;
      sorting::insertionsort::withguard::sort<int, SIZE>(*a); // code complete
      break;
  }

#ifdef OUTPUT
  cout << "********Sorted********" << endl;
  for(size_t i = 0; i < a->size(); ++i) {
    cout << a->at(i) << endl;
  }
#endif

  /*for(int i = 0; i < 5; ++i)
    cout << (*b)[i] << endl;
  delete b;*/

  delete a;

  return 0;
}
