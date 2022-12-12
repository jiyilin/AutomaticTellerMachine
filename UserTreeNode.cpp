#include "UserTreeNode.h"
#include<windows.h>
#include<fstream>
#include<sstream>

UserTreeNode* SortedUserListToBST(UserList*& lock)
{
	if (UserList_Length(lock)==0)
	{
		return nullptr;
	}

	auto left = UserList_InitUserList();
	auto right = UserList_InitUserList();

	auto key = new UserTreeNode;
	key->data = UserList_gain_center(lock);

	auto search = lock;
	while (search->next !=nullptr)
	{
		search = search->next;
		if (key==nullptr)
		{
			break;
		}
		if (search->data->Gain_User_Id() > key->data->Gain_User_Id())
		{
			auto process = new User(search->data->Gain_User_Id(), search->data->Gain_User_Password(),
				search->data->Gain_User_IdentityCard(), search->data->Gain_USer_Amount(),
				search->data->Gain_User_State());
			UserList_push_back(right, *process);
		}
		else if (search->data->Gain_User_Id() < key->data->Gain_User_Id())
		{
			auto process = new User(search->data->Gain_User_Id(), search->data->Gain_User_Password(),
				search->data->Gain_User_IdentityCard(), search->data->Gain_USer_Amount(),
				search->data->Gain_User_State());
			UserList_push_back(left, *process);
		}
	}

	key->left = SortedUserListToBST(left);
	key->right = SortedUserListToBST(right);
	return key;
}

bool SearchUserTreeNode(UserTreeNode*& lock, std::string eval, User*& key)
{
	if (lock == nullptr)
	{
		return false;
	}
	bool flag = false;
	if (lock->data->Gain_User_Id() > eval)
	{
		flag = SearchUserTreeNode(lock->left, eval, key);
	}
	else if(lock->data->Gain_User_Id() < eval)
	{
		flag = SearchUserTreeNode(lock->right, eval, key);
	}
	else
	{
		key = lock->data;
	}
	if (key==nullptr)
	{
		return false;
	}
	return true;
}

bool SearchUserTreeList(UserList* lock, std::string eval, User*& key)
{
	while (lock->next != nullptr)
	{
		lock = lock->next;
		if (lock->data->Gain_User_Id() == eval)
		{
			key = lock->data;
			return true;
		}
	}
	key = nullptr;
	return false;
}


UserList* GainUSerData()
{
	auto lock = UserList_InitUserList();
	if (!UserList_Read_Txt(lock))
	{
		MessageBox(nullptr, L"用户数据异常，无法获取用户数据", L"ERROR", MB_OK);
		return nullptr;
	}
	//auto key = SortedUserListToBST(lock);
	return lock;
}

bool UserDataFlushed(std::string flag)
{
	auto* lock = UserList_InitUserList();
	if (!UserList_Read_Txt(lock))
	{
		return false;
	}

	std::ofstream write;
	write.open("./data/UsersData.txt", std::ios_base::out);
	while (lock->next !=nullptr)
	{
		lock = lock->next;

		if (lock->data->Gain_User_Id() != flag)
		{
			std::stringstream stream;
			stream << lock->data->Gain_USer_Amount();
			std::string process;
			stream >> process;

			if (lock->data->Gain_User_State()==true)
			{
				write << lock->data->Gain_User_Id() << " " << lock->data->Gain_User_IdentityCard() << " " <<
					lock->data->Gain_User_Password() << " " << process << " " << "true" << std::endl;
			}
			else
			{
				write << lock->data->Gain_User_Id() << " " << lock->data->Gain_User_IdentityCard() << " " <<
					lock->data->Gain_User_Password() << " " << process << " " << "false" << std::endl;
			}
		}
	}
	write.close();
	return true;
}

bool UserLoad(std::string id, std::string password, User* &key)
{
	auto data = GainUSerData();
	if (!SearchUserTreeList(data,id,key))
	{
		key = nullptr;
		return false;
	}
	else
	{
		if (key->Gain_User_Password()==password && UserDataFlushed(key->Gain_User_Id()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
