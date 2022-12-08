#include "Procedure.h"

Procedure::Procedure(){
	mainWindow = new AutomaticTellerMachine;
}

void Procedure::SetMainWindowShow(){
	this->mainWindow->show();
}

void Procedure::SetMainWindowHide(){
	this->mainWindow->hide();
}

