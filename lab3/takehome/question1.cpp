#include <iostream>
#include "stack.hpp"

using namespace std;

float helper(string &s, int &index)
{
    custom::stack<float> st;
    while (index > -1)
    {
        if (s[index] == ' ')
        {
            index--;
            continue;
        }
        else if (s[index] == ')')
        {
            index--;
            st.push(helper(s, index));
        }
        else if (s[index] == '(')
        {
            index--;
            return st.top();
        }
        else if (s[index] == '+')
        {
            index--;
            float a = st.pop();
            float b = st.pop();
            st.push(a + b);
        }
        else if (s[index] == '/')
        {
            index--;
            float a = st.pop();
            float b = st.pop();
            st.push(a / b);
        }
        else if (s[index] == '-')
        {
            index--;
            float a = st.pop();
            float b = st.pop();
            st.push(a - b);
        }
        else if (s[index] == '*')
        {
            index--;
            float a = st.pop();
            float b = st.pop();
            st.push(a * b);
        }
        else
        {
            string temp = "";
            while (index > -1 and s[index] != ' ')
            {
                temp.push_back(s[index]);
                index--;
            }
            reverse(temp.begin(), temp.end());
            st.push(stoi(temp));
        }
    }
    return st.top();
}

int main()
{
    string s;
    getline(cin, s, '\n');
    int index = s.size() - 1;
    cout << helper(s, index) << endl;
}
