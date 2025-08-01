#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";
void Login();
void ShowMainMenue();
void ShowTransactionsMenue();
void ShowManageUsersMenue();

enum enMainMenueOptions
{
	ShowClientList = 1, AddNewClient = 2, DeleteClient = 3, UpdateClientInfo = 4,
	FindClient = 5, Transactions = 6, ManageUsers = 7, Logout = 8
};

enum enTransactionsMenueOptions
{
	Deposit = 1, Withdraw = 2, TotalBalances = 3, MainMenue = 4
};

enum enManageUsersMenueOptions
{
	ListUsers = 1, AddNewUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, enMainMenue = 6
};

enum enMainMenuePermissions
{
	eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16,
	pTransactions = 32, pManageUsers = 64
};

struct stClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0.0;
	bool MarkForDelete = false;
};

struct stUser
{
	string Username = "";
	string Password = "";
	short Permissions = 0;
	bool MarkForDelete = false;
};

stUser CurrentUser;

short ReadMainMenueOption()
{
	short Number = 0;
	cout << "Choose what do you want to do? [1 to 8]? ";
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

short ReadManageUsersMenueOption()
{
	short Number = 0;
	cout << "Choose what do you want to do? [1 to 6]? ";
	cin >> Number;
	return Number;
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "Enter Account Number ? ";
	cin >> AccountNumber;
	return AccountNumber;
}

string ReadUserName()
{
	string UserName = "";
	cout << "Enter UserName ? ";
	cin >> UserName;
	return UserName;
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

stClient ConvertLineToClientRecord(string LineRecord, string Seperator = "#//#")
{
	stClient Client;

	vector <string> vClientData = SplitString(LineRecord, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

stUser ConvertUserLineToRecord(string LineRecord, string Seperator = "#//#")
{
	stUser User;

	vector <string> vUserData = SplitString(LineRecord, Seperator);

	User.Username = vUserData[0];
	User.Password = vUserData[1];
	User.Permissions = stoi(vUserData[2]);

	return User;
}

vector <stClient> LoadClientsDataFromFile(string FileName)
{
	vector <stClient> vClients;

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLineToClientRecord(Line);

			vClients.push_back(Client);
		}

		MyFile.close();
	}

	return vClients;
}

vector <stUser> LoadUsersDataFromFile(string FileName)
{
	vector <stUser> vUsers;

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stUser User;

		while (getline(MyFile, Line))
		{
			User = ConvertUserLineToRecord(Line);

			vUsers.push_back(User);
		}

		MyFile.close();
	}

	return vUsers;
}

void PrintClientCard(stClient& Client)
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

void PrintUserCard(stUser& User)
{
	cout << "\n\nThe following are the User Details :\n\n";

	cout << "--------------------------------------------\n";
	cout << "User Name   : " << User.Username << endl;
	cout << "Password    : " << User.Password << endl;
	cout << "Permissions : " << User.Permissions << endl;
	cout << "--------------------------------------------\n\n";
}

bool FindClientByAccountNumber(string AccountNumber, stClient& Client, vector <stClient>& vClients)
{
	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}

	return false;
}

bool FindUserByUsername(string UserName, stUser& User, vector <stUser>& vUsers)
{
	for (stUser& U : vUsers)
	{
		if (U.Username == UserName)
		{
			User = U;
			return true;
		}
	}

	return false;
}

string ConvertRecordToLine(stClient& BankClientData, string Seperator = "#//#")
{
	string sClientRecord = "";

	sClientRecord += BankClientData.AccountNumber + Seperator;
	sClientRecord += BankClientData.PinCode + Seperator;
	sClientRecord += BankClientData.Name + Seperator;
	sClientRecord += BankClientData.Phone + Seperator;
	sClientRecord += to_string(BankClientData.AccountBalance);

	return sClientRecord;
}

string ConvertRecordToLine(stUser& BankUserData, string Seperator = "#//#")
{
	string sUserRecord = "";

	sUserRecord += BankUserData.Username + Seperator;
	sUserRecord += BankUserData.Password + Seperator;
	sUserRecord += to_string(BankUserData.Permissions);

	return sUserRecord;
}

void SaveClientsDataToFile(string FileName, vector <stClient>& vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		string DataLine = "";

		for (stClient& C : vClients)
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

void SaveUsersDataToFile(string FileName, vector <stUser>& vUsers)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		string DataLine = "";

		for (stUser& U : vUsers)
		{
			if (U.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(U);

				MyFile << DataLine << endl;
			}
		}

		MyFile.close();
	}
}

void PrintClientRecord(stClient& Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintUserRecord(stUser& User)
{
	cout << "| " << setw(20) << left << User.Username;
	cout << "| " << setw(12) << left << User.Password;
	cout << "| " << setw(14) << left << User.Permissions;

}

void PrintClientRecordBalanceLine(stClient& Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void GoBackToMainMenue()
{
	cout << "\n\n\nPress any key to go back to Main Menue... ";
	system("pause>0");
	ShowMainMenue();
}

void GoBackToTransactionsMenue()
{
	cout << "\n\n\nPress any key to go back to Transactions Menue... ";
	system("pause>0");
	ShowTransactionsMenue();
}

void GoBackToManageUsersMenue()
{
	cout << "\n\n\nPress any key to go back to Manage Users Menue... ";
	system("pause>0");
	ShowManageUsersMenue();
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	vector <stClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line = "";
		stClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLineToClientRecord(Line);
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

bool UserExistsByUsername(string Username, string FileName)
{
	vector <stUser> vUsers;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line = "";
		stUser User;

		while (getline(MyFile, Line))
		{
			User = ConvertUserLineToRecord(Line);
			if (User.Username == Username)
			{
				MyFile.close();
				return true;
			}

			vUsers.push_back(User);
		}

		MyFile.close();
	}
	return false;
}

stClient ReadNewClient()
{
	stClient Client;

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

short ReadPermissionsToSet()
{
	short Permissions = 0;
	char Answer = 'N';

	cout << "\nDo you want to give full access ? Y/N? ";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
		return -1;

	cout << "\nDo you want to give access to :\n";

	cout << "\nShow Client List ? Y/N? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
		Permissions += enMainMenuePermissions::pListClients;

	cout << "\nAdd New Client ? Y/N? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
		Permissions += enMainMenuePermissions::pAddNewClient;

	cout << "\nDelete Client ? Y/N? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
		Permissions += enMainMenuePermissions::pDeleteClient;

	cout << "\nUpdate Client ? Y/N? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
		Permissions += enMainMenuePermissions::pUpdateClient;

	cout << "\nFind Client ? Y/N? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
		Permissions += enMainMenuePermissions::pFindClient;

	cout << "\nTransactions ? Y/N? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
		Permissions += enMainMenuePermissions::pTransactions;

	cout << "\nManage Users ? Y/N? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
		Permissions += enMainMenuePermissions::pManageUsers;

	return Permissions;

}

stUser ReadNewUser()
{
	stUser User;

	cout << "Enter Username ? ";
	getline(cin >> ws, User.Username);

	while (UserExistsByUsername(User.Username, UsersFileName))
	{
		cout << "User with [" << User.Username << "] already exists, Enter another Username? ";
		getline(cin >> ws, User.Username);
	}

	cout << "Enter Password ? ";
	getline(cin, User.Password);

	User.Permissions = ReadPermissionsToSet();

	return User;
}

void AddDataLineToFile(string FileName, string stDataLine)
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
	stClient Client = ReadNewClient();

	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddingNewUser()
{
	stUser User = ReadNewUser();

	AddDataLineToFile(UsersFileName, ConvertRecordToLine(User));
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

void AddNewUsers()
{
	char AddMore = 'Y';

	do
	{
		cout << "Adding New User :\n\n";

		AddingNewUser();

		cout << "\n\nUser Added Successfully, do you want to add more Users?  Y/N?\n";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}

	return false;
}

bool MarkUserForDeleteByUsername(string Username, vector <stUser>& vUsers)
{
	for (stUser& U : vUsers)
	{
		if (U.Username == Username)
		{
			U.MarkForDelete = true;
			return true;
		}
	}

	return false;
}

void DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
	stClient Client;
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

void DeleteUserByUsername(string Username, vector <stUser>& vUsers)
{
	stUser User;
	char Answer = 'n';

	if (Username == "Admin")
	{
		cout << "\n\nYou cannot Delete This User.\n";
	}
	else if (FindUserByUsername(Username, User, vUsers))
	{
		PrintUserCard(User);

		cout << "\n\nAre you sure you want delete this User ?  Y/N? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			MarkUserForDeleteByUsername(Username, vUsers);
			SaveUsersDataToFile(UsersFileName, vUsers);

			vUsers = LoadUsersDataFromFile(UsersFileName);
			cout << "\n\nUser Deleted Successfully.\n";
		}
	}
	else
	{
		cout << "\nUser with User Name (" << Username << ") Not Found!\n";
	}
}

stClient ChangeClientRecord(string AccountNumber)
{
	stClient Client;

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

stUser ChangeUserRecord(string Username)
{
	stUser User;

	User.Username = Username;

	cout << "\n\nEnter Password ? ";
	getline(cin >> ws, User.Password);

	User.Permissions = ReadPermissionsToSet();

	return User;
}

void UpdateClientByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
	stClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want update this Client ?  Y/N? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			for (stClient& C : vClients)
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

void UpdateUserByUsername(string Username, vector <stUser>& vUsers)
{
	stUser User;
	char Answer = 'n';

	if (Username == "Admin")
	{
		cout << "\n\nYou cannot Update This User.\n";
	}
	else if (FindUserByUsername(Username, User, vUsers))
	{
		PrintUserCard(User);

		cout << "\n\nAre you sure you want update this User ?  Y/N? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			for (stUser& U : vUsers)
			{
				if (U.Username == Username)
				{
					U = ChangeUserRecord(Username);
					break;
				}
			}

			SaveUsersDataToFile(UsersFileName, vUsers);

			cout << "\n\nUser Updated Successfully.\n";
		}
	}
	else
	{
		cout << "\nUser with User Name (" << Username << ") Not Found!\n";
	}
}

bool CheckAccessPermission(enMainMenuePermissions Permission)
{
	if (CurrentUser.Permissions == enMainMenuePermissions::eAll)
		return true;

	if ((Permission & CurrentUser.Permissions) == Permission)
		return true;
	else
		return false;
}

void ShowAccessDeniedMessage()
{
	system("cls");

	cout << "\n--------------------------------------";
	cout << "\nAccess Denied,";
	cout << "\nYou dont Have Permissions To Do this,";
	cout << "\nPlease Contact Your Admin.";
	cout << "\n--------------------------------------";
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <stClient>& vClients)
{
	char Answer = 'n';

	cout << "\n\nAre you sure you want perform this Transaction ?  Y/N? ";
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		for (stClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveClientsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully. New Balance is : " << C.AccountBalance << endl;;
				return true;
			}
		}

		return false;
	}
}

void ShowDepositScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tDeposit Screen\n";
	cout << "-------------------------------------\n\n";

	stClient Client;
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		cout << "\nClient with [" << AccountNumber << "] Does Not Exist!\n\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0;
	cout << "\nPlease enter deposit amount ? ";
	cin >> Amount;

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithdrawScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tWithdraw Screen\n";
	cout << "-------------------------------------\n\n";

	stClient Client;
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, Client, vClients))
	{
		cout << "\nClient with [" << AccountNumber << "] Does Not Exist!\n\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0;
	cout << "\nPlease enter withdraw amount ? ";
	cin >> Amount;

	while (Amount > Client.AccountBalance)
	{
		cout << "\n\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance;
		cout << "\nPlease enter another amount ? ";
		cin >> Amount;
	}

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void ShowTotalBalancesScreen()
{
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t Balances List (" << vClients.size() << ") Client(s).\n";
	cout << "____________________________________________________________________________________";
	cout << "____________\n\n";

	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Balance";

	cout << "\n____________________________________________________________________________________";
	cout << "____________\n\n";

	double TotalBalances = 0;

	if (vClients.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available in the System!";
	}
	else
	{
		for (stClient& Client : vClients)
		{
			PrintClientRecordBalanceLine(Client);
			TotalBalances += Client.AccountBalance;
			cout << endl;
		}
	}

	cout << "\n____________________________________________________________________________________";
	cout << "____________\n\n";

	cout << "\t\t\t\t Total Balances = " << TotalBalances << endl << endl;
}

void PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
{
	switch (TransactionsMenueOption)
	{
	case enTransactionsMenueOptions::Deposit:
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMenue();
		break;

	case enTransactionsMenueOptions::Withdraw:
		system("cls");
		ShowWithdrawScreen();
		GoBackToTransactionsMenue();
		break;

	case enTransactionsMenueOptions::TotalBalances:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionsMenue();
		break;

	case enTransactionsMenueOptions::MainMenue:
		system("cls");
		ShowMainMenue();
		break;
	}
}

void ShowAllUsersScreen()
{
	vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

	cout << "\n\t\t\t\t Users List (" << vUsers.size() << ") User(s).\n";
	cout << "____________________________________________________________________________________";
	cout << "____________\n\n";

	cout << "| " << setw(20) << left << "User Name";
	cout << "| " << setw(12) << left << "Password";
	cout << "| " << setw(14) << left << "Permissions";

	cout << "\n____________________________________________________________________________________";
	cout << "____________\n\n";

	if (vUsers.size() == 0)
		cout << "\t\t\t\tNo Users Available In the System!";
	else
		for (stUser& User : vUsers)
		{
			PrintUserRecord(User);

			cout << endl;
		}

	cout << "\n____________________________________________________________________________________";
	cout << "____________\n\n";
}

void ShowAddNewUsersScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tAdd New Users Screen\n";
	cout << "-------------------------------------\n\n";

	AddNewUsers();
}

void ShowDeleteUserScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tDelete User Screen\n";
	cout << "-------------------------------------\n\n";

	vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string UserName = ReadUserName();
	DeleteUserByUsername(UserName, vUsers);
}

void ShowUpdateUserScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tUpdate User Screen\n";
	cout << "-------------------------------------\n\n";

	vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string Username = ReadUserName();
	UpdateUserByUsername(Username, vUsers);
}

void ShowFindUserScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tFind User Screen\n";
	cout << "-------------------------------------\n\n";

	vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
	string Username = ReadUserName();
	stUser User;

	if (FindUserByUsername(Username, User, vUsers))
	{
		PrintUserCard(User);
	}
	else
	{
		cout << "\nUser with User Name [" << Username << "] is not found!";
	}
}

void PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
{
	switch (ManageUsersMenueOption)
	{
	case enManageUsersMenueOptions::ListUsers:
		system("cls");
		ShowAllUsersScreen();
		GoBackToManageUsersMenue();
		break;

	case enManageUsersMenueOptions::AddNewUser:
		system("cls");
		ShowAddNewUsersScreen();
		GoBackToManageUsersMenue();
		break;

	case enManageUsersMenueOptions::DeleteUser:
		system("cls");
		ShowDeleteUserScreen();
		GoBackToManageUsersMenue();
		break;

	case enManageUsersMenueOptions::UpdateUser:
		system("cls");
		ShowUpdateUserScreen();
		GoBackToManageUsersMenue();
		break;

	case enManageUsersMenueOptions::FindUser:
		system("cls");
		ShowFindUserScreen();
		GoBackToManageUsersMenue();
		break;

	case enManageUsersMenueOptions::enMainMenue:
		system("cls");
		ShowMainMenue();
		break;
	}
}

void ShowAllClientsScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pListClients))
	{
		ShowAccessDeniedMessage();
		return;
	}

	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

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
		for (stClient& Client : vClients)
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
	if (!CheckAccessPermission(enMainMenuePermissions::pAddNewClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n-------------------------------------\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "-------------------------------------\n\n";

	AddNewClients();
}

void ShowDeleteClientScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n-------------------------------------\n";
	cout << "\tDelete Client Screen\n";
	cout << "-------------------------------------\n\n";

	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n-------------------------------------\n";
	cout << "\tUpdate Client Screen\n";
	cout << "-------------------------------------\n\n";

	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pFindClient))
	{
		ShowAccessDeniedMessage();
		return;
	}

	cout << "\n-------------------------------------\n";
	cout << "\tFind Client Screen\n";
	cout << "-------------------------------------\n\n";

	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	stClient Client;

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
	if (!CheckAccessPermission(enMainMenuePermissions::pTransactions))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
		return;
	}

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

void ShowManageUsersMenue()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pManageUsers))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
		return;
	}

	system("cls");

	cout << "=============================================\n";
	cout << "\t\tManage Users Menue Screen\n";
	cout << "=============================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "=============================================\n";

	PerformManageUsersMenueOption(enManageUsersMenueOptions(ReadManageUsersMenueOption()));
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
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::AddNewClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::DeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::UpdateClientInfo:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::FindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::Transactions:
		system("cls");
		ShowTransactionsMenue();
		break;

	case enMainMenueOptions::ManageUsers:
		system("cls");
		ShowManageUsersMenue();
		break;

	case enMainMenueOptions::Logout:
		system("cls");
		// ShowEndScreen();
		Login();
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
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "=============================================\n";

	PerformMainMenueOption(enMainMenueOptions(ReadMainMenueOption()));
}

bool FindUserByUsernameAndPassword(string Username, string Password, stUser& CurrentUser)
{
	vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

	for (stUser U : vUsers)
	{
		if (U.Username == Username && U.Password == Password)
		{
			CurrentUser = U;
			return true;
		}
	}

	return false;
}

bool LoadUserInfo(string Username, string Password)
{
	if (FindUserByUsernameAndPassword(Username, Password, CurrentUser))
		return true;
	else
		return false;
}

void Login()
{
	bool LoginFailed = false;
	string Username, Password;

	do
	{
		system("cls");

		cout << "=============================================\n";
		cout << "\t\tLogin Screen\n";
		cout << "=============================================\n";

		if (LoginFailed)
		{
			cout << "Invalid Username/Password!\n";
		}

		cout << "Enter Username ? ";
		cin >> Username;

		cout << "Enter Password ? ";
		cin >> Password;

		LoginFailed = !LoadUserInfo(Username, Password);

	} while (LoginFailed);

	ShowMainMenue();
}

int main()
{
	Login();

	system("pause>0");
	return 0;
}