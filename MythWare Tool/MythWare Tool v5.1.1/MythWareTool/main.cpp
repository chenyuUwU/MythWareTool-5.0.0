#include <QtWidgets>
#include "MythWareTool.h"
#include <Tlhelp32.h>
#include <fstream>
#include "WinHelperLib.h"

HINSTANCE Global_HINSTANCE = NULL;
Global_ProcessControl ProcessControl = NULL;
Global_InjectDLL InjectDLL = NULL;
Global_GetProcessInfo GetProcessInfo = NULL;
Global_UninstallDLL UninstallDLL = NULL;

int main(int argc, char *argv[])
{
	QApplication mwt(argc, argv);

	MythWareTool window;
	window.setWindowTitle("MythWare Tool");
	window.setWindowIcon(QIcon(":icon\\jiyu_icon.png"));
	window.setFixedSize(322, 425);
	window.setObjectName("mwtwindow");
	window.setStyleSheet(R"(QWidget#mwtwindow {background-color: #1e1e1e;})");

	QSettings ini("C:\\Program Files\\mwtconfig.ini", QSettings::IniFormat);
	QString InjectDllEnable = ini.value("MythWareToolSettings/InjectDllEnable").toString();
	QString Enable = "1";
	if (InjectDllEnable == Enable)
	{
		window.setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint);
	}

	Global_HINSTANCE = LoadLibrary(L"WinHelperLib_x64.dll");
	if (Global_HINSTANCE == NULL)
	{
		MythWareTool msg;
		msg.mwtmsgbox("由于\"WinHelperLib_x64.dll\"不存在，所以程序无法正常运行。重新安装可能解决此问题 ", "致命错误", BTN_OK, ICON_ERROR);
		exit(0);
	}
	ProcessControl = (Global_ProcessControl)GetProcAddress(Global_HINSTANCE, "ProcessControl");
	InjectDLL = (Global_InjectDLL)GetProcAddress(Global_HINSTANCE, "InjectDLL");
	GetProcessInfo = (Global_GetProcessInfo)GetProcAddress(Global_HINSTANCE, "GetProcessInfo");
	UninstallDLL = (Global_UninstallDLL)GetProcAddress(Global_HINSTANCE, "UninstallDLL");

	std::ifstream check_ini;
	check_ini.open("C:\\Program Files\\mwtconfig.ini");

	if (!check_ini.is_open())
	{
		QSettings ini("C:\\Program Files\\mwtconfig.ini", QSettings::IniFormat); 
		ini.setValue("StudentMainpath/path", "C:\\Program Files (x86)\\Mythware\\极域电子教室软件 v4.0 2015 豪华版");
		ini.setValue("MythWareToolSettings/InjectDllEnable", "0");
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

	DWORD Processid = GetCurrentProcessId();
	std::ofstream pid;
	pid.open("C:\\Program Files\\ProcessID.pid");
	pid << Processid;
	pid.close();

	wchar_t exePath[MAX_PATH];
	GetModuleFileName(NULL, exePath, MAX_PATH);
	std::wofstream path;
	path.open("C:\\Program Files\\exePath.path");
	path << exePath;
	path.close();

	QFile::copy("MwtInjectDLL_x64.dll", "C:\\Program Files\\MwtInjectDLL_x64.dll");

	MythWareTool msg;
	if (!check_process)
	{
		msg.mwtmsgbox("学生端主程序进程不存在 这可能导致部分功能无法使用", "警告", BTN_OK, ICON_WARNING);
	}

	window.show();
	return  mwt.exec();
}