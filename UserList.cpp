#include "UserList.h"
#include<fstream>
#include<Windows.h>
#include<sstream>

void UserList_push_back(UserList* &lock, User eval)
{
	auto end = lock;
	while (end->next!=nullptr)
	{
		end = end->next;
	}

	auto nodeData = new User(eval.Gain_User_Id(), eval.Gain_User_Password(),
		eval.Gain_User_IdentityCard(), eval.Gain_USer_Amount(), eval.Gain_User_State());
	auto node = new UserList;
	node->data = nodeData;
	node->next = nullptr;

	end->next = node;
}

void UserList_push_front(UserList*& lock, User eval)
{
	auto nodeData = new User(eval.Gain_User_Id(), eval.Gain_User_Password(),
		eval.Gain_User_IdentityCard(), eval.Gain_USer_Amount(), eval.Gain_User_State());
	auto node = new UserList;
	node->data = nodeData;
	node->next = lock->next;

	lock->next = node;
}

void UserList_pop_back(UserList*& lock)
{
	if (UserList_Empty(lock))
	{
		return;
	}
	auto end = lock;
	while (end->next->next != nullptr)
	{
		end = end->next;
	}
	end->next = nullptr;
}

void UserList_pop_front(UserList*& lock)
{
	lock = lock->next;
	lock->data = nullptr;
}

bool UserList_Empty(UserList* lock)
{
	if (lock->next ==nullptr)
	{
		return true;
	}
	return false;
}

int UserList_Length(UserList* lock)
{
	int key = 0;
	auto search = lock;
	while (search->next!=nullptr)
	{
		search = search->next;
		key++;
	}
	return key;
}

User* UserList_gain_center(UserList* lock)
{
	int flag = UserList_Length(lock)/2;
	auto search = lock;
	while (flag!=0)
	{
		search = search->next;
		flag--;
	}
	return search->data;
}

//User* UserList_Split(UserList* lock, UserList*& left, UserList*& right)
//{
//	UserList_sort(lock);
//	auto flag = UserList_Length(lock);
//	int i = 0;
//	auto search = lock;
//	while (search->next!=nullptr)
//	{
//		search = search->next;
//		i++;
//		if (i<flag)
//		{
//			UserList_push_back(left, *(search->data));
//		}
//		else
//		{
//			UserList_push_back(right, *(search->data));
//		}
//	}
//	return UserList_gain_center(lock);
//}


UserList* UserList_InitUserList()
{
	auto head = new UserList;
	head->next = nullptr;
	return head;
}

void UserList_sort(UserList*& lock)
{
	User* process;
	auto search = lock;
	auto flag = search;
	while (search->next!=nullptr)
	{
		search = search->next;
		flag = search;
		while (flag!=nullptr)
		{
			flag = flag->next;
			if (flag->data->Gain_User_Id() < search->data->Gain_User_Id())
			{
				process = search->data;
				search->data = flag->data;
				flag->data = process;
			}
		}
	}
}

bool UserList_Read_Txt(UserList*& lock)
{
	std::ifstream read;
	read.open("./data/UsersData.txt", std::ios_base::in);
	if (read.is_open()==false)
	{
		MessageBox(nullptr, L"数据库异常，无法获取用户数据", L"ERROR", MB_OK);
		return false;
	}
	std::string input;
	std::string id;
	std::string password;
	std::string idCard;
	std::string process1;
	std::string process2;
	double cash;
	bool canUse;
	while (true)
	{
		read >> id >> idCard >> password >> process1 >> process2;
		if (process2 == "true")
		{
			canUse = true;
		}
		else
		{
			canUse = false;
		}
		std::stringstream stream(process1);
		stream >> cash;
		User process(id, password, idCard, cash, canUse);
		UserList_push_back(lock, process);
		if (read.eof())
		{
			break;
		}
	}
	read.close();
	return true;
}
