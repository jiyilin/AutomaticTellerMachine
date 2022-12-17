#pragma once

#ifndef Administrator_H
#define Administrator_H

#include <string>
#include <list>

#include "Human.h"

class Administrator : private Human
{
public:
	Administrator();
	bool AdminstratorLoad(std::string &name, std::string &key);
};

bool GainFundsTrackingAnswer(std::string FundsTrackingFrom,
							 std::string FundsTrackingTo, std::string FundsTrackingTime,
							 std::list<std::list<std::string>> &key);

void GainFundsTrackingPROCESS(std::string eval, std::list<std::list<std::string>>& key);
std::string ChangeHistoryString(std::string &lock);
#endif // !Administrator_H