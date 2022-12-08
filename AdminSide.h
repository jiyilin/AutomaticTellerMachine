#pragma once

#include <QMainWindow>
#include "ui_AdminSide.h"

class AdminSide : public QMainWindow
{
	Q_OBJECT

public:
	AdminSide(QWidget *parent = nullptr);
	~AdminSide();

private:
	Ui::AdminSideClass ui;
};
