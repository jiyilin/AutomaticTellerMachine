#include <string>
#include <iostream>
#include <sstream>
#include<fstream>
#include<qstring.h>
#include<qtimer.h>
#include<qtimeline.h>
#include<qtimezone.h>

#include "AdminSide.h"
#include "UserTreeNode.h"

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
		double cash = ATM->Gain_CapitalPools();
		std::string process("资金填充成功,资金池现存：");
		process = process + std::to_string(cash);
		auto output = QString::fromStdString(process);
		QMessageBox msgBox(QMessageBox::Warning, "SUCCESS",output , QMessageBox::Ok, this);
		msgBox.exec();
	}
}

void AdminSide::on_PoolEmptyButton_click()
{
	QMessageBox msgBox(QMessageBox::Warning, "Warning", "确认清空资金库吗", QMessageBox::Ok | QMessageBox::Cancel, this);
	if (msgBox.exec() == QMessageBox::Ok)
	{
		ATM->EmptyThePool();
		QMessageBox msgBox1(QMessageBox::Warning, "SUCCESS", "已完成资金库清空", QMessageBox::Ok, this);
		msgBox1.exec();
	}
}

void AdminSide::on_UserQueriesPushButton_click()
{
	ui.UserDataQueriesList->clear();
	std::ifstream read;
	read.open("./data/UsersData.txt", std::ios_base::in);
	if (read.is_open() == false)
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "数据库异常，无法打开用户表并读取", QMessageBox::Ok);
		msgBox.exec();
		return;
	}
	std::string input;
	while (std::getline(read,input))
	{
		ui.UserDataQueriesList->addItem(input.c_str());
	}
}

void AdminSide::on_UserFreezesSuerPushButton_click()
{
	auto data = GainUSerData();
	std::string lock = ui.UserFreezesIdInput->text().toStdString();
	auto search = data;
	while (search->next!=nullptr)
	{
		search = search->next;
		if (search->data->Gain_User_Id() == lock)
		{
			search->data->SetUserCanUse(false);
			QMessageBox msgBox(QMessageBox::Warning, "SUCCESS", "冻结成功", QMessageBox::Ok);
			msgBox.exec();
			std::ofstream write;
			write.open("./data/UsersData.txt", std::ios_base::out);
			search = data;
			while (search->next != nullptr)
			{
				search = search->next;
				if (search->data->Gain_User_State() == true)
				{
					write << search->data->Gain_User_Id() << " " << search->data->Gain_User_IdentityCard() << " " << search->data->Gain_User_Password() << " " <<
						search->data->Gain_USer_Amount() << " " << "true" << std::endl;
				}
				else
				{
					write << search->data->Gain_User_Id() << " " << search->data->Gain_User_IdentityCard() << " " << search->data->Gain_User_Password() << " " <<
						search->data->Gain_USer_Amount() << " " << "false" << std::endl;
				}
			}
			write.close();
			return;
		}
	}
	QMessageBox msgBox(QMessageBox::Question, "ERROR", "冻结失败，查无此用户", QMessageBox::Ok);
	msgBox.exec();
}

void AdminSide::on_UserUnFreezePushButton_click()
{
	auto data = GainUSerData();
	std::string lock = ui.UserUnFreezesIdInput->text().toStdString();
	auto search = data;
	while (search->next != nullptr)
	{
		search = search->next;
		if (search->data->Gain_User_Id() == lock)
		{
			search->data->SetUserCanUse(true);
			QMessageBox msgBox(QMessageBox::Warning, "SUCCESS", "解冻成功", QMessageBox::Ok);
			msgBox.exec();
			std::ofstream write;
			write.open("./data/UsersData.txt", std::ios_base::out);
			search = data;
			while (search->next != nullptr)
			{
				search = search->next;
				if (search->data->Gain_User_State() == true)
				{
					write << search->data->Gain_User_Id() << " " << search->data->Gain_User_IdentityCard() << " " << search->data->Gain_User_Password() << " " <<
						search->data->Gain_USer_Amount() << " " << "true" << std::endl;
				}
				else
				{
					write << search->data->Gain_User_Id() << " " << search->data->Gain_User_IdentityCard() << " " << search->data->Gain_User_Password() << " " <<
						search->data->Gain_USer_Amount() << " " << "false" << std::endl;
				}
			}
			write.close();
			return;
		}
	}
	QMessageBox msgBox(QMessageBox::Question, "ERROR", "冻结失败，查无此用户", QMessageBox::Ok);
	msgBox.exec();
}

