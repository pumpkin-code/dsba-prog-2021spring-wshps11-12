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


// TODO: HW: try to create a method that output the content of the given map as
// a sequence of <key, value> pairs
// Mention that IntSizetMap::const_iterator gives you a reference to the pair,
// whose first element is the key, and the second is the value
void printMap(const IntSizetMap& vec)
{
    // TODO: try to use the range-based for loop, firstly
    // TODO: try to use the iteratos-based approach, secondly
}


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

    return 0;
}


