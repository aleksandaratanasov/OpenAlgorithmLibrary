#ifndef TESTGENERATORS_H
#define TESTGENERATORS_H

#include <string>
#include <cstdlib>
#include <array>
#include <vector>
#include <time.h>
#include <typeinfo>
#include "randomstring.h"

// Test types
// Note ascending order is the natural order, which is the goal of the sorting algorithms here, which means that such an array is already sorted
//#define RANDOM      //Numeric/string elements of the array are generated randomly ([0]...,-100,0,27,-2,...[SIZE-1])
//#define DESCENDING  //Numeric/string elements of the array are generated sequentielly in a descending order ([0]...,3,2,1,0,-1,-2,-3,...[SIZE-1])
//#define ASCENDING   //Numeric/string elements of the array are generated sequentielly in a ascending order ([0]...,-3,-2,-1,0,1,2,3,...[SIZE-1])


namespace testing {
  enum ttype {
    RANDOM = 0,
    DESCENDING,
    ASCENDING
  };

//  enum dtype {
//    INTEGER = 0,
//    DOUBLE,
//    STRING
//  };

  /// Generates numeric and string test
  /// @param target - array which will be filled with test data; if array is already full, old content will be replaced with new one
  /// @param testType - determines the way data is generated (RANDOM|DESCENDING|ASCENDING)
  /// @param dataType - determines the type of the generated data (INTEGER|DOUBLE|STRING)
  /// @param randRangeMin - the lower bound of the randomly generated data (applies only for numeric types); used as starting point for ASCENDING test
  /// @param randRangeMax - the upper bound of the randomly generated data (applies only for numeric types); used as starting point for DESCENDING test
  /// @param stringMaxLen - determines the max length of a randomly generated string

//  void generateIntTest(void *target, ttype testType = RANDOM, long int randRangeMin = -1000, long int randRangeMax = 1000);















  /*template<typename T, size_t S>
  void generateTest(std::array<T,S>& target, ttype testType = RANDOM, dtype dataType = INTEGER, long int randRangeMin = -1000, long int randRangeMax = 1000, size_t stringMaxLen = 32) {

    // Check if type of the array is supported by the test generator
    std::string tT = typeid(T).name();
    if(tT != "Ss" || tT != "d" || tT != "i") return;

    // Check if there is a type mismatch between the type of that array and the given dataType
    if((tT == "i" && dataType != INTEGER) ||
       (tT == "d" && dataType != DOUBLE) ||
       (tT == "Ss" && dataType != STRING))
      return;

    // Check if target isn't already full in which case delete it's content and fill it with new one
  //  if(target != nullptr)
  //    delete target;

    size_t i = 0;

    // Make sure that following rand() calls generate values from a set based on the given seed
    unsigned int seed = time(NULL);
    srand(seed);

    switch(dataType) {
      case INTEGER:
        switch(testType) {
          case RANDOM:
            for(; i < S; ++i)
              target[i] = randRangeMin + (rand_r(&seed) % (randRangeMax - randRangeMin + 1));
            break;
          case ASCENDING:
            for(; i < S; ++i)
              target[i] = randRangeMin + i;
            break;
          case DESCENDING:
            for(; i < S; ++i)
              target[i] = randRangeMax - i;
            break;
        }
        break;
      case DOUBLE:
        switch(testType) {
          case RANDOM:
            for(; i < S; ++i)
              target[i] = (double)(randRangeMin + (rand_r(&seed) % (randRangeMax - randRangeMin + 1)));
            break;
          case ASCENDING:
            for(; i < S; ++i)
              target[i] = (double)(randRangeMin + i);
            break;
          case DESCENDING:
            for(; i < S; ++i)
              target[i] = (double)(randRangeMax - i);
            break;
        }
        break;
      case STRING:
        switch(testType) {
          case RANDOM:
            for(; i < S; ++i)
              target[i] = rand(stringMaxLen, seed);
            break;
          case ASCENDING:
            for(; i < S; ++i)
              target[i] = "";
            break;
          case DESCENDING:
            for(; i < S; ++i)
              target[i] = "";
            break;
        }
        break;
  //    case STRING:
  //      for(size_t i = 0; i < S; ++i)
  //        target[i] = rand(stringMaxLen);
  //      break;
  //    case DOUBLE:
  //      for(size_t i = 0; i < S; ++i)
  //        target[i] = rangeMin + (rand() % (rangeMax - rangeMin + 1));
  //      break;
    }
  }*/
}

#endif // TESTGENERATORS_H
