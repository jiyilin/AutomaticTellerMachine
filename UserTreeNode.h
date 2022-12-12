#pragma once

#ifndef UserTreeNode_H
#define UserTreeNode_H

#include"UserList.h"

using UserTreeNode = struct UserTreeNode
{
	User* data;
	UserTreeNode* left;
	UserTreeNode* right;
	UserTreeNode() :data(nullptr), left(nullptr), right(nullptr) {};
};

UserTreeNode* SortedUserListToBST(UserList*& lock);
bool SearchUserTreeNode(UserTreeNode*& lock, std::string eval, User*& key);
UserList* GainUSerData();
bool UserLoad(std::string id, std::string password, User* &key);
bool SearchUserList(UserList* lock, std::string eval, User*& key);
#endif // !UserTreeNode_H
