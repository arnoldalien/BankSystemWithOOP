

#pragma once

#include "clsScreen.h"
#include "clsUsers.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
{

private:

    static void _PrintUser(clsUsers User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermission  : " << User.Permissions;
        cout << "\n___________________\n";
    }

public:

    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("\t  Delete User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUsers::IsUserExist(UserName))
        {
            cout << "\nUser is not found, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUsers User = clsUsers::Find(UserName);

        _PrintUser(User);

        cout << "\nAre you sure you want to delete this User y/n? ";

        char Answer = 'n';

        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            if (User.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";

                _PrintUser(User);
            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
    }
};