#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClient.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsMenueScreen.h"
#include "clsManageMenueScreen.h"
#include "clsLoginRegisterScreen.h"
#include "Global.h"

class clsMainSecreen : protected clsScreen
{
private:

    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eRegisterLogin = 8, eExit = 9
    };

    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 9]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 9, "Enter Number between 1 to 9? ");
        return Choice;
    }

    static  void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen()
    {
        //cout << "\nClient List Screen Will be here...\n";
        clsClientListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientsScreen()
    {
        //cout << "\nAdd New Client Screen Will be here...\n";
        clsAddNewClient::AddNewClient();
    }

    static void _ShowDeleteClientScreen()
    {
        //cout << "\nDelete Client Screen Will be here...\n";
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        //cout << "\nUpdate Client Screen Will be here...\n";
        clsUpdateClientScreen::UpdateClient();
    }

    static void _ShowFindClientScreen()
    {
       //cout << "\nFind Client Screen Will be here...\n";
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        //cout << "\nTransactions Menue Will be here...\n";
        clsTransactionsMenueScreen::ShowTransactionsMenueScreen();
    }

    static void _ShowManageUsersMenue()
    {
        //cout << "\nUsers Menue Will be here...\n";
        clsManageMenueScreen::ShowManageUserMenueScreen();
    }

    static void _ShowRegisterLoginScreen()
    {
       // cout << "\nRegister Login Screen will be here.\n";

        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

   /* static void _ShowEndScreen()
    {
        cout << "\nEnd Screen Will be here...\n";

    }*/

    static void _Logout()
    {
        CurrentUser = clsUsers::Find("", "");
    }

    static void _PerFromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case clsMainSecreen::eListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }

        case clsMainSecreen::eAddNewClient:
        {
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;
        }

        case clsMainSecreen::eDeleteClient:
        {
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;
        }

        case clsMainSecreen::eUpdateClient:
        {
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;
        }

        case clsMainSecreen::eFindClient:
        {
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;
        }

        case clsMainSecreen::eShowTransactionsMenue:
        {
            system("cls");
           _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;
        }

        case clsMainSecreen::eManageUsers:
        {
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eRegisterLogin:
        {
            system("cls");
            _ShowRegisterLoginScreen();
            _GoBackToMainMenue();
        }

        case clsMainSecreen::eExit:
        {
            system("cls");
            _Logout();
            //_Login();
            break;
        }

        }
    }

public:

        
    static void ShowMainMenue()
    {
        system("cls");

        _DrawScreenHeader("            Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t     Main Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerFromMainMenueOption(enMainMenueOptions(_ReadMainMenueOption()));
    }
};