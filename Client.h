﻿#pragma once

#ifndef Client_H
#define Client_H

#include <QMainWindow>

#include "ui_Client.h"
#include"User.h"
#include"Machine.h"

class Client : public QMainWindow
{
	Q_OBJECT

public:
	Client(QWidget* parent = nullptr);
	~Client();

private slots:

	void on_RegisteredPushButton_click();

	void on_LoadSureButton_click();

	void on_UserExitButton_click();

	void on_WithdrawalPushButton_click();

	void on_UserDeposit_click();

	void on_UserWithdrawalButton_click();

	void on_DepositButton_click();

	void on_ChangePasswordPushButton_click();
private:
	Ui::ClientClass ui;
	Machine* ATM;
	User* userNow;
};

#endif // !Client_H