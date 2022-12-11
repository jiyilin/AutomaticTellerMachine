#pragma once

#ifndef UserTreeNode_H
#define UserTreeNode_H

#include<string>
#include"UserList.h"

class UserTreeNode
{
private:
	User* data;
	UserTreeNode* left;
	UserTreeNode* right;
public:
	UserTreeNode();
	UserTreeNode(User* x);
	UserTreeNode(User* x, UserTreeNode* left, UserTreeNode* right);
	UserTreeNode* SortedListToBST(UserList*& nums);
	UserTreeNode* SearchUserToBST(UserTreeNode* lock,std::string flag);
	bool UserSearch(std::string lock, User*& key);
};



#endif // !UserTreeNode_H