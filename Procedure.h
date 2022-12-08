#pragma once

#include"AutomaticTellerMachine.h"

class Procedure
{
private:

	//Main window
	AutomaticTellerMachine* mainWindow;

public:
	Procedure();

	void SetMainWindowShow();
	void SetMainWindowHide();
};
