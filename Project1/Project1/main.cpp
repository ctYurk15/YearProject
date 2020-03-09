#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

//own libraries
#include "User.h"
#include "Apps.h"
#include "Lessons.h"

using namespace std;

//string nameLessons[5] = { "Math", "Science", "Programming", "English", "DataBase" };

void ReadUsers(vector<User> &users, string way)
{
	ifstream fin;
	fin.open(way);

	//fortime vals
	int size = 0;
	string login = " ", name = " ", surname = " ", fatherName = " ", pass = " ", group = " ";
	float avarageNumber = 0;
	bool admin = false;
	bool lessons[5] = { false, false, false, false, false };

	fin >> size;
	for (int i = 0; i < size; i++)
	{
		fin >> login >> name >> surname >> fatherName >> pass >> group >> avarageNumber;
		for (int i = 0; i < 5; i++)
		{
			fin >> lessons[i];
			if (lessons[i]) studentsToLessons[i]++;
		}
		fin >> admin;
		users.push_back(User(login, name, surname, fatherName, pass, group, avarageNumber, lessons, admin));
	}

	for (int i = 0; i < 5; i++)
	{
		cout << studentsToLessons[i] << endl;
	}

	fin.close();
}

void WriteUsers(vector<User> users, string way)
{
	ofstream fout;
	fout.open(way);

	fout << users.size() << endl; // writing size

	for (int i = 0; i < users.size(); i++)
	{
		fout << users[i].GetLogin() << " "; // writing login
		
		for (int j = 0; j < 3; j++) //writing name
		{
			fout << users[i].GetName(j) << " ";
		}

		fout << users[i].GetPass() << " " << users[i].GetGroup() << " "; // writing password and group

		fout << users[i].getAvarageNumber() << " "; // writing avarage number

		for (int j = 0; j < 5; j++) // writing lessons
		{
			fout << users[i].getLesson(j) << " ";
		}

		fout << users[i].isAdmin() << endl;
	}

	fout.close();
}

void AddUser(vector<User> &users)
{
	//temporary vars
	string login = " ";
	string name = " ";
	string surname = " ";
	string fatherName = " ";
	string pass = " ";
	string group = " ";
	float avarageNumber = 0;
	bool goingLessons[5];
	bool admin = false;

	//helpful vars
	

	//process of adding
	cout << "Login: ";
	cin >> login;
	cout << "Log name, surname and fathername: ";
	cin >> name >> surname >> fatherName;
	cout << "Password: ";
	cin >> pass;
	cout << "Group: ";
	cin >> group;
	cout << "Avarage number: ";
	cin >> avarageNumber;
	for (int i = 0; i < 5; i++)
	{
		string boolString = " ";
		
		while (boolString != "yes" && boolString != "no")
		{
			cout << users[0].nameLessons[i] << "(yes or no): ";
			cin >> boolString;
		}

		if (boolString == "yes") goingLessons[i] = true;
		else goingLessons[i] = false;
	}

	
	string boolString = " ";

	while (boolString != "yes" && boolString != "no")
	{
		cout << "Admin(yes or no): ";
		cin >> boolString;
	}

	if (boolString == "yes") admin = true;
	else admin = false;

	//confirmation
	boolString = " ";

	while (boolString != "yes" && boolString != "no")
	{
		cout << "Are you sure(yes or no): ";
		cin >> boolString;
	}

	if (boolString == "yes") users.push_back(User(login, name, surname, fatherName, pass, group, avarageNumber, goingLessons, admin));

}

int main()
{
	//reading users
	string way = "users.txt";
	vector<User> userList;
	ReadUsers(userList, way);
	bool usingProgram = true;

	string login = " ", pass = " ";

	Apps systemApp = Apps();

	while (usingProgram)
	{
		cout << "Lessons v0.1\n";
		cout << "Login: ";
		cin >> login;

		bool foundUser = false;
		int userIndex = 0;

		//searching for the user with login
		for (int i = 0; i < userList.size(); i++)
		{
			if (userList[i].GetLogin() == login)
			{
				userIndex = i;
				foundUser = true;
				break;
			}
		}

		if (foundUser)
		{
			//authorising
			bool authorising = true;
			bool usingProfile = true;
			while (authorising)
			{
				cout << "Password: ";
				cin >> pass;
				if (userList[userIndex].GetPass() == pass)
				{
					break;
				}
				else
				{
					cout << "No" << endl;
				}
			}
			
			//using profile
			while (usingProfile)
			{
				string command = " ";
				string boolString = " ";
				cout << "->";
				cin >> command;

				//commands
				if (command == "/exit")     //exit
				{
					usingProgram = false;
					usingProfile = false;
				}
				else if (command == "/switchProfile") // change profile
				{
					usingProfile = false;
				}
				else if (command == "/profile") // look at your profile
				{
					userList[userIndex].Disp(userList[userIndex].isAdmin());
				}
				else if (command == "/info") // info
				{
					systemApp.Commands(userList[userIndex].isAdmin());
				}
				else if (command == "/setLesson") // change going to lessons
				{
					int _numb = 0;
					bool _going = false;
					cout << "Log number of lesson: ";
					cin >> _numb;
					cout << "Will you go or not(yes or no): ";
					while (boolString != "yes" && boolString != "no")
					{
						cin >> boolString;
					}
					if (boolString == "yes") _going = true;
					
					//confimation
					while (boolString != "yes" && boolString != "no")
					{
						cout << "Are you sure(yes or no): ";
						cin >> boolString;
					}
					if (boolString == "yes") userList[userIndex].SetLesson(_numb, _going);
					
				}
				else if (command == "/changeLogin") // change your login
				{
					cout << "Log your new login: ";
					cin >> command;
					cout << "Do you realy whant to change your login(type yes, if yes): ";
					cin >> boolString;
					if (boolString == "yes")
					{
						userList[userIndex].SetLogin(command);
					}
				}
				else if (command == "/addUser") // adding user
				{
					if(userList[userIndex].isAdmin())AddUser(userList);
					else cout << "You haven`t permisson for this action. " << endl;
				}
				else if (command == "/displayUsers") // display all users(if you`re admin, you`ll see their`s passwords)
				{
					for (int i = 0; i < userList.size(); i++)
					{
						userList[i].Disp(userList[userIndex].isAdmin());
						cout << endl;
					}
				}
				else if (command == "/deleteUser") // deleting user
				{
					if (userList[userIndex].isAdmin())
					{
						int index = 0;
						while (true)
						{
							cout << "Log number: ";
							cin >> index;
							if (index >= 0 && index <= userList.size()) break;
							cout << "Incorrect number" << endl;
						}
						
						vector<User>::iterator it = userList.begin();
						for (int i = 0; i < index; i++)
						{
							it++;
						}

						//confirmation
						boolString = " ";
						while (boolString != "yes" && boolString != "no")
						{
							cout << "Are you sure(yes or no): ";
							cin >> boolString;
						}
						if(boolString == "yes") userList.erase(it);
					}
					else cout << "You haven`t permisson for this action. " << endl;
				}
				else
				{
					cout << "What? Use /info to get commands list" << endl;
				}
			}
		}

		else
		{
			cout << "We haven`t user with this login." << endl;
		}
	}
	
	WriteUsers(userList, way);
	system("pause");
	return 0;
}

/*#pragma warning(disable:4996)
/*int main() {
	FILE* f = fopen("bitch.bin", "w");

	char* buffer = (char*)malloc(8192);

	for (int i=0;; i++) {
		fwrite(buffer, 1, 2048, f);
	}
	
	system("pause");
	return 0;
}*/