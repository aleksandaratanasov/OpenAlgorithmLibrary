#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
#include <vector>

#include "bubblesort.h"
#include "quicksort.h"
#include "mergesort.h"
#include "heapsort.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::array;
using std::vector;

int main()
{
  int min, max;
  cout << "Enter minimum integer value for the range of random numbers:";
  cin >> min;
  cout << "Enter maximum integer value for the range of random numbers:";
  cin >> max;

  array<int, 100> a;
  for(size_t i = 0; i < a.size(); ++i)
    a[i] = min + (rand() % (max - min + 1));

  cout << "\n#array_size:" << sizeof(a)/sizeof(a[0]) << endl;

  for(size_t i = 0; i < a.size(); ++i)
    cout << a[i] << endl;

  int choice;
  cout << "\nList of available sorting algorithms:\n"
       << "1 - bubble sort\n"
       << "2 - quicksort\n"
       << "3 - mergesort\n"
       << "4 - heapsort"
       << endl;
  cout << "Your choice: ";
  cin >> choice;

//  min = -10;
//  max = 10;
//  choice = 2;

  switch(choice) {
    case 1:
      sorting::bubblesort::sort(a);
      break;
    case 2:
      sorting::quicksort::sort(a);
      break;
    case 3:
      sorting::mergesort::sort(a);
      break;
    case 4:
      sorting::heapsort::sort(a);
      break;
  }

  for(size_t i = 0; i < a.size(); ++i)
    cout << a.at(i) << endl;

  return 0;
}

