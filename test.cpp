#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

string decToHexa(int n)
{
    // ans string to store hexadecimal number
    string ans = "";

    while (n != 0)
    {
        int rem = 0;
        char ch;
        rem = n % 16;
        if (rem < 10)
        {
            ch = rem + 48;
        }
        else
        {
            ch = rem + 55;
        }
        ans += ch;
        n = n / 16;
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

// Driver code
int main()
{
    int n = 25;

    cout << decToHexa(n);

    return 0;
}