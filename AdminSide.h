#pragma once

#ifndef AdminSide_H
#define AdminSide_H


#include <QMainWindow>
#include<qmessagebox.h>

#include "ui_AdminSide.h"
#include"Administrator.h"
#include"Machine.h"

class AdminSide : public QMainWindow
{
	Q_OBJECT

public:
	AdminSide(QWidget* parent = nullptr);
	~AdminSide();
private slots:
	void on_SignButton_click();

private:
	Ui::AdminSideClass ui;
	Administrator administrator;
	Machine* ATM;
};

#endif // !AdminSide_H
