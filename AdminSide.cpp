#include "AdminSide.h"

AdminSide::AdminSide(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);
	ui.LoadWindow->hide();
	ui.MenuWindow->hide();
	ui.LoadDashboardWindow->hide();
}

AdminSide::~AdminSide() = default;
