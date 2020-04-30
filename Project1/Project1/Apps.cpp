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
	/*for (int i = 0; i < users.size(); i++)
	{
		users[i].Disp(admin);
		cout << endl;
	}*/

	int lineLenght = 0;
	int loginMaxSize = 0;
	int nameMaxSize = 0;
	int groupMaxSize = 0;
	int avarageNumberMaxSize = string("Avarage number:").size();
	int passwordMaxSize = 0;
	
	//finding maxsizes
	for (int i = 0; i < users.size(); i++)
	{
		//login
		if (users[i].GetLogin().size() > loginMaxSize)
		{
			loginMaxSize = users[i].GetLogin().size();
		}

		//name
		if (users[i].GetFullName().size() > nameMaxSize)
		{
			nameMaxSize = users[i].GetFullName().size();
		}

		//group
		if (users[i].GetGroup().size() > groupMaxSize)
		{
			groupMaxSize = users[i].GetGroup().size();
		}

		//password
		if (users[i].GetPass().size() > passwordMaxSize)
		{
			passwordMaxSize = users[i].GetPass().size();
		}
	}

	lineLenght = loginMaxSize + nameMaxSize + groupMaxSize + avarageNumberMaxSize + passwordMaxSize + 8;

	lineLenght += 10; // for role

	for (int j = 0; j < 5; j++)
	{
		lineLenght += nameLessons[j].size();
		lineLenght++;
	}

	//cout << loginMaxSize;
	//cout << groupMaxSize;

	for (int j = 0; j < lineLenght; j++) cout << '-';		// drawing
	cout << endl;

	cout << "Login:";
	for (int i = 0; i < loginMaxSize - 6; i++) cout << ' ';
	cout << '|';

	cout << "Name:";
	for (int i = 0; i < nameMaxSize - 3; i++) cout << ' ';
	cout << '|';

	cout << "Group:";
	for (int i = 0; i < groupMaxSize - 7; i++) cout << ' ';
	cout << '|';

	cout << "Avarage number:|";

	if (admin)
	{
		cout << "Pass:";
		for (int i = 0; i < passwordMaxSize - 5; i++) cout << ' ';
		cout << '|';
	}

	for (int j = 0; j < 5; j++)
	{
		cout << nameLessons[j] << ":" << '|';
	}

	cout << "Role:|";

	cout << endl;

	for (int i = 0; i < users.size(); i++)
	{
		for (int j = 0; j < lineLenght; j++) cout << '-';		// drawing
		cout << endl;											// line
		  
		//login
		cout << users[i].GetLogin();
		for (int j = 0; j < loginMaxSize - users[i].GetLogin().size(); j++)
		{
			cout << " ";
		}
		cout << '|';

		//name
		cout << users[i].GetName(0) << " " << users[i].GetName(1) << " " << users[i].GetName(2);
		for (int j = 0; j < nameMaxSize - users[i].GetFullName().size(); j++)
		{
			cout << " ";
		}
		cout << '|';

		//group
		cout << users[i].GetGroup();
		for (int j = 0; j < groupMaxSize - users[i].GetGroup().size(); j++)
		{
			cout << " ";
		}
		cout << '|';

		//avarageNumber
		cout << users[i].getAvarageNumber();
		for (int j = 0; j < avarageNumberMaxSize - to_string(int(users[i].getAvarageNumber())).size();  j++)
		{
			cout << " ";
		}
		cout << '|';

		//password
		if (admin)
		{
			cout << users[i].GetPass();
			for (int j = 0; j < passwordMaxSize - users[i].GetPass().size(); j++)
			{
				cout << " ";
			}
			cout << '|';
		}

		//lessons
		for (int j = 0; j < 5; j++)
		{
			string answer = " ";
			int addSpace = 0;
			if (users[i].getLesson(j))
			{
				answer = "yes";
				addSpace = nameLessons[j].size() - 3;
			}
			else
			{
				answer = "no";
				addSpace = nameLessons[j].size() - 2;
			}

			cout << answer;
			addSpace++;
			for (int i = 0; i < addSpace; i++) cout << ' ';
			cout << '|';

		}

		//role
		if (users[i].isAdmin()) cout << "admin|";
		else cout << "user |";

		cout << endl;
	}

	for (int j = 0; j < lineLenght; j++) cout << '-';
	cout << endl;

	/*cout << maxSize << endl;

	int b = 90;

	string a;
	a = to_string(b);
	cout << a << " " << a.length() << endl;*/

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
	float avarageNumber = -1;
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
	avarageNumber = getInput();
	while (avarageNumber <= 0 || avarageNumber > 100)
	{
		cout << "From 0 to 100 please: ";
		avarageNumber = getInput();
	}
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

void Apps::DeleteUser(vector<User>& userList, string _login)
{
	/*int index = 0;
	while (true)
	{
		cout << "Log number: ";
		cin >> index;
		if (index >= 0 && index <= userList.size()) break;
		cout << "Incorrect number" << endl;
	}*/

	bool found = false;

	//searching for user with _login
	vector<User>::iterator it = userList.begin();
	for (int i = 0; i < userList.size(); i++)
	{
		it++;
		if (userList[i].GetLogin() == _login)
		{
			found = true;
			it--;
			break;
		}
	}

	//confirmation

	if (found)
	{
		string boolString = " ";
		while (boolString != "yes" && boolString != "no")
		{
			cout << "Are you sure(yes or no): ";
			cin >> boolString;
		}
		if (boolString == "yes") userList.erase(it);
	}
	else cout << "We have not user with this login." << endl;
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

float Apps::getInput()
{
	float input = 0;

	while (true)
	{
		cin >> input;

		if (!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "That is not number. Log number. ";
		}
		else
		{
			break;
		}
	}

	return input;
}

Apps::~Apps()
{
}
