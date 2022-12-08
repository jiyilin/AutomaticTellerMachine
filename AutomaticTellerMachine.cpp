#include "AutomaticTellerMachine.h"

AutomaticTellerMachine::AutomaticTellerMachine(QWidget *parent): QMainWindow(parent){
    ui.setupUi(this);
    client = new Client;
}

AutomaticTellerMachine::~AutomaticTellerMachine() = default;

void AutomaticTellerMachine::on_ExitButton_click(){
    this->hide();
}

void AutomaticTellerMachine::on_ClientButton_click(){
    client->show();
}
