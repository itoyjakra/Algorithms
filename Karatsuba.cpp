// Karatsuba algorithm for integer multiplication
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include <limits>
#include <stack>
#include <assert.h>
using namespace std;

string add(string x, string y)
{
    stack<int> sx, sy, result;
    for (int i=0; i<x.length(); i++)
        sx.push(stoi(x.substr(i, 1)));
    for (int i=0; i<y.length(); i++)
        sy.push(stoi(y.substr(i, 1)));

    int carry = 0;
    while (!sx.empty() || !sy.empty())
    {
        int a = 0;
        if (!sx.empty())
        {
            a = sx.top();
            sx.pop();
        }
        int b = 0;
        if (!sy.empty())
        {
            b = sy.top();
            sy.pop();
        }
        int sum = a + b + carry;
        carry = 0;
        if (sum > 9)
        {
            result.push(sum - (sum/10) * 10);
            carry = sum / 10;
        }
        else
            result.push(sum);
    }
    if (carry > 0)
        result.push(carry);

    string add;
    while (!result.empty())
    {
        add += to_string(result.top());
        result.pop();
    }

    return (add);
}

string subtract(string x, string y)
{
    stack<int> sx, sy, result;
    for (int i=0; i<x.length(); i++)
        sx.push(stoi(x.substr(i, 1)));
    for (int i=0; i<y.length(); i++)
        sy.push(stoi(y.substr(i, 1)));

    int borrow = 0;
    while (!sx.empty())
    {
        int a = sx.top();
        sx.pop();
        int b = 0;
        if (!sy.empty())
        {
            b = sy.top();
            sy.pop();
        }

        if (a < (b + borrow))
        {
            result.push(10 + a - borrow - b);
            borrow = 1;
        }
        else
        {
            result.push(a - b - borrow);
            borrow = 0;
        }
    }

    string sub;
    while (!result.empty())
    {
        sub += to_string(result.top());
        result.pop();
    }
    while (sub.front() == '0')
        sub.erase(0, 1);

    return (sub);
}

string mult(string x, string y)
{
    int n = x.length() < y.length() ? x.length() : y.length();
    if (n > 1)
    {
        int n2 = n/2;

        string a = x.substr(0, x.length()-n2);
        string b = x.substr(x.length()-n2);
        string c = y.substr(0, y.length()-n2);
        string d = y.substr(y.length()-n2);


        string ac = mult(a, c);
        string bd = mult(b, d);
        
        string apb_cpd = mult(add(a, b), add(c, d));

        if (n % 2 == 1) n--;
        string ad_bc = subtract(apb_cpd, ac);
        ad_bc = subtract(ad_bc, bd);
        for (int i=0; i<n2; i++)
            ad_bc += '0';
        for (int i=0; i<n; i++)
            ac += '0';

        string res = add(ac, bd);
        res = add(res, ad_bc);

        return (res);
    }
    else
        return( to_string(stoi(x) * stoi(y)) );

}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Enter two numbers\n";
        return 1;
    }

    string x = argv[1];
    string y = argv[2];
    string m = mult(x, y);
    std::cout << m << std::endl;
}
