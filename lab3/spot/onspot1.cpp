#include <bits/stdc++.h>
#include "queue.hpp"
using namespace std;

int main()
{
    fstream file;
    string word, filename;
    filename = "input.txt";
    file.open(filename);
    int rotation, count = 0;
    custom::queue<int> q;
    while (file >> word)
        if (count++ == 0)
            rotation = stoi(word);
        else
            q.push(stoi(word));
    while (rotation--)
        q.push(q.pop());

    ofstream myfile;
    myfile.open("output.txt");
    while (!q.empty())
        myfile << q.pop() << " ";
    myfile.close();
    return 0;
}