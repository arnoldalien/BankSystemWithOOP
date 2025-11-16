
#pragma once

#include <iostream>
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsDeleteClientScreen : protected clsScreen
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

public:

    static void ShowDeleteClientScreen()
    {
        if (!CheckAccessRights(clsUsers::enPermissions::pDeleteClient))
        {
            return;
        }

        _DrawScreenHeader("\t Delete Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number is not found, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

            cout << "\nAre you sure you want to delete this Client y/n? ";

            char Answer = 'n';

            cin >> Answer;

            if (tolower(Answer) == 'y')
            {
                if (Client1.Delete())
                {
                    cout << "\nClient Deleted Successfully :-)\n";

                    _PrintClient(Client1);
                }
                else
                {
                    cout << "\nError Client Was not Deleted\n";
                }
        }
    }
};