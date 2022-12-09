#pragma once

#ifndef Administrator_H
#define Administrator_H

#include<string>

#include"Human.h"

class Administrator :private Human
{
public:
	Administrator();
	bool AdminstratorLoad(std::string& name, std::string& key);
};

#endif // !Administrator_H
