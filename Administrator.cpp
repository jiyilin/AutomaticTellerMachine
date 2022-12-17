#include<fstream>
#include "Administrator.h"

constexpr auto AdministratorID = "福州大学至诚学院";
constexpr auto AdministratorPassword = "123456";

Administrator::Administrator(){
	this->id = AdministratorID;
	this->password = AdministratorPassword;
}

bool Administrator::AdminstratorLoad(std::string &name, std::string &key){
	if (name != this->id || key!=this->password)
	{
		return false;
	}
	return true;
}

bool GainFundsTrackingAnswer(std::string FundsTrackingFrom, std::string FundsTrackingTo,
							std::string FundsTrackingTime, std::vector<std::list<std::string>>& key)
{
	std::ifstream readMain;
	readMain.open("./data/" + FundsTrackingFrom + ".txt", std::ios_base::in);
	if (readMain.is_open() == false)
	{
		return false;
	}
	return true;
}
