#include <bits/stdc++.h>
using namespace std;

class Associate
{
private:
    int id;
    string technology;
    int experienceInYears;

public:
    Associate()
    {
        id = 0;
        technology = "";
        experienceInYears = 0;
    }

    Associate(int lid, string ltechnology, int lexperienceInYears)
    {
        id = lid;
        technology = ltechnology;
        experienceInYears = lexperienceInYears;
    }

    int returnId()
    {
        return id;
    }

    string returntechnology()
    {
        return technology;
    }

    int returnexperienceInYears()
    {
        return experienceInYears;
    }
};

class Solution
{
private:
public:
    string toLower(string searchTechnology)
    {
        for (auto &character : searchTechnology)
        {
            if (character >= 'A' && character <= 'Z')
            {
                character += 32;
            }
        }
        return searchTechnology;
    }

    vector<Associate> associatesForGivenTechnology(vector<Associate> &empData, string searchTechnology)
    {
        vector<Associate> matched;
        string searchTechnologyLowerCase = toLower(searchTechnology);
        for (Associate &emp : empData)
        {
            if (emp.returnexperienceInYears() % 5 == 0 && emp.returntechnology() == searchTechnologyLowerCase)
            {
                matched.push_back(emp);
            }
        }
        return matched;
    }
};

int main()
{
    vector<Associate> emps;
    int numEmployees = 5;

    for (int i = 0; i < numEmployees; ++i)
    {
        int id, exp;
        string tech;
        cout << "Enter Employee Id: ";
        cin >> id;
        cout << "Enter Technology: ";
        cin >> tech;
        cout << "Enter Experience: ";
        cin >> exp;
        Associate temp(id, tech, exp);
        emps.push_back(temp);
    }

    Solution s;
    string srch;
    cout << "Enter the Technology to search for: ";
    cin >> srch;
    for (Associate emp : s.associatesForGivenTechnology(emps, srch))
        cout << emp.returnId() << endl;
    return 0;
}