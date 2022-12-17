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
			process.push_back(FundsTrackingFrom + " " + remark);
			break;
		}
	}
	readMain.close();
	if (process.empty()!=true)
	{
		key.push_back(process);
	}

	auto VECTORSEARCH = key.begin();
	while (VECTORSEARCH!=key.end())
	{
		auto LISTSEARCH = (*VECTORSEARCH).begin();
		while (LISTSEARCH!=(*VECTORSEARCH).end())
		{
			GainFundsTrackingPROCESS(*LISTSEARCH, key);
			LISTSEARCH++;
		}
		VECTORSEARCH++;
	}
	return true;
}

std::string ChangeHistoryString(std::string &lock)
{
	auto start = lock.length();
	while (lock[start]!=' ')
	{
		start--;
	}
	std::string key;
	for (; start < lock.size(); start++)
	{
		key.push_back(lock[start]);
	}

	std::string name;
	int flag = 0;
	start = 0;
	for (;start < lock.size(); start++)
	{
		if (lock[start]==' ')
		{
			flag++;
		}
		if (flag==2)
		{
			name.push_back(lock[start]);
		}
		else if(flag ==3)
		{
			break;
		}
	}

	lock = name;
	return key;
}

void GainFundsTrackingPROCESS(std::string eval, std::list<std::list<std::string>>& key)
{
	auto flag = ChangeHistoryString(eval);
	std::ifstream read;
	read.clear();
	std::string txt = "./data/" + eval + ".txt";
	read.open(txt, std::ios_base::in);
	if (read.is_open()==false)
	{
		return;
	}
	std::string remark;
	std::list<std::string> process;
	bool flagStart = false;
	while (std::getline(read, remark))
	{
		if (std::strstr(remark.c_str(), flag.c_str()) != nullptr)
		{
			flagStart = true;
		}
		else
		{
			if (flagStart==false)
			{
				continue;
			}
			if (std::strstr(remark.c_str(),"向"))
			{
				process.push_back(eval + " " + remark);
			}
		}
	}
	if (process.empty() != true)
	{
		key.push_back(process);
	}
	read.close();
}
