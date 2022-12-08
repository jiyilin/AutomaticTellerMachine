#pragma once

#ifndef Procedure_H
#define Procedure_H

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


#endif // !Procedure_H