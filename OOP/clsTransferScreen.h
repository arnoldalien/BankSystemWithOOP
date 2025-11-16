

#pragma once

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "Global.h"

class clsTransferScreen : protected clsScreen
{

private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________\n";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.GetAccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

	static double _ReadAmount(clsBankClient SourceClient)
	{
		double Amount = 0;

		cout << "\nEnter Transfer Amount? ";

		Amount = clsInputValidate::ReadDblNumber();

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
			Amount = clsInputValidate::ReadDblNumber();
		}

		return Amount;
	}

	static string _ReadAccountNumber(string Massege)
	{
		string AccountNumber = "";

		cout << Massege;
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t  Transfer Screen");

		clsBankClient SourceCleint = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number to Transfer From : "));

		_PrintClient(SourceCleint);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number to Transfer To : "));

		_PrintClient(DestinationClient);

		double Amount = _ReadAmount(SourceCleint);

		cout << "\nAre you sure you want to perform this operation? y/n? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			if (SourceCleint.Transfer(Amount, DestinationClient, CurrentUser.GetUserName()))
			{
				cout << "\nTransfer done successfully\n";
			}
			else
			{
				cout << "\nTransfer Faild '\n";
			}
		}

		_PrintClient(SourceCleint);
		_PrintClient(DestinationClient);
	}
};