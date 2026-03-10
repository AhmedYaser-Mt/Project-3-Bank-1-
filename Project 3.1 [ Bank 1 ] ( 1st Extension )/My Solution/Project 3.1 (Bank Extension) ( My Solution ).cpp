#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cctype>
using namespace std;

const string ClientsFileName = "Clients.txt";
void ShowMainMenue();
void ShowTransactionsMenue();

enum enMainMenueOptions
{
	ShowClientList = 1, AddNewClient = 2, DeleteClient = 3, UpdateClientInfo = 4,
	FindClient = 5, Transactions = 6, Exit = 7
};

enum enTransactionsMenueOptions
{
	Deposit = 1, Withdraw = 2, TotalBalances = 3, MainMenue = 4
};

struct sClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0.0;
	bool MarkForDelete = false;
};

short ReadMainMenueOption()
{
	short Number = 0;
	cout << "Choose what do you want to do? [1 to 7]? ";
	cin >> Number;
	return Number;
}

short ReadTransactionsMenueOption()
{
	short Number = 0;
	cout << "Choose what do you want to do? [1 to 4]? ";
	cin >> Number;
	return Number;
}

double ReadDepositAmount()
{
	double Number = 0;
	cout << "Enter Deposit Amount ? ";
	cin >> Number;
	return Number;
}

double ReadWithdrawAmount(sClient& Client)
{
	double Number = 0;
	cout << "Enter Withdraw Amount ? ";
	cin >> Number;

	while (Number > Client.AccountBalance)
	{
		cout << "\n\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance;
		cout << "\nPlease enter another amount ? ";
		cin >> Number;
	}
	return Number;
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "Enter Account Number ? ";
	cin >> AccountNumber;
	return AccountNumber;
}

vector <string> SplitString(string S1, string delim)
{
	short pos = 0;
	string sWord = "";
	vector <string> vString;

	while ((pos = S1.find(delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}

		S1.erase(0, pos + delim.length());
	}

	if (S1 != "")
	{
		vString.push_back(S1);
	}

	return vString;
}

sClient ConvertLineToRecord(string LineRecord, string Seperator = "#//#")
{
	sClient Client;

	vector <string> vClientData = SplitString(LineRecord, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

vector <sClient> LoadClientsDataFromFile(string FileName)
{
	vector <sClient> vClients;

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);

			vClients.push_back(Client);
		}

		MyFile.close();
	}

	return vClients;
}

void PrintClientCard(sClient& Client)
{
	cout << "\n\nThe following are the Client Details :\n\n";

	cout << "--------------------------------------------\n";
	cout << "AccountNumber  : " << Client.AccountNumber << endl;
	cout << "PinCode        : " << Client.PinCode << endl;
	cout << "Name           : " << Client.Name << endl;
	cout << "Phone          : " << Client.Phone << endl;
	cout << "AccountBalance : " << Client.AccountBalance << endl;
	cout << "--------------------------------------------\n\n";
}

bool FindClientByAccountNumber(string AccountNumber, sClient& Client, vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}

	return false;
}

string ConvertRecordToLine(sClient& BankClientData, string Seperator = "#//#")
{
	string sClientRecord = "";

	sClientRecord += BankClientData.AccountNumber + Seperator;
	sClientRecord += BankClientData.PinCode + Seperator;
	sClientRecord += BankClientData.Name + Seperator;
	sClientRecord += BankClientData.Phone + Seperator;
	sClientRecord += to_string(BankClientData.AccountBalance);

	return sClientRecord;
}

void SaveClientsDataToFile(string FileName, vector <sClient>& vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		string DataLine = "";

		for (sClient& C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);

				MyFile << DataLine << endl;
			}
		}

		MyFile.close();
	}
}

void PrintClientRecord(sClient& Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintClientBalance(sClient& Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void GoBackToMainMenueScreen()
{
	cout << "\n\n\nPress any key to go back to Main Menue... ";
	system("pause>0");
	ShowMainMenue();
}

void GoBackToTransactionsMenueScreen()
{
	cout << "\n\n\nPress any key to go back to Transactions Menue... ";
	system("pause>0");
	ShowTransactionsMenue();
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line = "";
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}

			vClients.push_back(Client);
		}

		MyFile.close();
	}
	return false;
}

sClient ReadNewClient()
{
	sClient Client;

	cout << "Enter Account Number ? ";
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "Client with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter PIN Code ? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name ? ";
	getline(cin, Client.Name);

	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;

	return Client;
}

void AddClientToFile(string FileName, string stDataLine)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;

		MyFile.close();
	}
}

void AddingNewClient()
{
	sClient Client = ReadNewClient();

	AddClientToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
	char AddMore = 'Y';

	do
	{
		cout << "Adding New Client :\n\n";

		AddingNewClient();

		cout << "\n\nClient Added Successfully, do you want to add more Clients?  Y/N?\n";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}

	return false;
}

void DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want delete this Client ?  Y/N? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsDataToFile(ClientsFileName, vClients);

			vClients = LoadClientsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.\n";
		}
	}
	else
	{
		cout << "\nClient with Account (" << AccountNumber << ") Not Found!\n";
	}
}

sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "\n\nEnter PIN Code ? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name ? ";
	getline(cin, Client.Name);

	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;

	return Client;
}

void DepositMoney(double DepositBalance, sClient& Client)
{
	Client.AccountBalance += DepositBalance;
}

void WithdrawMoney(double WithdrawBalance, sClient& Client)
{
	Client.AccountBalance -= WithdrawBalance;
}

void UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want delete this Client ?  Y/N? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}

			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "\n\nClient Updated Successfully.\n";
		}
	}
	else
	{
		cout << "\nClient with Account (" << AccountNumber << ") Not Found!\n";
	}
}

void SearchClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "\nClient with Account (" << AccountNumber << ") Not Found!\n";
	}
}

int CalculateTotalBalances(vector <sClient>& vClients)
{
	int TotalBalances = 0;

	for (sClient& C : vClients)
	{
		TotalBalances += C.AccountBalance;
	}

	return TotalBalances;
}

void DepositMoneyByAccountNumber(vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		cout << "\nClient with [" << AccountNumber << "] Does Not Exist!\n\n";
		AccountNumber = ReadClientAccountNumber();
	}

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client);

		double DepositAmount = ReadDepositAmount();

		cout << "\n\nAre you sure you want perform this Transaction ?  Y/N? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					DepositMoney(DepositAmount, C);
					cout << "\n\nDone Successfully.\n";
					cout << "New Balance = " << C.AccountBalance << endl;
					break;
				}
			}

			SaveClientsDataToFile(ClientsFileName, vClients);
		}
	}
}

void WithdrawMoneyByAccountNumber(vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		cout << "\nClient with [" << AccountNumber << "] Does Not Exist!\n\n";
		AccountNumber = ReadClientAccountNumber();
	}

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client);

		double WithdrawAmount = ReadWithdrawAmount(Client);

		cout << "\n\nAre you sure you want perform this Transaction ?  Y/N? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					WithdrawMoney(WithdrawAmount, C);
					cout << "\n\nDone Successfully.\n";
					cout << "New Balance = " << C.AccountBalance << endl;
					break;
				}
			}

			SaveClientsDataToFile(ClientsFileName, vClients);
		}
	}
}

void ShowDepositScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tDeposit Screen\n";
	cout << "-------------------------------------\n\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	DepositMoneyByAccountNumber(vClients);
}

void ShowWithdrawScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tWithdraw Screen\n";
	cout << "-------------------------------------\n\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	WithdrawMoneyByAccountNumber(vClients);
}

void ShowTotalBalancesScreen()
{
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t Balances List (" << vClients.size() << ") Client(s).\n";
	cout << "____________________________________________________________________________________";
	cout << "____________\n\n";

	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Balance";

	cout << "\n____________________________________________________________________________________";
	cout << "____________\n\n";

	if (vClients.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available in the System!";
	}
	else
	{
		for (sClient& Client : vClients)
		{
			PrintClientBalance(Client);

			cout << endl;
		}
	}

	cout << "\n____________________________________________________________________________________";
	cout << "____________\n\n";

	cout << "\t\t\t\t Total Balances = " << CalculateTotalBalances(vClients) << endl << endl;
}

void PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOptions)
{
	switch (TransactionsMenueOptions)
	{
	case enTransactionsMenueOptions::Deposit:
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMenueScreen();
		break;

	case enTransactionsMenueOptions::Withdraw:
		system("cls");
		ShowWithdrawScreen();
		GoBackToTransactionsMenueScreen();
		break;

	case enTransactionsMenueOptions::TotalBalances:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionsMenueScreen();
		break;

	case enTransactionsMenueOptions::MainMenue:
		system("cls");
		ShowMainMenue();
		break;
	}
}

void ShowAllClientsScreen()
{
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t Client List (" << vClients.size() << ") Client(s).\n";
	cout << "____________________________________________________________________________________";
	cout << "____________\n\n";

	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(10) << left << "PIN Code";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Phone";
	cout << "| " << setw(12) << left << "Balance";

	cout << "\n____________________________________________________________________________________";
	cout << "____________\n\n";

	if (vClients.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available in the System!";
	}
	else
	{
		for (sClient& Client : vClients)
		{
			PrintClientRecord(Client);

			cout << endl;
		}
	}

	cout << "\n____________________________________________________________________________________";
	cout << "____________\n\n";
}

void ShowAddNewClientsScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "-------------------------------------\n\n";

	AddNewClients();
}

void ShowDeleteClientScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tDelete Client Screen\n";
	cout << "-------------------------------------\n\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tUpdate Client Screen\n";
	cout << "-------------------------------------\n\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tFind Client Screen\n";
	cout << "-------------------------------------\n\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	sClient Client;

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
	}
}

void ShowTransactionsMenue()
{
	system("cls");

	cout << "=============================================\n";
	cout << "\t Transactions Menue Screen\n";
	cout << "=============================================\n";
	cout << "\t[1] Deposite.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "=============================================\n";

	PerformTransactionsMenueOption(enTransactionsMenueOptions(ReadTransactionsMenueOption()));
}

void ShowEndScreen()
{
	cout << "\n--------------------------------------\n";
	cout << "\tProgram Ends :-)\n";
	cout << "--------------------------------------\n\n";
}

void PerformMainMenueOption(enMainMenueOptions MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenueOptions::ShowClientList:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenueScreen();
		break;

	case enMainMenueOptions::AddNewClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenueScreen();
		break;

	case enMainMenueOptions::DeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenueScreen();
		break;

	case enMainMenueOptions::UpdateClientInfo:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenueScreen();
		break;

	case enMainMenueOptions::FindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenueScreen();
		break;

	case enMainMenueOptions::Transactions:
		system("cls");
		ShowTransactionsMenue();
		break;

	case enMainMenueOptions::Exit:
		system("cls");
		ShowEndScreen();
		break;
	}
}

void ShowMainMenue()
{
	system("cls");

	cout << "=============================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "=============================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << "=============================================\n";

	PerformMainMenueOption(enMainMenueOptions(ReadMainMenueOption()));
}

int main()
{
	ShowMainMenue();
	system("pause>0");

	return 0;
}