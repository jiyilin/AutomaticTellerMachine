#include "Client.h"

Client::Client(QWidget *parent): QMainWindow(parent){
	ui.setupUi(this);

	ui.LoadWindow->hide();
	ui.RegisteredWindow->hide();
	ui.Menu->hide();
	ui.LoadDashBoadWindow->hide();
}

Client::~Client() = default;
