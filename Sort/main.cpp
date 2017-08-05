#include <vector>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include "SortRoutines.h"
using namespace std;

long long n_compare = 0;
long long n_invert = 0;

void mergesort(std::vector<int> &v)
{
    // the mergesort algorithm uses the divide and conquer
    // approach. at every step in the recursion it splits
    // the vector into two halves, sorts each and then combine
    // them. it is a O(n*log(n)) algorithm.
    
    if (v.size() > 1)
    {
        // split the vector in two halves
        int n2 = v.size()/2;
        std::vector<int> lv(v.begin(), v.begin()+n2);
        std::vector<int> rv(v.begin()+n2, v.end());
    
        // sort the left and right vectors
        mergesort(lv);
        mergesort(rv);

        // merge the left and right sorted vectors
        std::vector<int> merged;
        vector<int>::iterator lit = lv.begin();
        vector<int>::iterator rit = rv.begin();

        int len_lv = lv.size();
        while (lit != lv.end() && rit != rv.end())
        {
            if (*lit <= *rit)
            {
                merged.push_back(*lit++);
                len_lv--;
            }
            else
            {
                merged.push_back(*rit++);
                n_invert += len_lv;
            }
        }
        while (lit != lv.end()) merged.push_back(*lit++);
        while (rit != rv.end()) merged.push_back(*rit++);
        v = merged;
    }
}

void quicksort(std::vector<int> &v, int pivot_type)
{
    // the quicksort algorithm uses the divide and conquer
    // approach. at every step in the recursion it creates
    // a partition and sorts the left and right elements of
    // the partition. it is a O(n*log(n)) algorithm but a
    // bad choice of pivot (first element) and a sorted vector
    // to start with will end up a O(n^2) runtime.

    if (v.size() > 1)
    {
        int p = create_pivot(v, pivot_type);
        p = partition(v);

        std::vector<int>::const_iterator first = v.begin();
        std::vector<int>::const_iterator last = v.begin() + p - 1;
        std::vector<int> vleft(first, last);
        quicksort(vleft, pivot_type);
        std::copy(vleft.begin(), vleft.end(), v.begin());

        first = v.begin() + p;
        last = v.end();
        std::vector<int> vright(first, last);
        quicksort(vright, pivot_type);
        std::copy(vright.begin(), vright.end(), v.begin() + p);

        n_compare += (v.size() - 1);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "enter filename, algorithm (quicksort, mergesort)" << std::endl;
        return 1;
    }

    std::vector<int> x = {};

    // open file
    std::ifstream inputFile(argv[1]);

    // test file open
    if (inputFile)
    {
        int value;

        // read the elements in the file into a vector
        while ( inputFile >> value )
            x.push_back(value);
    }

    std::string algo = argv[2];
    if (algo == "quicksort")
    {
        int pivot_type  = 3; //left most: 1, right most: 2, median:3
        quicksort(x, pivot_type);
        print_vector(x);
        std::cout << "number of comparisons = " << n_compare << std::endl;
    }
    else if (algo == "mergesort")
    {
        mergesort(x);
        print_vector(x);
        std::cout << "Number of inversions = " << n_invert << std::endl;
    }
    else
    {
        std::cerr << "specify a correct algorithm (mergesort, quicksort) \n";
        return 1;
    }
}
