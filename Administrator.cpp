#include <fstream>
#include<string.h>
#include "Administrator.h"

constexpr auto AdministratorID = "福州大学至诚学院";
constexpr auto AdministratorPassword = "123456";

Administrator::Administrator()
{
	this->id = AdministratorID;
	this->password = AdministratorPassword;
}

bool Administrator::AdminstratorLoad(std::string &name, std::string &key)
{
	if (name != this->id || key != this->password)
	{
		return false;
	}
	return true;
}

bool GainFundsTrackingAnswer(std::string FundsTrackingFrom, std::string FundsTrackingTo,
							 std::string FundsTrackingTime, std::list<std::list<std::string>> &key)
{
	std::ifstream readMain;
	readMain.open("./data/" + FundsTrackingFrom + ".txt", std::ios_base::in);
	if (readMain.is_open() == false)
	{
		return false;
	}
	std::string remark;
	std::list<std::string> process;
	while (std::getline(readMain,remark))
	{
		if (std::strstr(remark.c_str(), FundsTrackingTo.c_str()) !=nullptr &&
			std::strstr(remark.c_str(), FundsTrackingTime.c_str())!=nullptr)
		{
			process.push_back(remark);
			break;
		}
	}
	if (process.empty()!=true)
	{
		key.push_back(process);
	}



	return true;
}
