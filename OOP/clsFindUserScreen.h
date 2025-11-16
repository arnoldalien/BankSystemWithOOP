

#pragma once

#include "clsUsers.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsFindUserScreen : protected clsScreen
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

    static void ShowFindUsersScreen()
    {
        _DrawScreenHeader("\t Find User Screen");

        string UserName;
        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUsers::IsUserExist(UserName))
        {
            cout << "\nUserName is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUsers User1 = clsUsers::Find(UserName);

        if (!User1.IsEmpty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not found :-(\n";
        }

        _PrintUser(User1);
    }
};