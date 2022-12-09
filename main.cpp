#include"Procedure.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication Demo(argc, argv);

    if (auto* windows=new Procedure)
    {
        if (windows->EngineStarts())
        {
            return QApplication::exec();
        }
    }
    else
    {
        MessageBox(nullptr, L"程序启动失败，无法创建窗口!!!", L"ERROR", MB_OK);
    }
    return 0;
}