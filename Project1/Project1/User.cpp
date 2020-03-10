#include "User.h"
#include "Lessons.h"
#include <iostream>

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
	cout << "Login: " << login << "\nName: " << name << " " << surname << " " << fatherName << "\nGroup: " << group << "\nAvarage number: " << avarageNumber << endl;
	if (_admin) cout << "Password: " << pass << endl;
 
	cout << "\nLessons:" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << nameLessons[i] << ": ";
		if (goingLessons[i]) cout << "yes";
		else cout << "no";
		cout << endl;
	}

	cout << "\nRole: ";
	if (admin) cout << " admin";
	else cout << " user";
	cout << endl;
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

void User::SetLogin(string _login)
{
	login = _login;
}

void User::SetLesson(int _lesson, bool _going)
{
	if (_lesson < 5)
	{
		goingLessons[_lesson] = _going;
	}
	else
	{
		cout << "Too big number." << endl;
	}
}

bool User::isAdmin()
{
	return admin;
}


User::~User()
{
}
