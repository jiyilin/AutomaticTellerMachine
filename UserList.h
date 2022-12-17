#pragma once

#ifndef UserList_H
#define UserList_H

#include "User.h"

using UserList = struct UserList
{
	User *data;
	UserList *next;
};

void UserList_push_back(UserList *&lock, User eval);
void UserList_push_front(UserList *&lock, User eval);
void UserList_pop_back(UserList *&lock);
void UserList_pop_front(UserList *&lock);
bool UserList_Empty(UserList *lock);
int UserList_Length(UserList *lock);
User *UserList_gain_center(UserList *lock);
// User* UserList_Split(UserList* lock,UserList*& left, UserList*& right);
UserList *UserList_InitUserList();
void UserList_sort(UserList *&lock);
bool UserList_Read_Txt(UserList *&lock);

#endif // !UserList_H
