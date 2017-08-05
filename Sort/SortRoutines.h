#include <vector>
#include <iostream>
#include <fstream>
#include <assert.h>
using namespace std;

void print_vector(std::vector<int> v)
{
    for (int i=0; i<v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << "\n";
}

void swap(std::vector<int> &v, int i, int j)
{
    // swaps the i-th and j-th elements of vector v
    int x;
    x = v[i];
    v[i] = v[j];
    v[j] = x;
}

int find_median(std::vector<int> v)
{
    // returns the median elements of a vector.
    // median is calculated as the middle largest
    // element between the first, last and middle 
    // element

    int k;
    if (v.size() % 2 == 0)
        k = v.size() / 2 - 1;
    else
        k = v.size() / 2;

    int i = 0;
    int j = v.size() - 1;

    if ((v[i] > v[j] && v[i] < v[k]) || (v[i] < v[j] && v[i] > v[k]))
        return (i);
    else if ((v[j] > v[i] && v[j] < v[k]) || (v[j] < v[i] && v[j] > v[k]))
        return (j);
    else
        return (k);
}

int  create_pivot(std::vector<int> &v, int scheme)
{
    // creates a pivot element and swaps it with
    // the first element of the vector

    if (scheme == 1) // pivot is left most element
    {
        return (v[0]);
    }
    else if (scheme == 2) // pivot is right most element
    {
        swap(v, 0, v.size()-1);
        return (v[0]);
    }
    else if (scheme == 3) // pivot is the median element
    {

        int median_index = find_median(v);
        swap(v, 0, median_index);
        return (v[0]);
    }
    else // wrong pivot  value
    {
        return (-1);
    }
}

int partition(std::vector<int> &v)
{
    // create a partition in the vector based
    // on the first element as a pivot.
    // after the partition the pivot element
    // will be at the correct place, elements to the
    // left will all be smaller than the pivot and
    // elements to the right will all be larger than
    // the pivot element.

    int pivot = v[0];
    int p = 1;
    for (int i=1; i<v.size(); i++)
    {
        if (v[i] < pivot)
        {
            swap(v, i, p);
            p++;
        }
    }
    swap(v, 0, p-1);
    return (p);
}
