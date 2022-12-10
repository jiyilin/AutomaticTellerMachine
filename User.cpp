#include "User.h"

User::User()
{
	identityCard = "";
	amount = 0.0;
	state = false;
}

User::User(std::string name, std::string key, std::string idCard, double number)
{
	this->id = name;
	this->identityCard = idCard;
	this->password = key;
	this->amount = number;
	this->state = true;
}

User::User(std::string name, std::string key, std::string idCard, double number, bool is)
{
	this->id = name;
	this->identityCard = idCard;
	this->password = key;
	this->amount = number;
	this->state = is;
}

std::string User::Gain_User_Id()
{
	return this->id;
}

std::string User::Gain_User_Password()
{
	return this->password;
}

std::string User::Gain_User_IdentityCard()
{
	return this->identityCard;
}

double User::Gain_USer_Amount()
{
	return this->amount;
}

bool User::Gain_User_State()
{
	return this->state;
}

bool User::SetUserPassword(std::string& key)
{
	if (key.length() < 5 || key.length() > 12 || key == this->password)
	{
		return false;
	}
	this->password = key;
	return true;
}

bool User::SetUserMoney(double pay, bool IsPush)
{
	if (pay < 0)
	{
		return false;
	}

	if (IsPush == true)
	{
		this->amount = this->amount + pay;
	}
	else
	{
		if (this->amount - pay < 0)
		{
			return false;
		}
		this->amount = this->amount - pay;
	}
	return true;
}

bool User::SetUserCanUse(bool lock)
{
	if (this->state == lock)
	{
		return false;
	}
	this->state = lock;
	return true;
}
