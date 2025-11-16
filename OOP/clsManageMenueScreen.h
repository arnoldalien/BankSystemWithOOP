
#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageMenueScreen : protected clsScreen
{
private:

	enum enManageUsersMenueOptions {
		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
	};

	static short _ReadManageUsersMenueOptions()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 8, "Enter Number between 1 to 6? ");
		return Choice;
	}
	
	static  void _GoBackToManageUserMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Manage User Menue...\n";

		system("pause>0");
		ShowManageUserMenueScreen();
	}

	static void _PerFromManageUserMenueOptions(enManageUsersMenueOptions ManageUsersMenueOptions)
	{	
		switch (ManageUsersMenueOptions)
		{
		case clsManageMenueScreen::eListUsers:
		{
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUserMenue();
			break;
		}

		case clsManageMenueScreen::eAddNewUser:
		{
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUserMenue();
			break;
		}

		case clsManageMenueScreen::eDeleteUser:
		{
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUserMenue();
			break;
		}

		case clsManageMenueScreen::eUpdateUser:
		{
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUserMenue();
			break;
		}

		case clsManageMenueScreen::eFindUser:
		{
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUserMenue();
			break;
		}

		case clsManageMenueScreen::eMainMenue:
		{
			break;
		}

		}
	}

	static void _ShowListUsersScreen()
	{
		//cout << "\nList Users Screen will be here";
		clsListUsersScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		//cout << "\nAdd New User Screen will be here";
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		//cout << "\nDelete User Screen will be here";
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		//cout << "\nUpdate User Screen will be here";
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		//cout << "\nFind User Screen will be here";
		clsFindUserScreen::ShowFindUsersScreen();
	}

public:

	static void ShowManageUserMenueScreen()
	{

		if (!CheckAccessRights(clsUsers::enPermissions::pManageUsers))
		{
			return;
		}

		system("cls");

		_DrawScreenHeader("\t Manage User Menue");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t Manage User Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerFromManageUserMenueOptions(enManageUsersMenueOptions(_ReadManageUsersMenueOptions()));
	}
};