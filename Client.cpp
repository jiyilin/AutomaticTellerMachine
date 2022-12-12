#include "Client.h"
#include<string>
#include <fstream>
#include<sstream>
#include<qmessagebox.h>
#include<qtimer.h>
#include<qtimeline.h>
#include<qtimezone.h>
#include"UserTreeNode.h"

Client::Client(QWidget *parent): QMainWindow(parent){
	ui.setupUi(this);
	this->ATM = ATMPort();
	this->userNow = nullptr;

	ui.LoadWindow->hide();
	ui.RegisteredWindow->hide();
	ui.Menu->hide();
	ui.LoadDashBoadWindow->hide();
	ui.WithdrawalWindow->hide();
}

Client::~Client() = default;

bool Check_Id_Exist(std::string &lock)
{
	std::ifstream read;
	read.open("./data/UsersData.txt", std::ios_base::in);
	if (read.is_open() == false)
	{
		std::ofstream write;
		write.open("./data/UsersData.txt", std::ios_base::out);
		write.close();
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "数据库异常，无法打开用户表并读取,已重新创建用户表", QMessageBox::Ok);
		msgBox.exec();
		read.open("./data/UsersData.txt", std::ios_base::in);
	}
	std::string input;
	while (std::getline(read,input))
	{

		auto  CaptureID = [&input] {
			std::string key;
			for (int i = 0; i < input.size(); i++)
			{
				if (input[i] == ' ')
				{
					break;
				}
				key.push_back(input[i]);
			}
			return key;
		};

		if (auto key = CaptureID(); lock == key)
		{
			QMessageBox msgBox(QMessageBox::Question, "ERROR", "注册失败，该用户已存在", QMessageBox::Ok);
			msgBox.exec();
			return true;
		}
		read.close();
	}
	return false;
}

void Client::on_RegisteredPushButton_click()
{
	std::string id = ui.RegisteredIdInput->text().toStdString();
	std::string idCard = ui.RegisteredIdCardInput->text().toStdString();
	std::string password = ui.RegisteredPasswordInput->text().toStdString();
	std::string passwordCheck = ui.RegisteredPasswordCheckInput->text().toStdString();

	if (id.empty() || idCard.empty() || password.empty() || passwordCheck.empty())
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "输入不能为空", QMessageBox::Ok);
		msgBox.exec();
	}
	else if(password.length() < 6 || password.length() > 12)
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "密码应大于5位，并小于13位", QMessageBox::Ok);
		msgBox.exec();
	}
	else if(password != passwordCheck)
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "两次密码输入不一致", QMessageBox::Ok);
		msgBox.exec();
	}
	else if(Check_Id_Exist(id))
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "注册失败", QMessageBox::Ok);
		msgBox.exec();
	}
	else
	{
		std::ofstream write;
		write.open("./data/UsersData.txt", std::ios_base::app);
		if (write.is_open() == false)
		{
			QMessageBox msgBox(QMessageBox::Question, "ERROR", "数据库异常，无法打开用户表并写入", QMessageBox::Ok);
			msgBox.exec();
		}
		else
		{
			write << id << " " << idCard << " " << password <<" " << "0" << " " << "true" << std::endl;
			write.close();
			QMessageBox msgBox(QMessageBox::Warning, "SUCCESS", "注册成功", QMessageBox::Ok);
			msgBox.exec();
		}
	}
}

void Client::on_LoadSureButton_click()
{
	if (ui.LoadIdInput->text().length() == 0 || ui.LoadPasswordInput->text().length() == 0)
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "账号密码不能为空", QMessageBox::Ok);
		msgBox.exec();
	}
	else
	{
		if (UserLoad(ui.LoadIdInput->text().toStdString(),ui.LoadPasswordInput->text().toStdString(),this->userNow))
		{
			ui.RegisteredWindow->show();
			ui.LoadDashBoadWindow->show();
			ui.Menu->show();

			QString id = QString::fromStdString(userNow->Gain_User_Id());
			ui.LoadDashBoardId->setText(id);

			std::stringstream stream;
			stream << userNow->Gain_USer_Amount();
			std::string process;
			stream >> process;
			QString cash = QString::fromStdString(process);
			ui.LoadDashBoardCash->setText(cash);

			if (userNow->Gain_User_State()==true)
			{
				ui.LoadDashBoardState->setText("该用户已激活");
			}
			else
			{
				ui.LoadDashBoardState->setText("该用户未激活");
			}

			QDateTime time = QDateTime::currentDateTime();
			ui.LoadDashBoardTime->setText(time.toString("yyyy-MM-dd hh:mm:ss"));
		}
		else
		{
			if (this->userNow!=nullptr)
			{
				QMessageBox msgBox(QMessageBox::Question, "ERROR", "密码错误", QMessageBox::Ok);
				msgBox.exec();
				this->userNow = nullptr;
			}
			else
			{
				QMessageBox msgBox(QMessageBox::Question, "ERROR", "该用户不存在", QMessageBox::Ok);
				msgBox.exec();
			}
		}
	}
}

void Client::on_UserExitButton_click()
{
	std::stringstream stream;
	stream << userNow->Gain_USer_Amount();
	std::string process;
	stream >> process;

	std::ofstream write;
	write.open("./data/UsersData.txt", std::ios_base::app);
	if (userNow->Gain_User_State() == true)
	{
		write << userNow->Gain_User_Id() << " " << userNow->Gain_User_IdentityCard() << " " <<
			userNow->Gain_User_Password() << " " << process << " " << "true" << std::endl;
	}
	else
	{
		write << userNow->Gain_User_Id() << " " << userNow->Gain_User_IdentityCard() << " " <<
			userNow->Gain_User_Password() << " " << process << " " << "false" << std::endl;
	}
	write.close();
}

void Client::on_WithdrawalPushButton_click()
{
	if (userNow->Gain_User_State()==false)
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "存款失败，该用户已被冻结", QMessageBox::Ok);
		msgBox.exec();
	}
	else
	{
		std::stringstream stream(ui.WithdrawalInput->text().toStdString());
		double input;
		stream >> input;
		if (this->ATM->Push_CapitalPools(input))
		{
			userNow->SetUserMoney(input, true);
			on_UserDeposit_click();
		}
		else
		{
			QMessageBox msgBox(QMessageBox::Question, "ERROR", "存款失败，资金池已满", QMessageBox::Ok);
			msgBox.exec();
		}
	}
}

void Client::on_UserDeposit_click()
{
	std::stringstream stream;
	stream << userNow->Gain_USer_Amount();
	std::string key;
	stream >> key;
	QString out = QString::fromStdString(key);
	ui.WithdrawalBalance->setText(out);
	ui.WithdrawalBalance->update();
}

void Client::on_UserWithdrawalButton_click()
{
	std::stringstream stream;
	stream << userNow->Gain_USer_Amount();
	std::string key;
	stream >> key;
	QString out = QString::fromStdString(key);
	ui.DepositBalance->setText(out);
}

void Client::on_DepositButton_click()
{
	if (userNow->Gain_User_State() == false)
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "取款失败，该用户已被冻结", QMessageBox::Ok);
		msgBox.exec();
	}
	else
	{
		std::string process = ui.DepositInput->text().toStdString();
		std::stringstream stream(process);
		double input;
		stream >> input;
		if (this->ATM->Pop_CapitalPools(input))
		{
			userNow->SetUserMoney(input, false);
			on_UserWithdrawalButton_click();
		}
		else
		{
			QMessageBox msgBox(QMessageBox::Question, "ERROR", "取款失败，资金池已满", QMessageBox::Ok);
			msgBox.exec();
		}
	}
}
