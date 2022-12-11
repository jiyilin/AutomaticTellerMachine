#include "UserTreeNode.h"

UserTreeNode::UserTreeNode()
{
	data = nullptr;
	left = nullptr;
	right = nullptr;
}

UserTreeNode::UserTreeNode(User* x)
{
	data = new User(x->Gain_User_Id(), x->Gain_User_IdentityCard(), x->Gain_User_Password(),
		x->Gain_USer_Amount(), x->Gain_User_State());
	this->left = nullptr;
	this->right = nullptr;
}

UserTreeNode::UserTreeNode(User* x, UserTreeNode* x_left, UserTreeNode* x_right)
{
	data = new User(x->Gain_User_Id(), x->Gain_User_IdentityCard(), x->Gain_User_Password(),
		x->Gain_USer_Amount(), x->Gain_User_State());
	this->left = x_left;
	this->right = x_right;
}

UserTreeNode* UserTreeNode::SortedListToBST(UserList*& nums)
{
	if (nums->empty())
	{
		return nullptr;
	}
	nums->sort();
	auto* key = new UserTreeNode;
	key->data = new User(nums->gain_center()->Gain_User_Id(),nums->gain_center()->Gain_User_IdentityCard(),
						nums->gain_center()->Gain_User_Password(),nums->gain_center()->Gain_USer_Amount(),
						nums->gain_center()->Gain_User_State());
	UserList* left_x;
	UserList* right_x;
	nums->split(left_x, right_x);
	key->left = SortedListToBST(left_x);
	key->right = SortedListToBST(right_x);
	return key;
}

UserTreeNode* UserTreeNode::SearchUserToBST(UserTreeNode* lock, std::string flag)
{
	if (lock == nullptr)
	{
		return nullptr;
	}
	UserTreeNode* key = nullptr;
	if (lock->data->Gain_User_Id() > flag)
	{
		key = SearchUserToBST(lock->left, flag);
	}
	else if(lock->data->Gain_User_Id() < flag)
	{
		key = SearchUserToBST(lock->right, flag);
	}
	return key;
}

bool UserTreeNode::UserSearch(std::string lock,User*& key)
{
	auto answer = SearchUserToBST(this, lock);
	if (answer == nullptr)
	{
		key = nullptr;
		return false;
	}
	key = answer->data;
	return true;
}


