#include "User.h"
#include "Lessons.h"
#include <iostream>
#include <vector>

using namespace std;


User::User()
{
}

User::User(string _login, string _name, string _surname, string _fatherName, string _pass, string _group, float _avarageNumb, bool lessons[5], bool _admin)
{
	login = _login;
	name = _name;
	surname = _surname;
	fatherName = _fatherName;
	pass = _pass;
	group = _group;
	avarageNumber = _avarageNumb;
	admin = _admin;
	//lessons
	for (int i = 0; i < 5; i++)
	{
		goingLessons[i] = lessons[i];
	}
}

void User::Disp(bool _admin)
{
	for (int i = 0; i < 25; i++) cout << '-';
	cout << endl;
	cout << "Login: " << login << endl;
	cout << "Full name: " << name << " " << surname << " " << fatherName << endl;
	cout << "Group: " << group << endl;
	cout << "Avarage number: " << avarageNumber << endl;
	if (admin) cout << "Password: " << pass << endl;
	
	//going lessson
	for (int i = 0; i < 5; i++)
	{
		cout << nameLessons[i] << ": ";
		if (goingLessons[i])
		{
			cout << "yes" << endl;
		}
		else
		{
			cout << "no" << endl;
		}
	}

	cout << "Role: ";
	if (admin) cout << "admin" << endl;
	else cout << "user" << endl;
}

string User::GetLogin()
{
	return login;
}

string User::GetName(int i)
{
	if (i == 0) return name;
	else if (i == 1) return surname;
	else return fatherName;
}

string User::GetPass()
{
	return pass;
}

string User::GetGroup()
{
	return group;
}

string User::GetFullName()
{
	return (name + surname + fatherName);
}

float User::getAvarageNumber()
{
	return avarageNumber;
}

bool User::getLesson(int i)
{
	return goingLessons[i];
}

void User::SetLogin(vector<User> users, string _login)
{
	bool found = false;
	string boolString = " ";
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].GetLogin() == _login)
		{
			found = true;
			break;
		}
	}
	if (!found)
	{
		while (boolString != "yes" && boolString != "no")
		{
			cout << "Are you sure?(yes or no): ";
			cin >> boolString;
		}
		
		if(boolString == "yes")login = _login;
	}
	else cout << "This login already exist. Choose another." << endl;
}

void User::SetLesson(int _lesson, bool _going)
{
	if (_lesson < 5 && _lesson >= 0)
	{
		if (goingLessons[_lesson] != _going)
		{
			goingLessons[_lesson] = _going;
			if (_going) studentsToLessons[_lesson]++;
			else studentsToLessons[_lesson]--;
		}
	}
	else
	{
		cout << "Too big or too small number. It have be from 0 to 4." << endl;
	}
}

bool User::isAdmin()
{
	return admin;
}


User::~User()
{
}
