#pragma once

#ifndef UserList_H
#define UserList_H

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
	void split(User* left, User* right, User* center);
	bool empty();
};

#endif // !UserList_H
