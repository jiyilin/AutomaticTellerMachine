#include "Client.h"
#include<string>
#include <fstream>
#include<sstream>
#include<Windows.h>
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
	if (userNow == nullptr)
	{
		return;
	}
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
		return;
	}
	else
	{
		std::stringstream stream(ui.WithdrawalInput->text().toStdString());
		double input;
		stream >> input;
		if (this->ATM->Push_CapitalPools(input))
		{
			userNow->SetUserMoney(input, true);

			std::string historyHead("存款");
			auto History = GainHistoryString(historyHead, input, true);
			std::ofstream write;
			write.open("./data/" + this->userNow->Gain_User_Id() + ".txt", std::ios_base::app);
			write << History << std::endl;
			write.close();

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
		return;
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

			std::string historyHead("取款");
			auto History = GainHistoryString(historyHead, input, false);
			std::ofstream write;
			write.open("./data/" + this->userNow->Gain_User_Id() + ".txt", std::ios_base::app);
			write << History << std::endl;
			write.close();

			on_UserWithdrawalButton_click();
		}
		else
		{
			QMessageBox msgBox(QMessageBox::Question, "ERROR", "取款失败，资金池已空", QMessageBox::Ok);
			msgBox.exec();
		}
	}
}

void Client::on_ChangePasswordPushButton_click()
{
	std::string id = ui.ChangePasswordIdInput->text().toStdString();
	std::string oldPassword = ui.ChangePasswordOldPasswordInput->text().toStdString();
	std::string newPassword = ui.ChangePasswordNewPasswordInput->text().toStdString();
	std::string checkPassowrd = ui.ChangePasswordCheckPasswordInput->text().toStdString();
	if (id != userNow->Gain_User_Id())
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "修改失败，账号输入错误", QMessageBox::Ok);
		msgBox.exec();
	}
	else if(oldPassword != userNow->Gain_User_Password())
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "修改失败，原密码输入错误", QMessageBox::Ok);
		msgBox.exec();
	}
	else if(newPassword.length() < 6 || newPassword.length()>12)
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "修改失败，密码应大于5位并小于12位", QMessageBox::Ok);
		msgBox.exec();
	}
	else if(newPassword != checkPassowrd)
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "修改失败，两次密码输入错误", QMessageBox::Ok);
		msgBox.exec();
	}
	else if (userNow->Gain_User_State() == false)
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "注销失败，该用户已被东给", QMessageBox::Ok);
		msgBox.exec();
		return;
	}
	else
	{
		userNow->SetUserPassword(newPassword);
		QMessageBox msgBox(QMessageBox::Warning, "SUCCESS", "修改成功", QMessageBox::Ok);
		msgBox.exec();
	}
}

void Client::on_FreezePushButton_click()
{
	std::string inputIdCard = ui.FreezeIdcardInput->text().toStdString();
	if (inputIdCard == userNow->Gain_User_IdentityCard())
	{
		QMessageBox msgBox(QMessageBox::Warning, "Warning", "确定冻结吗？", QMessageBox::Ok | QMessageBox::Cancel);
		if (msgBox.exec() == QMessageBox::Ok)
		{
			userNow->SetUserCanUse(false);
			QMessageBox msgBoxSure(QMessageBox::Warning, "SUCCESS", "已冻结成功", QMessageBox::Ok);
			msgBoxSure.exec();
		}
	}
	else
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "冻结失败，银行卡输入错误", QMessageBox::Ok);
		msgBox.exec();
	}
}

void Client::on_userLogoutPushButton_click()
{
	std::string id = ui.userLogoutIdInput->text().toStdString();
	std::string password = ui.userLogoutPasswordInput->text().toStdString();
	if (id == userNow->Gain_User_Id() && password == userNow->Gain_User_Password())
	{
		if (userNow->Gain_User_State() == false)
		{
			QMessageBox msgBox(QMessageBox::Question, "ERROR", "注销失败，该用户已被东给", QMessageBox::Ok);
			msgBox.exec();
			return;
		}
		QMessageBox msgBox(QMessageBox::Warning, "Warning", "确定注销吗？", QMessageBox::Ok | QMessageBox::Cancel);
		if (msgBox.exec() == QMessageBox::Ok)
		{
			userNow = nullptr;
			QMessageBox msgBoxNew(QMessageBox::Warning, "SUCCESS", "注销成功", QMessageBox::Ok);
			msgBoxNew.exec();
			this->on_UserExitButton_click();
			this->close();
			ui.Menu->close();
		}
	}
	else
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "注销失败，账号或密码错误", QMessageBox::Ok);
		msgBox.exec();
	}
}

void Client::on_UserTransferSurePushButton_click()
{
	if (userNow->Gain_User_State() == false)
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "转账失败，该用户已被冻结", QMessageBox::Ok);
		msgBox.exec();
		return;
	}
	std::string ToId = ui.USerTransferToId->text().toStdString();
	std::string password = ui.USerTransferPassword->text().toStdString();
	double cash = ui.USerTransferCash->text().toDouble();
	auto data = GainUSerData();
	auto search = data;
	while (search->next!=nullptr)
	{
		search = search->next;
		if (ToId == search->data->Gain_User_Id())
		{
			if (userNow->SetUserMoney(cash, false))
			{
				if (userNow->Gain_User_Password() == password)
				{
					search->data->SetUserMoney(cash, true);
					std::stringstream stream;
					stream << this->userNow->Gain_USer_Amount();
					std::string process;
					stream >> process;
					QString output = QString::fromStdString(process);
					output = "转账成功，现有资金为" + output;
					QMessageBox msgBox(QMessageBox::Warning, "SUCCESS", output, QMessageBox::Ok);
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

					std::string historyHeadTo = "由" + userNow->Gain_User_Id() + "转账";
					auto HistoryTo = GainHistoryString(historyHeadTo, cash, true);
					std::ofstream writeHistoryTo;
					writeHistoryTo.open("./data/" + search->data->Gain_User_Id() + ".txt", std::ios_base::app);
					writeHistoryTo << HistoryTo << std::endl;
					writeHistoryTo.close();

					std::string historyHeadFrom = "向" + search->data->Gain_User_Id() + "转账";
					auto HistoryFrom = GainHistoryString(historyHeadFrom, cash, false);
					std::ofstream writeHistoryFrom;
					writeHistoryFrom.open("./data/" + userNow->Gain_User_Id() + ".txt", std::ios_base::app);
					writeHistoryFrom << HistoryFrom << std::endl;
					writeHistoryFrom.close();

				}
				else
				{
					QMessageBox msgBox(QMessageBox::Question, "ERROR", "转账失败，密码输入错误", QMessageBox::Ok);
					msgBox.exec();
				}
				return;
			}
			else
			{
				QMessageBox msgBox(QMessageBox::Question, "ERROR", "转账失败，资金输入错误", QMessageBox::Ok);
				msgBox.exec();
			}
			return;
		}
	}
	QMessageBox msgBox(QMessageBox::Question, "ERROR", "转账失败，查无此用户", QMessageBox::Ok);
	msgBox.exec();
}

void Client::on_UserHistoryPushButton_click()
{
	ui.UserHistoryList->clear();
	std::string txt = "./data/" + userNow->Gain_User_Id() + ".txt";
	std::ifstream read;
	read.open(txt, std::ios_base::in);
	if (read.is_open() == false)
	{
		QMessageBox msgBox(QMessageBox::Question, "ERROR", "数据库异常，无法打开历史记录表并读取", QMessageBox::Ok);
		msgBox.exec();
		return;
	}
	std::string input;
	while (std::getline(read, input))
	{
		ui.UserHistoryList->addItem(input.c_str());
	}
}

std::string GainHistoryString(std::string head, double cash,bool isPlus)
{
	std::string time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();

	std::string money;
	std::stringstream process;
	process << cash;
	process >> money;

	std::string key;
	if (isPlus == true)
	{
		key = head + "    +" + money + "    " + time;
	}
	else
	{
		key = head + "    -" + money + "   " + time;
	}

	return key;
}
