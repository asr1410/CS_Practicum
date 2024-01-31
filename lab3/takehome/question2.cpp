#include <bits/stdc++.h>
#include "stack.hpp"
using namespace std;

int count(string s)
{
    custom::stack<char> st;
    int count = 0;

    for (char c : s)
    {
        if (c == '(')
            st.push(c);
        else if (c == ')')
        {
            if (st.empty())
                return -1;

            st.pop();
            count++;
        }
    }

    if (!st.empty())
        return -1;

    return count;
}

int main()
{
    string s;
    getline(cin, s, '\n');
    cout << count(s) << endl;

    return 0;
}
