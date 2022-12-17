#pragma once

#ifndef AdminSide_H
#define AdminSide_H

#include <QMainWindow>
#include <qmessagebox.h>

#include "ui_AdminSide.h"
#include "Administrator.h"
#include "Machine.h"

class AdminSide : public QMainWindow
{
	Q_OBJECT

public:
	AdminSide(QWidget *parent = nullptr);
	~AdminSide();
private slots:
	void on_SignButton_click();

	void on_FundFillingButton_click();

	void on_PoolEmptyButton_click();

	void on_UserQueriesPushButton_click();

	void on_UserFreezesSuerPushButton_click();

	void on_UserUnFreezePushButton_click();

	void on_UserLogsOffSurePushButton_click();

	void on_FundsTrackingPushButton_click();

private:
	Ui::AdminSideClass ui;
	Administrator administrator;
	Machine *ATM;
};

#endif // !AdminSide_H
