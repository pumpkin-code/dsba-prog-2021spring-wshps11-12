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

#include <vector>
#include <random>       // for random generator
#include <ctime>        // for time() method
#include <utility>      // for swap
#include <iostream>
#include <map>

using VectOfInts = std::vector<int>;
using Int2SizetMap = std::map<int, size_t>;

// Creates a vector of integers from the range [r, q]
VectOfInts makeRandVector(size_t n, int r, int q)
{
    // make sure that r <= q
    if (q < r)
        std::swap(r, q);

    std::mt19937 gen(time(nullptr));
    //std::random_device rd;                  // alternative for time()
    //std::mt19937 gen(rd);
    std::uniform_int_distribution<> distrib(r, q);

    // distrib(gen)                         // gives another uniformly distributed “random” (pseudo) value

    VectOfInts vec;
    for (size_t i = 0; i < n; ++i)
    {
        int yetAnotherRandomValue = distrib(gen);
        vec.push_back(yetAnotherRandomValue);
    }

    return vec;
}

// Prints the given vector
void printVec(const VectOfInts& vec)
{
    // TODO: we could use the range-based for loop,

    // const_terator is a datatype defined in the scope of std::vector<>:: class
    // when we use the auto keyword, actually, the compiler puts a most appropriate
    // iterator type from the vector's definition. This is why we want to AVOID
    // using the auto keyword until we can provide the real name of the used
    // iterator datatype explicitly.
    // We can't use iterator instead of const_iterator, because the container object
    // is passed BY CONST REFERENCE/ the iterator must also be protected from changing
    for (VectOfInts::const_iterator it = vec.begin();       // <====> std::begin(vec)
            it != vec.end();                                // <====> std::end(vec)
            ++it)                                           // advance the iterator, moving it towards the end of the collection
    {
        std::cout << *it << "\t";
    }

}


// Prints the given vector in the backward order
void printVecReversed(const VectOfInts& vec)
{
    // we can't use the range-based for loop,

    for (VectOfInts::const_reverse_iterator it = vec.rbegin();       // <====> std::rbegin(vec)
            it != vec.rend();                                // <====> std::rend(vec)
            ++it)                                           // advance the iterator, moving it towards the beginning of the collection
    {
        std::cout << *it << "\t";
    }
}


Int2SizetMap makeMapFromVector(const VectOfInts& vec)
{
    Int2SizetMap resMap;

    // TODO: HW: remaster the following code with using the iterators. Consider
    // the iterator datatypes appearing EXPLICITLY (no the auto keyword!)
    for (int el : vec)
    {
        // we could use the operator[] for increasing the number of corresponding element
        // in the map, however, we are not sure that the initial valu for any POD
        // types, such as int, will be initialize with 0.

        // el is an element we need to consider as a key in the map, and to increase
        // the number of occurences at each new appearance

        // so we are going to check the presence of an element with the given key instead
        Int2SizetMap::iterator it2PrevElement = resMap.find(el);
        if (it2PrevElement == resMap.end())             // the given key does not exist
        {
            resMap.insert( { el , 1 } );
                        //  ^ a key, the element from the vector
                         //       ^ a value indicating the number of times that the key appears in the vector
        }
        else
        {
            //it2PrevElement->first == el  <===> (*it2PrevElement).first == el
            ++it2PrevElement->second;              // (*it2PrevElement).second
        }

        // TODO: rewrite it for the case of using the return value of the insert method
    }

    return resMap;
}



// Prints out the content of the map in the forward order by pairs of elements.
void printMap(const Int2SizetMap& coll)
{
    // TODO: HW: try to remaster the code with using the iterators

    for (const std::pair<int, size_t>& el  :  coll) // we could use copy assignment here instead of const ref,
    {
        std::cout << "{ " << el.first           // el.first is the key
                  << ", " << el.second          // el.second is the value
                  << " }\t";
    }
}




int main()
{
    // TODO: ask a user to input some data....

    // testing individual functions
    VectOfInts vec = makeRandVector(10, 1, 5);
    printVec(vec);
    std::cout << "\n";
    printVecReversed(vec);
    std::cout << "\n";

    // creates a map from the given vector
    Int2SizetMap map1 = makeMapFromVector(vec);
    printMap(map1);
    std::cout << "\n";


    return 0;
}


