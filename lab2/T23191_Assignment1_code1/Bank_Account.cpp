#include <bits/stdc++.h>
using namespace std;

class Bank_Account
{
private:
    string name;
    long long account_number;
    string type_of_account;
    double balance_amount;

public:
    Bank_Account(){};
    void CreateAccount(string aname, long long anum, string atype)
    {
        name = aname;
        account_number = anum;
        type_of_account = atype;
        balance_amount = 0;
    }
    void Balance()
    {
        cout << "Current Balance : " << balance_amount << endl;
    }
    void Deposit(double damount)
    {
        balance_amount += damount;
    }
    void Withdraw(double wamount)
    {
        if (balance_amount < wamount)
            cout << "You can withdraw amount upto " << balance_amount << endl;
        else
            balance_amount -= wamount;
    }
    void Display()
    {
        cout << "Name of Account Holder : " << name << endl;
        cout << "Account Number : " << account_number << endl;
        cout << "Type of Account : " << type_of_account << endl;
        cout << "Balance Amount : " << balance_amount << endl;
    }
};

int main()
{
    Bank_Account nUser;
    string aname, atype;
    long long anum, abal;
    cout << "Online Bank Account" << endl;
    cout << "Enter the Details to create Account" << endl;
    cout << "Enter Name : ";
    getline(cin, aname, '\n');
    cout << "Enter Unique Account Number : ";
    cin >> anum;
    cout << "Enter Type of Account : ";
    cin >> atype;
    nUser.CreateAccount(aname, anum, atype);
    while (1)
    {

        cout << "1. Deposit Money" << endl;
        cout << "2. Withdraw Money" << endl;
        cout << "3. Account Details" << endl;
        cout << "4. Exit" << endl;
        int option;
        cout << "Enter the Option : ";
        cin >> option;
        if (option == 1)
        {
            int dmoney;
            cout << "Amount to be deposited : ";
            cin >> dmoney;
            nUser.Deposit(dmoney);
        }
        else if (option == 2)
        {
            nUser.Balance();
            int wmoney;
            cout << "Amount to withdraw : ";
            cin >> wmoney;
            nUser.Withdraw(wmoney);
        }
        else if (option == 3)
        {
            nUser.Display();
        }
        else
        {
            return 0;
        }
    }

    return 0;
}