

#pragma once

#include "clsScreen.h"
#include "clsUsers.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen : protected clsScreen
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

    static void _ReadUserInfo(clsUsers& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }

    static int _ReadPermissionsToSet()
    {
        int Permissions = 0;
        char Answer = 'n';

        cout << "\nDo you want to give full access ? Y/N? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to:\n";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::pListClients;
        }


        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::pAddNewClient;
        }


        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::pDeleteClient;
        }


        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::pUpdateClients;
        }


        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::pFindClient;
        }


        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::pTranactions;
        }


        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::pManageUsers;
        }

        cout << "\nShow Login Register? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUsers::enPermissions::pShowLogInRegister;
        }

        return Permissions;
    }

 public:

     static void ShowUpdateUserScreen()
     {
         _DrawScreenHeader("\t  Update User Screen");

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

         cout << "\nUpdate User Info:";
         cout << "\n___________________\n";

         _ReadUserInfo(User);

         clsUsers::enSaveResults SaveResult;

         SaveResult = User.Save();

         switch (SaveResult)
         {
         case clsUsers::svFaildEmptyObject:
         {
             cout << "\nError Account Was Not Saved Because Its Empty";
             break;
         }

         case clsUsers::svSucceeded:
         {
             cout << "\nUser Updated Successfully :-)\n";
             _PrintUser(User);
             break;
         }
         }
     }
};