#pragma once

#ifndef Administrator_H
#define Administrator_H

#include<string>
#include<vector>
#include<list>

#include"Human.h"

class Administrator :private Human
{
public:
	Administrator();
	bool AdminstratorLoad(std::string& name, std::string& key);
};

bool GainFundsTrackingAnswer(std::string FundsTrackingFrom,
	std::string FundsTrackingTo, std::string FundsTrackingTime,
	std::vector<std::list<std::string>> &key);
#endif // !Administrator_H
