#include <bits/stdc++.h>
#include "queue.hpp"
using namespace std;

void helper(int n)
{
    if (n > 0)
    {
        int s;
        custom::queue<int> q;
        q.push(1);
        while (n--)
        {
            s = q.front();
            q.pop();
            cout << s << endl;
            s *= 10;
            q.push(s + 0);
            q.push(s + 1);
        }
    }
}

int main()
{
    int n;
    cin >> n;
    helper(n);
    return 0;
}