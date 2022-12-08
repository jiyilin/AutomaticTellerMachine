#include"Procedure.h"
#include <QtWidgets/QApplication>
#include<Windows.h>

int main(int argc, char *argv[])
{
    QApplication Demo(argc, argv);

    if (auto* windows=new Procedure)
    {
        windows->SetMainWindowShow();
    }
    else
    {
        MessageBox(nullptr, L"ERROR", L"程序启动失败，无法创建窗口!!!", MB_OK);
    }

    return QApplication::exec();
}
