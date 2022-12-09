#include "AdminSide.h"
#include <string>
#include <iostream>
using namespace std;

AdminSide::AdminSide(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);
	ui.LoadWindow->hide();
	ui.MenuWindow->hide();
	ui.LoadDashboardWindow->hide();
}

AdminSide::~AdminSide() = default;

void AdminSide::on_SignButton_click()
{
	if (ui.LoadIdInput->text().length()==0 || ui.LoadPasswordInput->text().length()==0)
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "账号与密码不能为空", QMessageBox::Ok, this);
		msgBox.exec();
	}
	string id = ui.LoadIdInput->text().toStdString();
	string password = ui.LoadPasswordInput->text().toStdString();
	if (!administrator.AdminstratorLoad(id,password))
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "账号或密码错误", QMessageBox::Ok, this);
		msgBox.exec();
		ui.LoadIdInput->setText("");
		ui.LoadPasswordInput->setText("");
	}
	else
	{
		ui.MenuWindow->show();
		ui.LoadDashboardWindow->show();
		ui.LoadIdInput->setText("");
		ui.LoadPasswordInput->setText("");
	}
}
