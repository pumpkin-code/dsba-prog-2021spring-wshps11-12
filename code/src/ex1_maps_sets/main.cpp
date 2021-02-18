////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief      Main module for Problem 1: 
/// \author     Sergey Shershakov
/// \version    0.1.0
/// \date       16.02.2021
///             This code is for educational purposes of the course "Introduction
///             to programming" provided by the Faculty of Computer Science
///             at the Higher School of Economics.
///
///  Dealing with maps and sets.
///
////////////////////////////////////////////////////////////////////////////////

#include <utility>      // for std::swap, could use <algorithm> as well
#include <random>       // for mt19937 (pseudo-)random numbers generator
#include <ctime>        // for time() function
#include <vector>
#include <map>
#include <iostream>


using IntVector = std::vector<int>;
using IntSizetMap = std::map<int, size_t>;

// Creates a vector of n random numbers from the given range [r, q] , r <= q ?
IntVector makeVector(size_t n, int r, int q)
{
    // if r > q, it could be what is called the exception, however now we simply fix
    // the issues if so

    if (r > q)
        std::swap(r, q);        // make sure the relationship r <= q

    IntVector vec;

    // let's generate some pseudo-random values
    std::mt19937 gen(time(nullptr));            // we provide a seed (intialize the generator)
    std::uniform_int_distribution<int> distr(r, q);

    // distr(gen) gives us another pseudo-random number
    for (size_t i = 0; i < n; ++i)
    {
        int anotherRandomNumber = distr(gen);   // the parenthesis operator() is called for the
                                                // distr object and the generator is provided as
                                                // as the only one actual parameter
        vec.push_back(anotherRandomNumber);
    }

    return vec;
}

// Prints out the content of the given vector in the forward order.
void printVec(const IntVector& vec)
{
    // TODO: HW remaster the following code using the range-based for loop

    // use iterators for iterating the look in the forward direction
    // IntVector::iterator          // allows to iterate over a mutable collection, so you'll be able
                                    // to change individual elements
    // IntVector::const_iterator    // works for both const and non-const ranges (containers)
                  // ^ often, you can see using of the auto keyword here. Until we are able
                  // to deduce the real datatype for all the iterators, deferenced iterators and all,
                  // we are going to use the auto keyword

    for (IntVector::const_iterator it = vec.begin();    // we can use std::begin(vec), it's exactly the same
                                    it != vec.end();    // we can use std::end(vec) as well
                                    ++it)               // advance the iterator, moves it towards the end of the range
    {
        std::cout << *it << "\t";
                //   ^ here * is a (red-colored) dereference operator, it gives
                //     the value of the element from the range the iterator /it\ points to
    }
}


// Prints out the content of the given vector in the backward order.
void printBackVec(const IntVector& vec)
{
    for (IntVector::const_reverse_iterator it = vec.rbegin();    // we can use std::rbegin(vec), it's exactly the same
                                    it != vec.rend();    // we can use std::rend(vec) as well
                                    ++it)               // advance the iterator, moves it towards the beginning of the range
    {
        std::cout << *it << "\t";
                //   ^ here * is a (red-colored) dereference operator, it gives
                //     the value of the element from the range the iterator /it\ points to
    }
}


// Creates a map using the given vector as a sample. We put all the unique elements
// of the vector to the map (as keys) and associate these keys with the number of
// occurences of the corresponding values in the vector.
IntSizetMap createMapFromVec(const IntVector& vec)
{
    // TODO: HW: remaster the following code using the iterators-based approach

    IntSizetMap resMap;         // a newly created map

    // we use the range-based for loop
    for (int el : vec)
    {
        // we need add new keys in a map and associate them with 1 (initially only
        // one occurence), and then, for the existing keys, wi simply need to increment
        // the number of occurences

        // we need to be able to check whether another key (el) exists in the or not
        IntSizetMap::iterator it = resMap.find(el);
        if (it == resMap.end())                 // the key doesn't exist
        {
            resMap.insert ( { el, 1}  );
                      //     ^ is the first element is the key of the current element, the element from the vector
                      //         ^ is the associated value of the current element, represents the number ofoccurences
        }
        else
        {
            // (*it).second   <====> it->second   - represents the existing associated value, the number of occurences
            ++it->second;
        }
    }

    return resMap;
}

//using namespace std;


// TODO: HW: try to create a method that output the content of the given map as
// a sequence of <key, value> pairs
// Mention that IntSizetMap::const_iterator gives you a reference to the pair,
// whose first element is the key, and the second is the value
void printMap(const IntSizetMap& myMap)
{
    std::cout << "{";

    // TODO: try to use the range-based for loop, firstly
    //    for(const std::pair<int, unsigned long long> val : map)
    //    {
    //        std::cout << val.first << " == " << val.second << "\n";
    //    }

    //std::map

    // The solution proposed by Ival Kovalyonok

    // TODO: try to use the iteratos-based approach, secondly
    for(IntSizetMap::const_iterator it = myMap.begin();     // the same as std::begin(myMap)
            it != myMap.end();                              // the same as std::end(myMap)
            ++it)
    {
        // (*it) gives one a dereferenced object the iterator points to, and for
        // the map it's a pair,
        //std::cout << (*it).first << " == " << (*it).second << "\n";   // IT's ok
        std::cout << it->first << " => " << it->second << ", ";         // an alternative approach
    }

    std::cout << "}";


    // TODO: try to use the iteratos-based approach, secondly
}

// Prints keys only
void printMapKeys(const IntSizetMap& myMap)
{
    // let's call another pair "element", because it's better than simply "value",
    // since the value is just a part of the element (it's the second part)
    //for(const std::pair<int, size_t> element : myMap)             // we take another pair by copying it as a new pair, but we don't need a copy
    //for(const std::pair<int, size_t>& element : myMap)      // technically, it must be const int in the first element of the pair, because even we had non const iterator here, the key of a map must not be changed under any condition
    for(const std::pair<const int, size_t>& element : myMap)
    {
        //std::cout << element.first << " == " << element.second << "\n";
        std::cout << element.first << ", ";
    }
}


void printEachTthMapElement(const IntSizetMap& myMap, size_t t)
{
    // TODO: HW: re-master the code below using the range-based for approach intead of iterators
    // hint: consider using the skipping counter as well and when you need to skip elements,
    // use the continue keyword.

    if (t == 0)
        t = 1;              // it's not a really good solution, it's better to throw an exception instead

    std::cout << "{";

    size_t numOfSkippedElements = t - 1;                    // we know that we have skip t - 1 elements

    // try to use the iteratos-based approach, secondly
    for (IntSizetMap::const_iterator it = myMap.begin();     // the same as std::begin(myMap)
            it != myMap.end();                              // the same as std::end(myMap)
            ++it)
    {
        // before we output (print) another value (pair), we need to skip some
        // (t - 1)-elements
        while (numOfSkippedElements /*!= 0*/            // all the int values are casted to a logical value implicitly: 0 gives false, all other numbers give true
               && it != myMap.end())
        {
            ++it;
            --numOfSkippedElements;
        }
        // altervatively we consider the condition for breaking (terminating) the while loop above:
        // either we skipped all the necessary elements or reached the end of the collection and we can't skip anything more

        // we can get out the loop under two conditions, and we must check the last one
        if (it == myMap.end())
            break;

        std::cout << it->first << " => " << it->second << ", ";         // an alternative approach

        numOfSkippedElements = t - 1;                   // the number of element to skip at the next iteration of the loop must be reset (restored)
    }

    std::cout << "}";
}




/// Look for a given key \a key in the given map \a myMap. If the key exists,
/// \returns true and the associated value by using another reference variable,
/// otherwise return false and the value of the ref var is undefined.

bool findKeyInMap(const IntSizetMap& myMap, int key, size_t& val)
{
   IntSizetMap::const_iterator it = myMap.find(key);
   if (it == myMap.end())
       return false;

    // if we reach this very point, we have a valid non-end iterator that points
    // to a element with the key \a key
    //   Here ((*it).first == key) is an invariant.
    val = (*it).second;
    return true;
}

// TODO: HW: Modify the method (create another (overloaded?) variant)
// that returns a pair of <bool, size_t> with corresponding values.


int main()
{
    // TODO: HW: ask a user for inputting some n, p, q...

    // check the individual methods
    IntVector vec = makeVector(10, -3, 3);      // want to generate 10 random values from [-3; 3]
    printVec(vec);
    std::cout << '\n';
    printBackVec(vec);
    std::cout << '\n';

    // create a map from the vector
    IntSizetMap map1 = createMapFromVec(vec);
    printMap(map1);
    std::cout << '\n';

    std::cout << "Print keys only: ";
    printMapKeys(map1);
    std::cout << '\n';

    std::cout << "Print each 2nd elements of the map: ";
    printEachTthMapElement(map1, 2);
    std::cout << '\n';

    size_t val;
    if (findKeyInMap(map1, 0, val))
        std::cout << "Found a value for key 0, which is: " << val;

    if (findKeyInMap(map1, 42, val))
        std::cout << "Found a value for key 42, which is: " << val;

    std::cout << '\n';

    return 0;
}


