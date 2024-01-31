#include <bits/stdc++.h>
using namespace std;
#include "stack.hpp"
int main()
{
    int size;
    cin >> size;
    vector<int> nums(size);
    for (int i = 0; i < size; i++)
        cin >> nums[i];
    custom::stack<int> s;
    for (int i = 0; i < size; i++)
    {
        s.push(nums[i]);
        int j = i + 1;
        while (j < size)
        {
            if (nums[j] > s.top())
            {
                s.pop();
                s.push(nums[j]);
                break;
            }
            j++;
        }
        if (nums[i] != s.top())
            cout << s.top() << " ";
    }
    cout << -1;
    return 0;
}