#include "Apps.h"
#include <iostream>

using namespace std;


Apps::Apps()
{
}

void Apps::Commands(bool isAdmin)
{
	cout << "/profile - get info about your profile" << endl;
	cout << "/switchProfile - change your profile" << endl;
	cout << "/changeLogin - change your login" << endl;
	cout << "/exit - leave the programm" << endl;
}


Apps::~Apps()
{
}
