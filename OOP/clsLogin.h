

#pragma once

#include "Global.h"
#include "clsUsers.h"
#include "clsScreen.h"
#include "clsMainSecreen.h"

class clsLoginScreen : protected clsScreen
{
private:

	static bool _Login()
	{
		bool LoginFaild = false;
		short FaildLoginCount = 0;

		string UserName, Password;
		do
		{

			if (LoginFaild)
			{
				FaildLoginCount++;

				cout << "\n\t\t\t\t\tInvlaid Username/Password!\n";
				cout << "\t\t\t\t\tYou have " << 3 - FaildLoginCount
					<< " Trial(s) to login.\n\n";
			}

			if (FaildLoginCount == 3)
			{
				cout << "\033[31m\t\t\t\t\tYou are Locked after 3 trials\n\n\033[0m";
				return false;
			}

			cout << "\t\t\t\t\tEnter Userame? ";
			cin >> UserName;

			cout << "\t\t\t\t\tEnter Password? ";
			cin >> Password;

			CurrentUser = clsUsers::Find(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogIn();
		clsMainSecreen::ShowMainMenue();
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t     Login Screen");
		return _Login();
	}
};