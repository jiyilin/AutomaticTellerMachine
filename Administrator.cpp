#include "Administrator.h"

constexpr auto AdministratorID = "���ݴ�ѧ����ѧԺ";
constexpr auto AdministratorPassword = "123456";

Administrator::Administrator()
{
	this->id = AdministratorID;
	this->password = AdministratorPassword;
}

bool Administrator::AdminstratorLoad(string &name, string &key){
	if (name != this->id || key!=this->password)
	{
		return false;
	}
	return true;
}
