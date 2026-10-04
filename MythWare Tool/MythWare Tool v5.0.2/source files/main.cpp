#define _CRT_SECURE_NO_WARNINGS
#include <QtWidgets>
#include "MythWareTool.h"
#include <windows.h>
#include <Tlhelp32.h>
#include <fstream>

int main(int argc, char *argv[])
{
	QApplication mwt(argc, argv);

	MythWareTool window;
	window.setWindowTitle("MythWare Tool");
	window.setWindowIcon(QIcon(":icon\\jiyu_icon.png"));
	window.setFixedSize(322, 425);
	window.setObjectName("mwtwindow");
	window.setStyleSheet(R"(QWidget#mwtwindow {background-color: #1e1e1e;})");

	std::ifstream check_ini;
	check_ini.open("C:\\Program Files\\mwtconfig.ini");

	if (!check_ini.is_open())
	{
		QSettings ini("C:\\Program Files\\mwtconfig.ini", QSettings::IniFormat); 
		ini.setValue("StudentMainpath/path", "C:\\Program Files (x86)\\Mythware\\极域电子教室软件 v4.0 2015 豪华版");
	}
	check_ini.close();

	bool check_process = false;
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 processentry32;
	processentry32.dwSize = sizeof(PROCESSENTRY32);
	BOOL P32ret = Process32First(snap, &processentry32);
	while (P32ret)
	{
		if (wcscmp(processentry32.szExeFile, L"StudentMain.exe") == 0)
		{
			check_process = true;
		}
		P32ret = Process32Next(snap, &processentry32);
	}
	CloseHandle(snap);

	MythWareTool msg;
	if (!check_process)
	{
		msg.mwtmsgbox("学生端主程序进程不存在 这可能导致部分功能无法使用", "警告", BTN_OK, ICON_WARNING);
	}

	window.show();
	return  mwt.exec();
}