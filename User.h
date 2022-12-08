#pragma once

#ifndef User_H
#define User_H

#include "Human.h"

class User:private Human
{
private:
	string identityCard;
	double amount;
	bool state;
public:
	User();
	User(string &name, string &key, string &idCard, double &number);

	string Gain_User_Id();
	string Gain_User_Password();
	string Gain_User_IdentityCard();
	double Gain_USer_Amount();
	bool Gain_User_State();

	bool SetUserPassword(string &key);
	bool SetUserMoney(double pay, bool IsPush);
	bool SetUserCanUse(bool lock);
};


#endif // !User_H
