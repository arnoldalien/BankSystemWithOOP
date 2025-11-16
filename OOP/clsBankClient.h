
#pragma once

#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <string>
#include <fstream>
#include "clsUtil.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClinetObject(string Line, string Seperator = "#//#")
	{
		vector <string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stof(vClientData[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string stClientRecord = "";

		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.GetAccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsBankClient& C : vClients)
			{
				if (C.MarkedForDeleted() == false)
				{
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();

		}
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClinetObject(Line);
				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return vClients;
	}

	void _AddDataLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.GetAccountNumber() == GetAccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	string _PrepareTransferLogRegister(double Amount, clsBankClient& DestinationClient, string UserName, string Seperator = "#//#")
	{
		string stTransferLogRegister = "";

		stTransferLogRegister += clsDate::GetSystemDateTimeString() + Seperator;
		stTransferLogRegister += GetAccountNumber() + Seperator;
		stTransferLogRegister += DestinationClient.GetAccountNumber() + Seperator;
		stTransferLogRegister += to_string(Amount) + Seperator;
		stTransferLogRegister += to_string(GetAccountBalance()) + Seperator;
		stTransferLogRegister += to_string(DestinationClient.AccountBalance) + Seperator;
		stTransferLogRegister += UserName;

		return stTransferLogRegister;
	}

	void _RegisterTransferLog(double Amount, clsBankClient& DestinationClient, string UserName)
	{
		string stDataLine = _PrepareTransferLogRegister(Amount, DestinationClient, UserName);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	struct stTransferLogRecord;
	static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTransferLogRecord TransferRecord;

		vector <string> vTransferRecord = clsString::Split(Line, Seperator);

		TransferRecord.DateAndTime = vTransferRecord[0];
		TransferRecord.SourceAccountNumber = vTransferRecord[1];
		TransferRecord.DestinationAccountNumber = vTransferRecord[2];
		TransferRecord.Amount = stoi(vTransferRecord[3]);
		TransferRecord.SourceBalance = stoi(vTransferRecord[4]);
		TransferRecord.DestinationBalance = stoi(vTransferRecord[5]);
		TransferRecord.UserName = vTransferRecord[6];

		return TransferRecord;
	}

public:

	clsBankClient(enMode Mode	, string FirstName, string LastName,
		string Email,string Phone, string AccountNumber, string PinCode, float AccountBalance)
		:
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	struct stTransferLogRecord
	{
		string DateAndTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		double Amount;
		double SourceBalance;
		double DestinationBalance;
		string UserName;
	};

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	string GetAccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	static clsBankClient Find(string AccountNumber)
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClinetObject(Line);
				if (Client.GetAccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClinetObject(Line);
				if (Client.GetAccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
			
		return (!Client1.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExist = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if(IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;

				break;
			}
		}

		case enMode::UpdateMode:
		{
			_Update();

			return enSaveResults::svSucceeded;
			
			break;
		}

		case enMode::AddNewMode:
		{
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExist;
			}
			else
			{
				_AddNew();

				_Mode = enMode::UpdateMode;

				return enSaveResults::svSucceeded;
			}
		}

		}
	}

	 bool Delete()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.GetAccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
		*this = _GetEmptyClientObject();

		return true;
	}

	 static vector <clsBankClient> GetClientsList()
	 {
		 return _LoadClientsDataFromFile();
	 }

	 static double GetTotalBalances()
	 {
		 vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		 double TotalBalance = 0;

		 for (clsBankClient C : vClients)
		 {
			 TotalBalance += C.AccountBalance;
		 }

		 return TotalBalance;
	 }

	 void Deposit(double Amount)
	 {
		 _AccountBalance += Amount;
		 Save();
	 }

	 bool Withdraw(double Amount)
	 {
		 if (Amount > _AccountBalance)
		 {
			 return false;
		 }
		 else
		 {
			 _AccountBalance -= Amount;
			 Save();
			 return true;
		 }
	 }

	 bool Transfer(double Amount, clsBankClient& DestinationClient, string UserName)
	 {
		 if (Amount > AccountBalance)
		 {
			 return false;
		 }
		 else
		 {
			 Withdraw(Amount);
			 DestinationClient.Deposit(Amount);
			 _RegisterTransferLog(Amount, DestinationClient, UserName);
			 return true;
		 }
	 }

	 static vector <stTransferLogRecord> GetTransferLogList()
	 {
		 vector <stTransferLogRecord> vTransferLogRecord;

		 fstream MyFile;
		 MyFile.open("TransferLog.txt", ios::in);

		 if (MyFile.is_open())
		 {
			 string Line;

			 while (getline(MyFile, Line))
			 {
				 stTransferLogRecord TransferRecord = _ConvertTransferLogLineToRecord(Line);

				 vTransferLogRecord.push_back(TransferRecord);
			 }

			 MyFile.close();
		 }

		 return vTransferLogRecord;
	 }
};