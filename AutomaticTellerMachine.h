#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AutomaticTellerMachine.h"
#include"Client.h"
#include"AdminSide.h"

class AutomaticTellerMachine : public QMainWindow
{
    Q_OBJECT

public:
    AutomaticTellerMachine(QWidget *parent = nullptr);
    ~AutomaticTellerMachine();

private slots:
    void on_ClientButton_click();

    void on_AdminSideButton_click();

private:
    Ui::AutomaticTellerMachineClass ui;
    Client* client;
    AdminSide* adminSide;
};
