#pragma once

#ifndef User_H
#define User_H

#include "Human.h"

class User:private Human
{
private:
	std::string identityCard;
	double amount;
	bool state;
public:
	User();
	User(std::string name, std::string key, std::string idCard, double number);

	std::string Gain_User_Id();
	std::string Gain_User_Password();
	std::string Gain_User_IdentityCard();
	double Gain_USer_Amount();
	bool Gain_User_State();

	bool SetUserPassword(std::string &key);
	bool SetUserMoney(double pay, bool IsPush);
	bool SetUserCanUse(bool lock);
};


#endif // !User_H
