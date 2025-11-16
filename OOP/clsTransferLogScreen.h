#pragma once

#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <fstream>

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:

    static void _PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferRecord)
    {
        cout << setw(8) << left << ""
            << "| " << setw(23) << left << TransferRecord.DateAndTime
            << "| " << setw(12) << left << TransferRecord.SourceAccountNumber
            << "| " << setw(12) << left << TransferRecord.DestinationAccountNumber
            << "| " << setw(12) << left << TransferRecord.Amount
            << "| " << setw(12) << left << TransferRecord.SourceBalance
            << "| " << setw(12) << left << TransferRecord.DestinationBalance
            << "| " << setw(12) << left << TransferRecord.UserName;
    }

public:

    static void ShowTransferLogListScreen()
    {
        vector <clsBankClient::stTransferLogRecord> vTransferRecord = clsBankClient::GetTransferLogList();

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t   (" + to_string(vTransferRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << ""
            << "\n\t_______________________________________________________________________________________________________________\n";

        cout << setw(8) << left << ""
            << "| " << left << setw(23) << "Date/Time"
            << "| " << left << setw(12) << "Src Acct"
            << "| " << left << setw(12) << "Dst Acct"
            << "| " << left << setw(12) << "Amount"
            << "| " << left << setw(12) << "Src Bal"
            << "| " << left << setw(12) << "Dst Bal"
            << "| " << left << setw(12) << "User"
            << endl;

        cout << setw(8) << left << ""
            << "_______________________________________________________________________________________________________________\n";

        if (vTransferRecord.empty())
        {
            cout << "\n\t\t\tNo Transfer Log Records Found!\n";
            return;
        }

        for (clsBankClient::stTransferLogRecord Tr : vTransferRecord)
        {
            _PrintTransferLogRecordLine(Tr);
            cout << endl;
        }

        cout << setw(8) << left << ""
            << "_______________________________________________________________________________________________________________\n";
    }
};
