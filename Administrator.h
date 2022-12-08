#pragma once

#ifndef Administrator_H
#define Administrator_H

#include"Human.h"

class Administrator :private Human
{
public:
	Administrator();
	bool AdminstratorLoad(string& name, string& key);
};

#endif // !Administrator_H
