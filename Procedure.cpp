#include "Procedure.h"

Procedure::Procedure()
{
	mainWindow = new AutomaticTellerMachine;
}

void Procedure::SetMainWindowShow()
{
	this->mainWindow->show();
}

void Procedure::SetMainWindowHide()
{
	this->mainWindow->hide();
}

bool Procedure::DatabaseDetection()
{
	if (GetFileAttributesA("data") == INVALID_FILE_ATTRIBUTES)
	{
		if (system("md data") == 0)
		{
			MessageBox(nullptr, L"程序未添加数据库，已创建新数据库", L"Waring", MB_OK);
		}
		else
		{
			MessageBox(nullptr, L"程序启动失败，数据库未通过检测", L"ERROR", MB_OK);
			return false;
		}
	}
	return true;
}

bool Procedure::EngineStarts()
{
	if (this->DatabaseDetection())
	{
		this->SetMainWindowShow();
		return true;
	}
	else
	{
		return false;
	}
}
