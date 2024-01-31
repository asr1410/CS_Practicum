#include <bits/stdc++.h>
#include "queue.hpp"
using namespace std;

int main()
{
    custom::queue<string> q;
    int testCases;
    cin >> testCases;
    for (int i = 0; i < testCases; i++)
    {
        int commands;
        cin >> commands;
        custom::queue<string> q;
        q.push("/");
        for (int j = 0; j < commands; j++)
        {
            string input;
            getline(cin, input, '\n');
            if (input.substr(0, 3) == "cd ")
            {
                vector<string> store;
                if (input[3] == '/')
                {
                    istringstream iss(input.substr(4, input.size()));
                    string token;
                    while (getline(iss, token, '/'))
                    {
                        if (token == "..")
                        {
                            if (store.size())
                                store.pop_back();
                        }
                        else
                        {
                            store.push_back(token);
                        }
                    }
                    string temp = "";
                    for (int i = 0; i < store.size(); i++)
                    {
                        if (i == 0)
                        {
                            temp += "/";
                            temp += store[i];
                            temp += "/";
                        }
                        else
                        {
                            temp += store[i];
                            temp += "/";
                        }
                    }
                    q.pop();
                    q.push(temp);
                }
                else
                {
                    istringstream iss(q.pop());
                    string token;
                    while (getline(iss, token, '/'))
                    {
                        if (token == "..")
                        {
                            if (store.size())
                                store.pop_back();
                        }
                        else
                        {
                            store.push_back(token);
                        }
                    }
                    token = "";
                    istringstream is(input.substr(3, input.size()));
                    while (getline(is, token, '/'))
                    {
                        if (token == "..")
                        {
                            if (store.size())
                                store.pop_back();
                        }
                        else
                        {
                            store.push_back(token);
                        }
                    }
                    token = "";
                    for (int i = 0; i < store.size(); i++)
                    {
                        if (i == 0)
                        {
                            token += "/";
                            token += store[i];
                            token += "/";
                        }
                        else
                        {
                            token += store[i];
                            token += "/";
                        }
                    }

                    q.push(token);
                }
            }
            else if (input.substr(0, 3) == "pwd")
            {
                cout << q.front() << endl;
            }
        }
    }

    return 0;
}
