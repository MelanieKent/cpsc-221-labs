/**
 * @file main.cpp
 * This file contains code for output testing of the
 *  heap class.
 * @author Daniel Hoodin, modified by Jack Toole for colored output
 * @date March 2009
 */

#include <algorithm>
#include <iostream>
#include <random>
#include <fstream>
#include <ctype.h>
#include <time.h>
#include <utility>
#include "heap.h"
#include "coloredout.h"
#include "random.h"

using namespace std;
using namespace util;

#define COUNT_FULL 15
#define COUNT_ALMOST_FULL 14

int verifyHeapProperty(heap<int> heap, int idx);

void printHeader(const string& headline)
{
    cout << string(64, colored_out::BORDER_CHAR) << endl;
    colored_out::output_bold(headline);
    cout << endl << string(64, colored_out::BORDER_CHAR) << endl;
}

void printAfter(int value, std::string operation = "remove")
{
    cout << endl;
    colored_out::output_bold("After " + operation + "(");
    colored_out::output_bold(value);
    colored_out::output_bold(")");
    cout << endl;
}

vector<int> setUpVector(int seed, int count)
{
    Random rand_gen(seed);
    vector<int> result;
    result.reserve(seed);
    for (int i = 0; i < count; i++)
        result.push_back(i);
    random_shuffle(result.begin(), result.end(), rand_gen);
    return result;
}


int main(int argc, char** argv)
{
    // Color the output
    bool is_colored
        = (argc > 1 && tolower(argv[1][0]) == 'c') && isatty(STDOUT_FILENO);
    colored_out coloroutput;
    if (is_colored) {
        coloroutput.set_expected_file("soln_heapfun_1.out");
        int status = coloroutput.start();
        if (status < 0)
            return 0;
    }

    // test push
    vector<int> to_insert = setUpVector(67, COUNT_FULL);
    heap<int> myHeap;

    if (myHeap.root() == 0) coloroutput.set_expected_file("soln_heapfun_0.out");

    int smallestSoFar = to_insert[0];

    for (size_t i = 0; i < to_insert.size(); ++i) {
        if(to_insert[i] < smallestSoFar){
            smallestSoFar = to_insert[i];
        }
        myHeap.push(to_insert[i]);
        printAfter(to_insert[i], "push");
        cout << myHeap;
    }

    // test pop REQUIRES INIT
    to_insert = setUpVector(67, COUNT_FULL);
    myHeap = heap<int>(to_insert);
    cout << "Original Heap:" << endl;
    cout << myHeap;

    bool passed = true;
    for (int i = 0; i < (int)to_insert.size(); i++)
    {
        int min = myHeap.pop();
        if (COUNT_FULL < 64 || i != min)
        {
            printAfter(min, "pop");
            cout << myHeap;
        }
    }

    // test init full
    Random rand_gen(92);
    vector<int> myArray;
    myArray.reserve(COUNT_FULL);

    for (int i = 0; i < COUNT_FULL; i++)
        myArray.push_back(i);
    random_shuffle(myArray.begin(), myArray.end(), rand_gen);

    cout << colored_out::BORDER_CHAR
         << " Original array: " << colored_out::BORDER_CHAR << endl;
    cout << "[";
    for (size_t i = 0; i < myArray.size(); ++i)
        cout << " " << myArray[i];
    cout << " ]" << endl
         << endl;

    cout << colored_out::BORDER_CHAR
         << " After buildheap: " << colored_out::BORDER_CHAR << endl;

    myHeap = heap<int>(myArray);
    cout << myHeap;

    // test init almost full
    rand_gen = Random(92);
    myArray.clear();
    myArray.reserve(COUNT_ALMOST_FULL);

    for (int i = 0; i < COUNT_ALMOST_FULL; i++)
        myArray.push_back(i);
    random_shuffle(myArray.begin(), myArray.end(), rand_gen);

    cout << colored_out::BORDER_CHAR
         << " Original array: " << colored_out::BORDER_CHAR << endl;
    cout << "[";
    for (size_t i = 0; i < myArray.size(); ++i)
        cout << " " << myArray[i];
    cout << " ]" << endl
         << endl;

    cout << colored_out::BORDER_CHAR
         << " After buildheap: " << colored_out::BORDER_CHAR << endl;

    myHeap = heap<int>(myArray);
    cout << myHeap;


}