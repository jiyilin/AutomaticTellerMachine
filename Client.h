#pragma once

#ifndef Client_H
#define Client_H

#include <QMainWindow>

#include "ui_Client.h"

class Client : public QMainWindow
{
	Q_OBJECT

public:
	Client(QWidget* parent = nullptr);
	~Client();

private slots:

	void on_RegisteredPushButton_click();

private:
	Ui::ClientClass ui;
};

#endif // !Client_H