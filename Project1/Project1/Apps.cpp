#include "Apps.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "User.h";
#include "Lessons.h"

using namespace std;


Apps::Apps()
{
}

void Apps::Commands(bool isAdmin)
{
	cout << "/profile - get info about your profile" << endl;
	cout << "/switchProfile - change your profile" << endl;
	cout << "/changeLogin - change your login" << endl;
	cout << "/addUser - add new user(only for admins)" << endl;
	cout << "/deleteUser - delete some user(only for admins)" << endl;
	cout << "/displayUsers - display all user(admins can see passwords)" << endl;
	cout << "/getUsersOfGroup - display all users from some group" << endl;
	cout << "/getUsersByLesson - display all users from some lesson" << endl;
	cout << "/getUsersByLogin - seek user with some login" << endl;
	cout << "/sortByAvarageNumber - sort users from smaller to greater avarage number" << endl;
	cout << "/exit - leave the programm" << endl;
}

void Apps::DispUsers(vector<User> users, bool admin)
{
	for (int i = 0; i < users.size(); i++)
	{
		users[i].Disp(admin);
		cout << endl;
	}
}

void Apps::ReadUsers(vector<User>& users, string way)
{
	ifstream fin;
	fin.open(way);

	//fortime vals
	int size = 0;
	string login = " ", name = " ", surname = " ", fatherName = " ", pass = " ", group = " ";
	float avarageNumber = 0;
	bool admin = false;
	bool lessons[5] = { false, false, false, false, false };

	std::vector<string>::iterator it;

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
		
		if (find(groups.begin(), groups.end(), group) == groups.end()) // if group isn`t pushed now
		{
			groups.push_back(group);
		} 

	}

	fin.close();
}

void Apps::WriteUsers(vector<User> users, string way)
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

void Apps::AddUser(vector<User>& users)
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
			cout << nameLessons[i] << "(yes or no): ";
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

void Apps::DeleteUser(vector<User>& userList)
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
	string boolString = " ";
	while (boolString != "yes" && boolString != "no")
	{
		cout << "Are you sure(yes or no): ";
		cin >> boolString;
	}
	if (boolString == "yes") userList.erase(it);
}

void Apps::DisplayUsersFromGroup(vector<User> users, string group, bool admin)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].GetGroup() == group)
		{
			users[i].Disp(admin);
		}
	}
}

void Apps::DisplayUsersByLesson(vector<User> users, int lesson, bool admin)
{
	if (studentsToLessons[lesson] <= 15) // if enought place for all
	{
		cout << "Users for lesson " << nameLessons[lesson] << ":" << endl;
		//displaying
		for (int i = 0; i < users.size(); i++)
		{
			if (users[i].getLesson(lesson))
			{
				users[i].Disp(admin);
				cout << endl;
			}

		}
	}
	else // if students more then 15
	{
		cout << "15 best users for " << nameLessons[lesson] << ":\n";
		SortByNumber(users);

		int i = 0;
		
		for (int j = users.size() - 1; j >= 0 && i < 15; j--)
		{
			if (users[j].getLesson(lesson))
			{
				users[j].Disp(admin);
				cout << endl;
				i++;
			}
		}

	}

	

	

	cout << "Total: " << studentsToLessons[lesson] << " student(s)" << endl;
}

void Apps::GetUserByNickName(vector<User> users, string login, bool admin)
{
	bool found = false; // if found user

	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].GetLogin() == login)
		{
			users[i].Disp(admin);
			found = true;
			break;
		}
	}

	if (!found) cout << "We haven`t user with login " << login << endl;

}


void Apps::SortByNumber(vector<User>& users)
{
	float *arr = new float[users.size()]; // array for users numbers
	
	for (int i = 0; i < users.size(); i++) // filling arr
	{
		arr[i] = users[i].getAvarageNumber();
	}

	sort(arr, arr + users.size()); // sorting arr

	vector<User> usersCopy = vector<User>(); // copy vector

	
	for (int i = 0; i < users.size(); i++) // initialize vector
	{
		for(int j = 0; j < users.size(); j++)
		{
			if (users[j].getAvarageNumber() == arr[i])
			{
				usersCopy.push_back(users[j]);
				break;
			}
		}
	}

	users = usersCopy;

	cout << "Success!" << endl;
	delete arr;
	
}

void Apps::SortByName(vector<User>& users)
{
	string *names = new string[users.size()]; // array of names
	vector<User> usersCopy; // for-time vector

	for (int i = 0; i < users.size(); i++) //initialize names
	{
		names[i] = users[i].GetFullName();
	}

	sort(names, names + users.size()); // sorting names

	for (int i = 0; i < users.size(); i++) // filling copy
	{
		for (int j = 0; j < users.size(); j++)
		{
			if (users[j].GetFullName() == names[i])
			{
				usersCopy.push_back(users[j]);
				break;
			}
		}
	}

	users = usersCopy;
	
}

void Apps::SortByGroups(vector<User>& users)
{
	string *groupsArr = new string[groups.size()]; // temporary arr
	vector<User> usersCopy; // for-time vector

	for (int i = 0; i < groups.size(); i++)
	{
		groupsArr[i] = groups[i];
	}

	sort(groupsArr, groupsArr + groups.size()); // sorting groups

	for (int i = 0; i < groups.size(); i++)
	{
		for (int j = 0; j < users.size(); j++)
		{
			if (users[j].GetGroup() == groupsArr[i])
			{
				usersCopy.push_back(users[j]);
				
			}
		}
	}

	users = usersCopy;
}

Apps::~Apps()
{
}
