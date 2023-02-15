/**
 * @file testheap.cpp
 * Heap Testing Code
 *
 * @author Jack Toole
 * @date Fall 2011
 *
 * @author Chase Geigle
 * @date Fall 2012
 *
 */
#define CATCH_CONFIG_MAIN

#include <iostream>
#include <fstream>
#include <ctype.h>
#include <time.h>
#include <utility>
#include "coloredout.h"
#include "heap.h"
#include "random.h"
#include "catch.hpp"

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


TEST_CASE("test push","[weight=0]]"){
    vector<int> to_insert = setUpVector(67, COUNT_FULL);
    heap<int> myHeap;

    int smallestSoFar = to_insert[0];

    for (size_t i = 0; i < to_insert.size(); ++i) {
        if(to_insert[i] < smallestSoFar){
            smallestSoFar = to_insert[i];
        }
        myHeap.push(to_insert[i]);
        printAfter(to_insert[i], "push");
        cout << myHeap;
        REQUIRE(!myHeap.empty());
        REQUIRE(myHeap.peek() == smallestSoFar);
    }
}

TEST_CASE("test pop REQUIRES INIT", "[weight=0]"){
    vector<int> to_insert = setUpVector(67, COUNT_FULL);
    heap<int> myHeap(to_insert);
    cout << "Original Heap:" << endl;
    cout << myHeap;

    bool passed = true;
    for (int i = 0; i < (int)to_insert.size(); i++) {
        REQUIRE(!myHeap.empty());
        int min = myHeap.pop();
        if (COUNT_FULL < 64 || i != min) {
            printAfter(min, "pop");
            cout << myHeap;
        }
        REQUIRE(i == min);
    }
}

TEST_CASE("test init full", "[weight=0]"){
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
    cout << " ]" << endl << endl;

    cout << colored_out::BORDER_CHAR
         << " After buildheap: " << colored_out::BORDER_CHAR << endl;

    heap<int> myHeap(myArray);
    cout << myHeap;

    REQUIRE(!myHeap.empty());
    REQUIRE(myHeap.peek() == 0);

    REQUIRE(COUNT_FULL == verifyHeapProperty(myHeap, myHeap.root()));
}


TEST_CASE("test init almost full", "[weight=0]"){
    Random rand_gen(92);
    vector<int> myArray;
    myArray.reserve(COUNT_ALMOST_FULL);

    for (int i = 0; i < COUNT_ALMOST_FULL; i++)
        myArray.push_back(i);
    random_shuffle(myArray.begin(), myArray.end(), rand_gen);

    cout << colored_out::BORDER_CHAR
         << " Original array: " << colored_out::BORDER_CHAR << endl;
    cout << "[";
    for (size_t i = 0; i < myArray.size(); ++i)
        cout << " " << myArray[i];
    cout << " ]" << endl << endl;

    cout << colored_out::BORDER_CHAR
         << " After buildheap: " << colored_out::BORDER_CHAR << endl;

    heap<int> myHeap(myArray);
    cout << myHeap;

    REQUIRE(!myHeap.empty());
    REQUIRE(myHeap.peek() == 0);

    REQUIRE(COUNT_ALMOST_FULL == verifyHeapProperty(myHeap, myHeap.root()));
}

int verifyHeapProperty(heap<int> heap, int startIdx){
    if(!heap.hasAChild(startIdx)){
        return 1;
    }
    int root = heap._elems[startIdx];
    int leftIdx = heap.leftChild(startIdx);

    if(root > heap._elems[leftIdx]){ // failed heap property on left
    	return 0; 
    }
    int rightIdx = heap.rightChild(startIdx);

    if(rightIdx < (int) heap._elems.size()){ // does index have a right child
    	if(heap._elems[rightIdx] > root){ // does heap property suceed on right
    		return 1 + verifyHeapProperty(heap, leftIdx) + verifyHeapProperty(heap, rightIdx);
    	} else {
    		return 0;
    	}
    } else {
    	return 1 + verifyHeapProperty(heap, leftIdx);
    }
}


/**
 *  This test is NEVER RUN, but ONLY COMPILED.
 *   Its compilation checks that you aren't using any values, i.e.
 *   array[i], as an index into the array (since a string can't be
 *   used as an index into an array. If you do, this code will
 *   prevent the heap code from compiling. Neat, huh?
 **/
void testCompileOnly()
{
    vector<string> testHeapStringsCompiles;
    heap<string> myHeap(testHeapStringsCompiles);
    myHeap.pop();
}

