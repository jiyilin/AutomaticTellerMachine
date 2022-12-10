#include "UserList.h"


UserList::UserList()
{
	this->head = new UserList;
	this->data = nullptr;
	this->next = head;
	this->head->next = nullptr;
	this->head->data = nullptr;
}

void UserList::push_back(User lock)
{
	auto node = new UserList;
	node->data = new User(lock.Gain_User_Id(), lock.Gain_User_Password(),
						lock.Gain_User_IdentityCard(), lock.Gain_USer_Amount());
	node->next = nullptr;
	node->head = nullptr;

	UserList* search = this->head;
	while (search->next!=nullptr)
	{
		search = search->next;
	}
	search->next = node;
}

void UserList::push_front(User lock)
{
	auto node = new UserList;
	node->data = new User(lock.Gain_User_Id(), lock.Gain_User_Password(),
						lock.Gain_User_IdentityCard(), lock.Gain_USer_Amount());
	node->next = nullptr;
	node->head = nullptr;

	node->next = this->head->next;
	this->head->next = node;
}

void UserList::pop_back()
{
	if (this->head->next == nullptr)
	{
		return;
	}
	UserList* search = this;
	while (search->next->next != nullptr)
	{
		search = search->next;
	}
	search->next = nullptr;
}

void UserList::pop_front()
{
	if (this->head->next == nullptr)
	{
		return;
	}
	this->head->next = this->head->next->next;
}

void UserList::sort()
{
	if (this->head->next == nullptr)
	{
		return;
	}
	User* process;
	for (auto left = this->head->next; left != nullptr; left = left->next)
	{
		for (auto right = left; right != nullptr; right = right->next)
		{
			if (left->data->Gain_User_Id() > right->data->Gain_User_Id())
			{
				process = left->data;
				left->data = right->data;
				right->data = process;
			}
		}
	}
}

User* UserList::gain_center()
{
	int number = this->size()/2;
	auto search = this->head;
	int key = 0;
	while (key < number)
	{
		key++;
		search = search->next;
	}
	return search->data;
}

int UserList::size()
{
	int key = 0;
	auto search = this->head;
	while (search->next != nullptr)
	{
		search = search->next;
		key++;
	}
	return key;
}

void UserList::split(UserList* &left, UserList* &right, User* &center)
{
	center = this->gain_center();
	left = new UserList;
	right = new UserList;
	auto search = this->head;
	bool isLeft = true;
	while (search->next!=nullptr)
	{
		search = search->next;
		if (search->data->Gain_User_Id() == center->Gain_User_Id())
		{
			isLeft = false;
		}
		else if(isLeft == true)
		{
			auto node = User(search->data->Gain_User_Id(), search->data->Gain_User_IdentityCard(),
				search->data->Gain_User_Password(), search->data->Gain_USer_Amount(), search->data->Gain_User_State());
			left->push_back(node);
		}
		else
		{
			auto node = User(search->data->Gain_User_Id(), search->data->Gain_User_IdentityCard(),
				search->data->Gain_User_Password(), search->data->Gain_USer_Amount(), search->data->Gain_User_State());
			right->push_back(node);
		}
	}
}



bool UserList::empty()
{
	if (this->head->next == nullptr)
	{
		return true;
	}
	return false;
}

bool UserList::eraser(std::string lock)
{
	if (this->empty())
	{
		return false;
	}
	auto search = this->head->next;
	auto SearchBefore = this->head;
	while (search->next!=nullptr)
	{
		SearchBefore = search;
		search = search->next;
		if (search->data->Gain_User_Id()==lock)
		{
			SearchBefore->next = search->next;
			return true;
		}
	}
	return false;
}

