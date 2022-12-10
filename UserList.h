#pragma once

#ifndef UserList_H
#define UserList_H

#include<string>
#include "User.h"

class UserList
{
private:
	User* data;
	UserList* head;
	UserList* next;
public:
	UserList();
	void push_back(User lock);
	void push_front(User lock);
	void pop_back();
	void pop_front();
	void sort();
	User* gain_center();
	int size();
	void split(UserList* &left, UserList* &right, User* &center);
	bool empty();
	bool eraser(std::string lock);
};

#endif // !UserList_H
