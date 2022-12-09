﻿#include <string>
#include <iostream>
#include <sstream>
#include<qstring.h>
#include<qtimer.h>
#include<qtimeline.h>
#include<qtimezone.h>

#include "AdminSide.h"

AdminSide::AdminSide(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);
	this->ATM = ATMPort();

	ui.LoadWindow->hide();
	ui.MenuWindow->hide();
	ui.LoadDashboardWindow->hide();
	ui.FundFillingWindow->hide();
}

AdminSide::~AdminSide() = default;

void AdminSide::on_SignButton_click()
{
	if (ui.LoadIdInput->text().length()==0 || ui.LoadPasswordInput->text().length()==0)
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "账号与密码不能为空", QMessageBox::Ok, this);
		msgBox.exec();
		return;
	}
	std::string id = ui.LoadIdInput->text().toStdString();
	std::string password = ui.LoadPasswordInput->text().toStdString();
	if (!administrator.AdminstratorLoad(id,password))
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "账号或密码错误", QMessageBox::Ok, this);
		msgBox.exec();
	}
	else
	{
		ui.MenuWindow->show();
		ui.backgroundWindow->show();
		ui.LoadWindow->show();
		ui.LoadDashboardWindow->show();

		double cash = ATM->Gain_CapitalPools();
		std::stringstream stream;
		stream << cash;
		std::string key;
		stream >> key;
		ui.PoolExistingFunds->setText(QString::fromStdString(key));

		QDateTime time = QDateTime::currentDateTime();
		ui.LoadDashboardWindowTime->setText(time.toString("yyyy-MM-dd hh:mm:ss"));
	}
}

void AdminSide::on_FundFillingButton_click()
{
	std::string input = ui.CashInput->text().toStdString();
	std::stringstream stream(input);
	double key;
	stream >> key;
	if (!ATM->Push_CapitalPools(key))
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "资金输入错误，填充失败", QMessageBox::Ok, this);
		msgBox.exec();
	}
	else
	{
		QMessageBox msgBox(QMessageBox::Warning, "SUCCESS", "资金填充成功", QMessageBox::Ok, this);
		msgBox.exec();
	}
}
