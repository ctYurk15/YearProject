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

int main()
{
	//reading users
	const string way = "users.txt";
	vector<User> userList;
	Apps systemApp = Apps();
	systemApp.ReadUsers(userList, way);
	bool usingProgram = true;

	string login = " ", pass = " ";

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
					userList[userIndex].Disp(true); // for seeing your pass
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
					_numb = systemApp.getInput();
					cout << "Will you go or not(yes or no): ";
					while (boolString != "yes" && boolString != "no")
					{
						cin >> boolString;
					}
					if (boolString == "yes") _going = true;
					else _going = false;

					boolString = " ";
					
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
					userList[userIndex].SetLogin(userList, command);
				}
				else if (command == "/addUser") // adding user
				{
					if(userList[userIndex].isAdmin())systemApp.AddUser(userList);
					else cout << "You haven`t permisson for this action. " << endl;
				}
				else if (command == "/displayUsers") // display all users(if you`re admin, you`ll see their`s passwords)
				{
					systemApp.DispUsers(userList, userList[userIndex].isAdmin());
				}
				else if (command == "/deleteUser") // deleting user
				{
					if (userList[userIndex].isAdmin())
					{
						cout << "Log login of user: ";
						cin >> command;
						systemApp.DeleteUser(userList, command);
					}
					else cout << "You haven`t permisson for this action. " << endl;
				}
				else if (command == "/getUsersOfGroup")
				{
					cout << "Log group: ";
					cin >> command;
					systemApp.DisplayUsersFromGroup(userList, command, userList[userIndex].isAdmin());
				}
				else if(command == "/getUsersByLesson")
				{
					int numb = 0;
					cout << "Log number of lesson: ";
					numb = systemApp.getInput();
					if (numb >= 0 && numb <= 5)
					{
						systemApp.DisplayUsersByLesson(userList, numb, userList[userIndex].isAdmin());
					}
				}
				else if (command == "/getUserByLogin")
				{
					cout << "Log login: ";
					cin >> command;
					systemApp.GetUserByNickName(userList, command, userList[userIndex].isAdmin());
				}
				else if (command == "/sortByAvarageNumber")
				{
					systemApp.SortByNumber(userList);
				}
				else if (command == "/sortByNames")
				{
					systemApp.SortByName(userList);
				}
				else if (command == "/sortByGroups")
				{
					systemApp.SortByGroups(userList);
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
	
	systemApp.WriteUsers(userList, way);
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