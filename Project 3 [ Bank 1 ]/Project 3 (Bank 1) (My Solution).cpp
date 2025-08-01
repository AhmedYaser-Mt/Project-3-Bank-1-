#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cctype>
using namespace std;

const string ClientsFileName = "Clients.txt";

enum enUserChoice {
	ShowClientList = 1, AddNewClient = 2, DeleteClient = 3, UpdateClientInfo = 4,
	FindClient = 5, Exit = 6
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

enUserChoice ReadUserChoice()
{
	short Number = 0;
	cin >> Number;
	return enUserChoice(Number);
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

void ShowMainMenueScreen()
{
	system("cls");
	cout << "=================================================\n";
	cout << "               Main Menue Screen\n";
	cout << "=================================================\n";
	cout << "          [1] Show Client List.\n";
	cout << "          [2] Add New Client.\n";
	cout << "          [3] Delete Client.\n";
	cout << "          [4] Update Client Info.\n";
	cout << "          [5] Find Client.\n";
	cout << "          [6] Exit.\n";
	cout << "=================================================\n";
	cout << "Choose what do you want to do? [1 to 6]? ";
}

void ShowEndScreen()
{
	system("cls");

	cout << "\n------------------------------------------\n";
	cout << "            Program Ends :-)\n";
	cout << "------------------------------------------\n\n";
}

void PrintClientRecord(sClient& Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector <sClient>& vClients)
{
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

	for (sClient& Client : vClients)
	{
		PrintClientRecord(Client);

		cout << endl;
	}

	cout << "\n____________________________________________________________________________________";
	cout << "____________\n\n";
}

void ShowBackToMenueMessage()
{
	cout << "\n\n\nPress any key to go back to Main Menue... ";
	system("pause>0");
}

string GetUserChoiceText(enUserChoice UserChoice)
{
	string arr[] = { "ShowClientList", "AddNewClient", "DeleteClient", "UpdateClientInfo", "FindClient", "Exit" };

	return arr[UserChoice - 1];
}

void ShowHeaderScreen(string Message)
{
	system("cls");

	cout << "\n------------------------------------------\n";
	cout << "           " << Message << " Screen\n";
	cout << "------------------------------------------\n\n";
}

bool IsAccountNumberExist(string AccountNumber)
{
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			return true;
		}
	}

	return false;
}

void ReadAndValidateAccountNumber(sClient& Client)
{
	cout << "Enter Account Number ? ";
	getline(cin >> ws, Client.AccountNumber);

	while (IsAccountNumberExist(Client.AccountNumber))
	{
		cout << "Client with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin, Client.AccountNumber);
	}
}

sClient ReadNewClient()
{
	sClient Client;

	ReadAndValidateAccountNumber(Client);

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

void AddClients()
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

void UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want update this Client ?  Y/N? ";
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

void StartBankProgram()
{
	enUserChoice UserChoice;

	do
	{
		ShowMainMenueScreen();

		UserChoice = ReadUserChoice();

		vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

		switch (UserChoice)
		{
		case enUserChoice::ShowClientList:
			system("cls");
			PrintAllClientsData(vClients);
			ShowBackToMenueMessage();
			break;

		case enUserChoice::AddNewClient:
			ShowHeaderScreen("Add New Client");
			AddClients();
			ShowBackToMenueMessage();
			break;

		case enUserChoice::DeleteClient:
			ShowHeaderScreen("Delete Client");
			DeleteClientByAccountNumber(ReadClientAccountNumber(), vClients);
			ShowBackToMenueMessage();
			break;

		case enUserChoice::UpdateClientInfo:
			ShowHeaderScreen("Update Client Info");
			UpdateClientByAccountNumber(ReadClientAccountNumber(), vClients);
			ShowBackToMenueMessage();
			break;

		case enUserChoice::FindClient:
			ShowHeaderScreen("Find Client");
			SearchClientByAccountNumber(ReadClientAccountNumber(), vClients);
			ShowBackToMenueMessage();
			break;

		case enUserChoice::Exit:
			break;
		}
	} while (UserChoice != enUserChoice::Exit);

	ShowEndScreen();
}

int main()
{
	StartBankProgram();

	return 0;
}