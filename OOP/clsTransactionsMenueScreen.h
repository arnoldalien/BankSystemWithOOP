
#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionsMenueScreen : protected clsScreen
{
private:
	
	enum enTransactionsMenueOptions {
		eDeposit = 1, eWithdraw = 2, eShowTotalBalances = 3, eTransfer = 4, eTransferLog = 5, eGoBackToMainMenue = 6 
	};

	static short _ReadTransactionsMenueOptions()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 8, "Enter Number between 1 to 5? ");
		return Choice;
	}

	static  void _GoBackToTransactionsMenue()
	{
		cout << setw(37) << left << "" << "\nPress any key to go back to Transactions Menue...\n";
		system("pause>0");
		ShowTransactionsMenueScreen();
	}

	static void _ShowDepositScreen()
	{
		//cout << "\nDeposit Screen Will be here...\n";
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		//cout << "\nWithdraw Screen Will be here";
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		//"\nBalances Screen Will be here";
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogListScreen();
	}

	static void _GoBackToMainMenueScreen()
	{
		
	}

	static void _PerFromTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
	{
		switch (TransactionsMenueOption)
		{
		case clsTransactionsMenueScreen::eDeposit:
		{
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case clsTransactionsMenueScreen::eWithdraw:
		{
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case clsTransactionsMenueScreen::eShowTotalBalances:
		{
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;
		}

		case clsTransactionsMenueScreen::eTransfer:
		{
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
		}

		case clsTransactionsMenueScreen::eTransferLog:
		{
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenue();
		}

		case clsTransactionsMenueScreen::eGoBackToMainMenue:
		{
			break;
		}

		}
	}

public:

	static void ShowTransactionsMenueScreen()
	{
		if (!CheckAccessRights(clsUsers::enPermissions::pTranactions))
		{
			return;
		}

		system("cls");

		_DrawScreenHeader("\t Transactions Menue");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t Transactions Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n"; 
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerFromTransactionsMenueOption(enTransactionsMenueOptions(_ReadTransactionsMenueOptions()));
	}
};