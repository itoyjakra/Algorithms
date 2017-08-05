#include <vector>
#include <iostream>
#include <fstream>
#include <assert.h>
#include "SortRoutines.h"
using namespace std;

long long n_compare = 0;

void quicksort(std::vector<int> &v, int pivot_type)
{
    // the quicksort algorithm uses the divide and conquer
    // approach. at every step in the recursion it creates
    // a partition and sorts the left and right elements of
    // the partition

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

int main()
{
    std::vector<int> x = {};

    // open file
    std::ifstream inputFile("sort.txt");

    // test file open
    if (inputFile)
    {
        int value;

        // read the elements in the file into a vector
        while ( inputFile >> value )
            x.push_back(value);
    }

    int pivot_type  = 3; //left most: 1, right most: 2, median:3
    quicksort(x, pivot_type);
    print_vector(x);
    std::cout << "number of comparisons for pivot type " << pivot_type << "  = " << n_compare << std::endl;
}
