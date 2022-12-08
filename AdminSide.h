#pragma once

#ifndef AdminSide_H
#define AdminSide_H


#include <QMainWindow>

#include "ui_AdminSide.h"

class AdminSide : public QMainWindow
{
	Q_OBJECT

public:
	AdminSide(QWidget* parent = nullptr);
	~AdminSide();

private:
	Ui::AdminSideClass ui;
};

#endif // !AdminSide_H
