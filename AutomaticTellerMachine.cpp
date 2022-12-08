#include "AutomaticTellerMachine.h"

AutomaticTellerMachine::AutomaticTellerMachine(QWidget *parent): QMainWindow(parent){
    ui.setupUi(this);
    client = new Client;
    adminSide = new AdminSide;
}

AutomaticTellerMachine::~AutomaticTellerMachine() = default;

void AutomaticTellerMachine::on_ClientButton_click(){
    client->show();
}

void AutomaticTellerMachine::on_AdminSideButton_click(){
    adminSide->show();
}
