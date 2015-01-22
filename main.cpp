#include <iostream>       // for user interaction
#include <string>
#include <array>          // the container used to store the elements that are sorted
#include <algorithm>      // for the random shuffle before calling quicksort
#include <random>         // use this for generation of random numbers instead of CSTDLIB
#include <cstdlib>
#include <chrono>         // for measuring execution time
#include <sys/resource.h>
//#include <gtest/gtest.h>  // Google Test C++ Framework
#include <typeinfo>
#include "bubblesort.h"
#include "insertionsort.h"
#include "quicksort.h"
#include "mergesort.h"
#include "heapsort.h"
#include "shellsort.h"
#include "randomstring.h"


//10000, 20000, 40000, 80000, 160000, 320000, 640000,...
//#define SIZE 1000
//#define SIZE 10000
//#define SIZE 20000
#define SIZE 40000
//#define SIZE 80000
//#define SIZE 160000
//#define SIZE 320000
//#define SIZE 640000
//#define SIZE 1280000

using std::cout;
using std::cin;
using std::array;
using std::endl;
using std::chrono::high_resolution_clock;

int main(int argc, char *argv[])
{
        //Testarray mit aufsteigenden double werten ORIGINAL
        array<double,SIZE> *orig;//Deklarieren
        orig = new array<double,SIZE>();//Initialisieren
        double startVal = -(SIZE / 2);
        for(size_t i=0; i<SIZE; startVal += 1.1223456789, ++i){
            //dereferenzieren um auf Objekte zuzugreifen
            //mit zufälligen werten füllen
          // (*arr)[i]= MIN + (rand() % (MAX-MIN+1));
            (*orig)[i] = startVal;
        }//for

        //Kopien der Arrays zum Arbeiten erstellen
        //in den jeweiligen Sortierverfahren initialisieren
        //normal copy ascending array
        array<double, SIZE> *arrCopyAsc;//Deklarieren

        //ascending reverse copy -> descending array
        array<double, SIZE> *arrCopyR;//Deklarieren
        //Also Kopie von Kopie machen !!!
        arrCopyR = new array<double, SIZE>();//Initialisieren
        std::copy_n((*orig).begin(), SIZE, (*arrCopyR).begin());
        //reverse
        std::reverse((*arrCopyR).begin(), (*arrCopyR).end());
        //Array umgedreht und muss dauernd kopiert werden
        array<double, SIZE> *arrCopyRCopy;//Deklarieren


        //Array kopieren und shuffle random anwenden
        array<double, SIZE> *arrCopyS;//Deklarieren
        //Array kopieren und shuffle random anwenden orig->shuffle
        //Dieses geshuffelte Array bei der Zeitmessung immer vorher kopieren !!!
        //Also Kopie von Kopie machen !!!
        arrCopyS = new array<double, SIZE>();//Initialisieren
        std::copy_n((*orig).begin(), SIZE, (*arrCopyS).begin());
        std::random_shuffle((*arrCopyS).begin(), (*arrCopyS).end());

        //Kopie vom Shuffle deklarieren
        array<double, SIZE> *arrCopyShuffleCopy;//Deklarieren



        //Deklariere Zeitmesspunkte
        high_resolution_clock::time_point t1;
        high_resolution_clock::time_point t2;

        //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        //Array ausgeben
        //for (size_t i = 0; i < SIZE; i++)
        //{
        //		cout << (*arrCopyR)[i] << endl;
        //}


        //-------------------------------------------------------------------------------------------
        //Zeitmessung
        //-------------------------------------------------------------------------------------------

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Insertionsort Normal Zeitmessung																						  ////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        cout << "//------------------------------------------------------------------//" << endl;
        cout << "//---------------INSERTIONSORT normal-------------------------------//" << endl;
        cout << "//------------------------------------------------------------------//" << endl;
        //-------------------------------------------------------------------------------------------//Status: ok
        //Insertionsort Normal
        //-------------------------------------------------------------------------------------------
        //Aufsteigend
        //-------------------------------------------------------------------------------------------
        //array ascending Original ist schon aufsteigend
        arrCopyAsc = new array<double, SIZE>();//Initialisieren
        std::copy_n((*orig).begin(), SIZE, (*arrCopyAsc).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::insertionsort::normal::sort<double, SIZE>(*arrCopyAsc);
        //Zeitpunkt1
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyAsc;
        cout << "Insertionsort normal - aufsteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Insertionsort Normal
        //-------------------------------------------------------------------------------------------
        //Absteigend
        //-------------------------------------------------------------------------------------------
        //Umgedrehtes Arrayerstellen orig->reverse->array descending
        arrCopyRCopy = new array<double, SIZE>();//Deklarieren
        std::copy_n((*arrCopyR).begin(), SIZE, (*arrCopyRCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::insertionsort::normal::sort<double, SIZE>(*arrCopyRCopy);
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyRCopy;
        cout << "Insertionsort normal - absteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Insertionsort Normal
        //-------------------------------------------------------------------------------------------
        //Random Shuffle
        //-------------------------------------------------------------------------------------------
        //random shuffle array Kopie machen
        arrCopyShuffleCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyS).begin(), SIZE, (*arrCopyShuffleCopy).begin());
        //Zeitpunkt 1
        t1 = high_resolution_clock::now();
        sorting::insertionsort::normal::sort<double, SIZE>(*arrCopyShuffleCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyShuffleCopy;
        cout << "Insertionsort normal - random shuffle Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Insertionsort mit Guard Zeitmessung																								  ////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        cout << "//------------------------------------------------------------------//" << endl;
        cout << "//---------------INSERTIONSORT mit Guard----------------------------//" << endl;
        cout << "//------------------------------------------------------------------//" << endl;
        //-------------------------------------------------------------------------------------------//Status: ok
        //Insertionsort mit Guard
        //-------------------------------------------------------------------------------------------
        //Aufsteigend
        //-------------------------------------------------------------------------------------------
        //array ascending Original ist schon aufsteigend
        arrCopyAsc = new array<double, SIZE>();//Initialisieren
        std::copy_n((*orig).begin(), SIZE, (*arrCopyAsc).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::insertionsort::withguard::sort<double, SIZE>(*arrCopyAsc);
        //Zeitpunkt1
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyAsc;
        cout << "Insertionsort mit Guard - aufsteigendes Array SIZE: "<< SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Insertionsort mit Guard
        //-------------------------------------------------------------------------------------------
        //Absteigend
        //-------------------------------------------------------------------------------------------
        //Umgedrehtes Arrayerstellen orig->reverse->array descending
        arrCopyRCopy = new array<double, SIZE>();//Deklarieren
        std::copy_n((*arrCopyR).begin(), SIZE, (*arrCopyRCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::insertionsort::withguard::sort<double, SIZE>(*arrCopyRCopy);
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyRCopy;
        cout << "Insertionsort mit Guard - absteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Insertionsort mit Guard
        //-------------------------------------------------------------------------------------------
        //Random Shuffle
        //-------------------------------------------------------------------------------------------
        //random shuffle array Kopie machen
        arrCopyShuffleCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyS).begin(), SIZE, (*arrCopyShuffleCopy).begin());
        //Zeitpunkt 1
        t1 = high_resolution_clock::now();
        sorting::insertionsort::withguard::sort<double, SIZE>(*arrCopyShuffleCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyShuffleCopy;
        cout << "Insertionsort mit Guard - random shuffle Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Insertionsort Guard + Indextransformation Zeitmessung																								  ////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        cout << "//------------------------------------------------------------------//" << endl;
        cout << "//---------------INSERTIONSORT mit Guard + Indextr------------------//" << endl;
        cout << "//------------------------------------------------------------------//" << endl;
        //-------------------------------------------------------------------------------------------//Status: ok
        //Insertionsort Guard + Indextransformation
        //-------------------------------------------------------------------------------------------
        //Aufsteigend
        //-------------------------------------------------------------------------------------------
        //array ascending Original ist schon aufsteigend
        arrCopyAsc = new array<double, SIZE>();//Initialisieren
        std::copy_n((*orig).begin(), SIZE, (*arrCopyAsc).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::insertionsort::withguardidxtransform::sort<double, SIZE>(*arrCopyAsc);
        //Zeitpunkt1
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyAsc;
        cout << "Insertionsort Guard + Indextransformation - aufsteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Insertionsort Guard + Indextransformation
        //-------------------------------------------------------------------------------------------
        //Absteigend
        //-------------------------------------------------------------------------------------------
        //Umgedrehtes Arrayerstellen orig->reverse->array descending
        arrCopyRCopy = new array<double, SIZE>();//Deklarieren
        std::copy_n((*arrCopyR).begin(), SIZE, (*arrCopyRCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::insertionsort::withguardidxtransform::sort<double, SIZE>(*arrCopyRCopy);
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyRCopy;
        cout << "Insertionsort Guard + Indextransformation - absteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Insertionsort Guard + Indextransformation
        //-------------------------------------------------------------------------------------------
        //Random Shuffle
        //-------------------------------------------------------------------------------------------
        //random shuffle array Kopie machen
        arrCopyShuffleCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyS).begin(), SIZE, (*arrCopyShuffleCopy).begin());
        //Zeitpunkt 1
        t1 = high_resolution_clock::now();
        sorting::insertionsort::withguardidxtransform::sort<double, SIZE>(*arrCopyShuffleCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyShuffleCopy;
        cout << "Insertionsort Guard + Indextransformation - random shuffle Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Mergesort Bottom-Up Zeitmessung																										////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        cout << "//------------------------------------------------------------------//" << endl;
        cout << "//---------------Mergesort Bottom-Up--------------------------------//" << endl;
        cout << "//------------------------------------------------------------------//" << endl;
        //-------------------------------------------------------------------------------------------//Status: ok
        //Mergesort Bottom-Up
        //-------------------------------------------------------------------------------------------
        //Aufsteigend
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        arrCopyAsc = new array<double, SIZE>();//Initialisieren
        std::copy_n((*orig).begin(), SIZE, (*arrCopyAsc).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::mergesort::bottomup::sort<double, SIZE>(*arrCopyAsc);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyAsc;
        cout << "Mergesort Bottom-Up - aufsteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Mergesort Bottom-Up
        //-------------------------------------------------------------------------------------------
        //Absteigend
        //-------------------------------------------------------------------------------------------
        //Umgedrehtes Arrayerstellen orig->reverse->array descending
        arrCopyRCopy = new array<double, SIZE>();//Deklarieren
        std::copy_n((*arrCopyR).begin(), SIZE, (*arrCopyRCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::mergesort::bottomup::sort<double, SIZE>(*arrCopyRCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyRCopy;
        cout << "Mergesort Bottom-Up - absteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Mergesort Bottom-Up
        //-------------------------------------------------------------------------------------------
        //Random Shuffle
        //-------------------------------------------------------------------------------------------
        //random shuffle array Kopie machen
        arrCopyShuffleCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyS).begin(), SIZE, (*arrCopyShuffleCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::mergesort::bottomup::sort<double, SIZE>(*arrCopyShuffleCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyShuffleCopy;
        cout << "Mergesort Bottom-Up - random shuffle Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;




        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Mergesort Natural Zeitmessung																							////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        cout << "//------------------------------------------------------------------//" << endl;
        cout << "//---------------Mergesort Natural----------------------------------//" << endl;
        cout << "//------------------------------------------------------------------//" << endl;
        //-------------------------------------------------------------------------------------------//Status: ok
        //Mergesort Natural
        //-------------------------------------------------------------------------------------------
        //Aufsteigend
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        arrCopyAsc = new array<double, SIZE>();//Initialisieren
        std::copy_n((*orig).begin(), SIZE, (*arrCopyAsc).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::mergesort::natural::sort<double, SIZE>(*arrCopyAsc);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyAsc;
        cout << "Mergesort Natural - aufsteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Mergesort Natural
        //-------------------------------------------------------------------------------------------
        //Absteigend
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        //array<double, SIZE> *arrCopyR;//Deklarieren
        arrCopyRCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyR).begin(), SIZE, (*arrCopyRCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::mergesort::natural::sort<double, SIZE>(*arrCopyRCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyRCopy;
        cout << "Mergesort Natural - absteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;
        //-------------------------------------------------------------------------------------------//Status: ok
        //Mergesort Natural
        //-------------------------------------------------------------------------------------------
        //Random Shuffle
        //-------------------------------------------------------------------------------------------
        arrCopyShuffleCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyS).begin(), SIZE, (*arrCopyShuffleCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::mergesort::natural::sort<double, SIZE>(*arrCopyShuffleCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyShuffleCopy;
        cout << "Mergesort Natural - random shuffle Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Quicksort Normal Zeitmessung																										////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        cout << "//------------------------------------------------------------------//" << endl;
        cout << "//---------------Quicksort Normal-----------------------------------//" << endl;
        cout << "//------------------------------------------------------------------//" << endl;
        //-------------------------------------------------------------------------------------------//Status: ok
        //Quicksort Normal
        //-------------------------------------------------------------------------------------------
        //Aufsteigend
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        arrCopyAsc = new array<double, SIZE>();//Initialisieren
        std::copy_n((*orig).begin(), SIZE, (*arrCopyAsc).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::quicksort::normal::sort<double, SIZE>(*arrCopyAsc);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyAsc;
        cout << "Quicksort Normal - aufsteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Quicksort Normal
        //-------------------------------------------------------------------------------------------
        //Absteigend
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        //array<double, SIZE> *arrCopyR;//Deklarieren
        arrCopyRCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyR).begin(), SIZE, (*arrCopyRCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::quicksort::normal::sort<double, SIZE>(*arrCopyRCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyRCopy;
        cout << "Quicksort Normal - absteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Quicksort Normal
        //-------------------------------------------------------------------------------------------
        //Random Shuffle
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        arrCopyShuffleCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyS).begin(), SIZE, (*arrCopyShuffleCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::quicksort::normal::sort<double, SIZE>(*arrCopyShuffleCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyShuffleCopy;
        cout << "Quicksort Normal - random shuffle Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Quicksort mit Shift Zeitmessung																										////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        cout << "//------------------------------------------------------------------//" << endl;
        cout << "//---------------Quicksort mit Shift--------------------------------//" << endl;
        cout << "//------------------------------------------------------------------//" << endl;
        //-------------------------------------------------------------------------------------------//Status: ok
        //Quicksort mit Shift
        //-------------------------------------------------------------------------------------------
        //Aufsteigend
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        arrCopyAsc = new array<double, SIZE>();//Initialisieren
        std::copy_n((*orig).begin(), SIZE, (*arrCopyAsc).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::quicksort::normalwithshift::sort<double, SIZE>(*arrCopyAsc);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyAsc;
        cout << "Quicksort mit Shift - aufsteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Quicksort mit Shift
        //-------------------------------------------------------------------------------------------
        //Absteigend
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        //array<double, SIZE> *arrCopyR;//Deklarieren
        arrCopyRCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyR).begin(), SIZE, (*arrCopyRCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::quicksort::normalwithshift::sort<double, SIZE>(*arrCopyRCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyRCopy;
        cout << "Quicksort mit Shift - absteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Quicksort mit Shift
        //-------------------------------------------------------------------------------------------
        //Random Shuffle
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        arrCopyShuffleCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyS).begin(), SIZE, (*arrCopyShuffleCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::quicksort::normalwithshift::sort<double, SIZE>(*arrCopyShuffleCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyShuffleCopy;
        cout << "Quicksort mit Shift - random shuffle Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Quicksort 3way mit Shift Zeitmessung																										////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        cout << "//------------------------------------------------------------------//" << endl;
        cout << "//---------------Quicksort 3way mit Shift---------------------------//" << endl;
        cout << "//------------------------------------------------------------------//" << endl;
        //-------------------------------------------------------------------------------------------//Status: ok
        //Quicksort 3way mit Shift
        //-------------------------------------------------------------------------------------------
        //Aufsteigend
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        arrCopyAsc = new array<double, SIZE>();//Initialisieren
        std::copy_n((*orig).begin(), SIZE, (*arrCopyAsc).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::quicksort::threewaypartwithshift::sort<double, SIZE>(*arrCopyAsc);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyAsc;
        cout << "Quicksort 3way mit Shift - aufsteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Quicksort 3way mit Shift
        //-------------------------------------------------------------------------------------------
        //Absteigend
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        //array<double, SIZE> *arrCopyR;//Deklarieren
        arrCopyRCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyR).begin(), SIZE, (*arrCopyRCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::quicksort::threewaypartwithshift::sort<double, SIZE>(*arrCopyRCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyRCopy;
        cout << "Quicksort 3way mit Shift - absteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Quicksort 3way mit Shift
        //-------------------------------------------------------------------------------------------
        //Random Shuffle
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        arrCopyShuffleCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyS).begin(), SIZE, (*arrCopyShuffleCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::quicksort::threewaypartwithshift::sort<double, SIZE>(*arrCopyShuffleCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyShuffleCopy;
        cout << "Quicksort 3way mit Shift - random shuffle Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Quicksort Hybrid Zeitmessung																										////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        cout << "//------------------------------------------------------------------//" << endl;
        cout << "//---------------Quicksort Hybrid-----------------------------------//" << endl;
        cout << "//------------------------------------------------------------------//" << endl;
        //-------------------------------------------------------------------------------------------//Status: ok
        //Quicksort Hybrid
        //-------------------------------------------------------------------------------------------
        //Aufsteigend
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        arrCopyAsc = new array<double, SIZE>();//Initialisieren
        std::copy_n((*orig).begin(), SIZE, (*arrCopyAsc).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::quicksort::hybrid::sort<double, SIZE>(*arrCopyAsc);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyAsc;
        cout << "Quicksort Hybrid - aufsteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Quicksort Hybrid
        //-------------------------------------------------------------------------------------------
        //Absteigend
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        //array<double, SIZE> *arrCopyR;//Deklarieren
        arrCopyRCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyR).begin(), SIZE, (*arrCopyRCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::quicksort::hybrid::sort<double, SIZE>(*arrCopyRCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyRCopy;
        cout << "Quicksort Hybrid - absteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //Quicksort Hybrid
        //-------------------------------------------------------------------------------------------
        //Random Shuffle
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        arrCopyShuffleCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyS).begin(), SIZE, (*arrCopyShuffleCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        cout << "***************YOU FAIL HERE" << endl;
        sorting::quicksort::hybrid::sort<double, SIZE>(*arrCopyShuffleCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyShuffleCopy;
        cout << "Quicksort Hybrid - random shuffle Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //sorting::heapsort Zeitmessung																									////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        cout << "//------------------------------------------------------------------//" << endl;
        cout << "//---------------sorting::heapsort-------------------------------------------//" << endl;
        cout << "//------------------------------------------------------------------//" << endl;
        //-------------------------------------------------------------------------------------------//Status: ok
        //sorting::heapsort
        //-------------------------------------------------------------------------------------------
        //Aufsteigend
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        arrCopyAsc = new array<double, SIZE>();//Initialisieren
        std::copy_n((*orig).begin(), SIZE, (*arrCopyAsc).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::heapsort::sort<double, SIZE>(*arrCopyAsc);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyAsc;
        cout << "sorting::heapsort - aufsteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //sorting::heapsort
        //-------------------------------------------------------------------------------------------
        //Absteigend
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        arrCopyRCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyR).begin(), SIZE, (*arrCopyRCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::heapsort::sort<double, SIZE>(*arrCopyRCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyRCopy;
        cout << "sorting::heapsort - absteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        //-------------------------------------------------------------------------------------------//Status: ok
        //sorting::heapsort
        //-------------------------------------------------------------------------------------------
        //Random Shuffle
        //-------------------------------------------------------------------------------------------
        //ascending reverse copy -> descending array
        arrCopyShuffleCopy = new array<double, SIZE>();//Initialisieren
        std::copy_n((*arrCopyS).begin(), SIZE, (*arrCopyShuffleCopy).begin());
        //Zeitpunkt1
        t1 = high_resolution_clock::now();
        sorting::heapsort::sort<double, SIZE>(*arrCopyShuffleCopy);
        //Zeitpunkt 2 nach dem Sortieren
        t2 = high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //copy nach sort nutzlos, loeschen
        delete arrCopyShuffleCopy;
        cout << "sorting::heapsort - random shuffle Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////Shellsort Zeitmessung																										////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //cout << "//------------------------------------------------------------------//" << endl;
        //cout << "//---------------SHELLSORT------------------------------------------//" << endl;
        //cout << "//------------------------------------------------------------------//" << endl;
        ////-------------------------------------------------------------------------------------------//Status: ok
        ////Shellsort
        ////-------------------------------------------------------------------------------------------
        ////Aufsteigend
        ////-------------------------------------------------------------------------------------------
        ////ascending reverse copy -> descending array
        //arrCopyAsc = new array<double, SIZE>();//Initialisieren
        //std::copy_n((*orig).begin(), SIZE, (*arrCopyAsc).begin());
        ////Zeitpunkt1
        //t1 = high_resolution_clock::now();
        //shellsort::sort<double, SIZE>(*arrCopyAsc);
        ////Zeitpunkt 2 nach dem Sortieren
        //t2 = high_resolution_clock::now();
        //duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        ////copy nach sort nutzlos, loeschen
        //delete arrCopyAsc;
        //cout << "Shellsort - aufsteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        ////-------------------------------------------------------------------------------------------//Status: ok
        ////Shellsort
        ////-------------------------------------------------------------------------------------------
        ////Absteigend
        ////-------------------------------------------------------------------------------------------
        ////ascending reverse copy -> descending array
        ////array<double, SIZE> *arrCopyR;//Deklarieren
        //arrCopyR = new array<double, SIZE>();//Initialisieren
        //std::copy_n((*orig).begin(), SIZE, (*arrCopyR).begin());
        ////Zeitpunkt1
        //t1 = high_resolution_clock::now();
        //shellsort::sort<double, SIZE>(*arrCopyR);
        ////Zeitpunkt 2 nach dem Sortieren
        //t2 = high_resolution_clock::now();
        //duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        ////copy nach sort nutzlos, loeschen
        //delete arrCopyR;
        //cout << "Shellsort - absteigendes Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;

        ////-------------------------------------------------------------------------------------------//Status: ok
        ////Shellsort
        ////-------------------------------------------------------------------------------------------
        ////Random Shuffle
        ////-------------------------------------------------------------------------------------------
        ////ascending reverse copy -> descending array
        //arrCopyS = new array<double, SIZE>();//Initialisieren
        //std::copy_n((*orig).begin(), SIZE, (*arrCopyS).begin());
        ////Shuffle
        //std::random_shuffle((*arrCopyS).begin(), (*arrCopyS).end());
        ////Zeitpunkt1
        //t1 = high_resolution_clock::now();
        //shellsort::sort<double, SIZE>(*arrCopyS);
        ////Zeitpunkt 2 nach dem Sortieren
        //t2 = high_resolution_clock::now();
        //duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        ////copy nach sort nutzlos, loeschen
        //delete arrCopyS;
        //cout << "Shellsort - random shuffle Array SIZE: " << SIZE << "  completed in :" << (double)duration << "ms" << endl;


        //Working arrays loeschen
        //Zeitmessung stuerzt ab kein delete !!!
        delete arrCopyR;
        delete arrCopyS;

        //Original loeschen
        delete orig;
    return 0;
}

//Schreibe aufsteigene DOUBLE Werte in einem Array
//Zeitmessung (NUR MIT DOUBLE)
//Für verschiedene Anzahl von Elemente:
//Array kopieren: std::copy_n((*ARR1).begin(), SIZE, (*ARR2).begin()) (Kopie von ARR1 nach ARR2)
//Nach jeder Anwendung eines Sortieralgos ist die Kopie nutzlos, deshalb "delete ARRKOPIE;" schreiben um diese zu löschen
//Für AUFSTEIGENDE Zeitmessung - einfach Kopie von dem oben genannten Array machen, Sortieralgo laufen lassen und Zeit messen
//Für ABSTEIGENDE Zeitmessung - Kopie von dem oben genannten Array machen, std::reverse() auf dem Kopie anwenden, Sortieralgo laufen lassen und Zeit messen
//Für ZUFÄLLIGE Zeitmessung - Kopie von dem oben genannten Array machen, std::random_shuffle() auf dem Kopie anwenden, Sortieralgo laufen lassen und Zeit messen
//VORSICHT: std::random_shuffle() wird bei jedem Aufruf eine neue Verteilung von den Werten schaffen; deshalb nur EINMAL machen und diese als Originalarray betrachten bzw. entsprechend Kopien davon machen

//double startD = SIZE / 2;
//for (size_t i = 0; i < SIZE; start += 1.056327 , i++)
//{
//	array
//}
//
