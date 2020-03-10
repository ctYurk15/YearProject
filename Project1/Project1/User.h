#pragma once
#include <string>
#include "Lessons.h"

using namespace std;

class User
{
private:
	string login = " ";
	string name = " ";
	string surname = " ";
	string fatherName = " ";
	string pass = " ";
	string group = " ";
	float avarageNumber = 0;
	bool goingLessons[5];
	bool admin = false;
public:
	User();
	User(string _login, string _name, string _surname, string _fatherName, string _pass, string _group, float _avarageNumb, bool lessons[5], bool _admin);
	void Disp(bool);
	string GetLogin();
	string GetName(int);
	string GetPass();
	string GetGroup();
	float getAvarageNumber();
	bool getLesson(int);
	void SetLogin(string);
	void SetLesson(int, bool);
	bool isAdmin();
	~User();
};

