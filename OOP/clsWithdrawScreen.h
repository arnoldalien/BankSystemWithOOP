
#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsWithdrawScreen : protected clsScreen
{
private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.GetAccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }

public:
    
    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t    Withdraw Screen");

        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not Exist";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        cout << "\nPlease Enter withdraw amount? ";
        double Amount = clsInputValidate::ReadDblNumber();

        if (Amount == 0)
        {
            cout << "\nOperation was cancelled.\n";
            return;
        }

        if (Client1.GetAccountBalance() >= Amount)
        {
            cout << "\nAre sure you want to perform this transaction? ";
            char Answer = 'n';
            cin >> Answer;

            if (Answer == 'Y' || Answer == 'y')
            {
                Client1.Withdraw(Amount);
                cout << "\nAmount Withdraw Successfully.\n";
                cout << "\nNew Balance Is: " << Client1.GetAccountBalance() << endl;
            }
           
        }
        else
        {
            cout << "\nCannot withdraw, Insuffecient Balance!\n";
            cout << "\nAmount to withdraw is: " << Amount << endl;
            cout << "Your Balance is: " << Client1.GetAccountBalance() << endl;
        }
    }
};