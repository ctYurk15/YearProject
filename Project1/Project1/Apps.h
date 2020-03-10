#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "User.h"

using namespace std;

class Apps
{
public:
	Apps();
	void Commands(bool);
	void DispUsers(vector<User>, bool);

	//redacting userlist
	void ReadUsers(vector<User>&, string);
	void WriteUsers(vector<User>, string);
	void AddUser(vector<User>&);
	void DeleteUser(vector<User>&);

	//searching
	void DisplayUsersFromGroup(vector<User>, string, bool);
	void DisplayUsersByLesson(vector<User>, int, bool);
	void GetUserByNickName(vector<User>, string, bool);

	//sorting
	void SortByNumber(vector<User>&);
	~Apps();
};

