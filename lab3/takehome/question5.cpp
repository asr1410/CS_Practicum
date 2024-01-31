#include <bits/stdc++.h>
#include "queue.hpp"

using namespace std;

int helper(custom::queue<int> &q, int mod)
{
    int count = 1;
    while (q.size() != 1)
    {
        if (count % mod == 0)
        {
            cout << q.pop() << endl;
            count = 1;
        }
        else
        {
            q.push(q.pop());
            count++;
        }
    }
    return q.pop();
}
int main()
{
    int count, mod;
    cin >> count >> mod;
    custom::queue<int> q;

    for (int i = 0; i < count; i++)
    {
        int person;
        cin >> person;
        q.push(person);
    }
    cout << "winner is " << helper(q, mod) << endl;
    return 0;
}