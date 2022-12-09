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

