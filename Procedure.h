#pragma once

#ifndef Procedure_H
#define Procedure_H

#include <windows.h>
#include"AutomaticTellerMachine.h"

class Procedure
{
private:

	//Main window
	AutomaticTellerMachine* mainWindow;

	void SetMainWindowShow();
	bool DatabaseDetection();

public:
	Procedure();
	void SetMainWindowHide();
	bool EngineStarts();
};


#endif // !Procedure_H