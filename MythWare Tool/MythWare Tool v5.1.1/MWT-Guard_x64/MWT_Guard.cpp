#include <windows.h>
#include <TlHelp32.h>
#include <fstream>
#include <string>
#include <shellapi.h>

DWORD WINAPI MWT_Guard(LPVOID lpParam)
{
	while (true)
	{
		DWORD Processid = NULL;
		std::wstring path;

		std::ifstream pid;
		pid.open("C:\\Program Files\\ProcessID.pid");
		if (!pid.is_open())
		{
			MessageBox(NULL, L"读取pid文件失败", L"错误", MB_ICONERROR);
		}
		else
		{
			pid >> Processid;
			pid.close();
		}

		std::wifstream exepath;
		exepath.open("C:\\Program Files\\exePath.path");
		if (!exepath.is_open())
		{
			MessageBox(NULL, L"读取路径文件失败", L"错误", MB_ICONERROR);
		}
		else
		{
			getline(exepath, path);
			exepath.close();
		}
		HANDLE openproc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, NULL, Processid);
		DWORD exitcode;

		if (GetExitCodeProcess(openproc, &exitcode))
		{
			if (exitcode != STILL_ACTIVE)
			{
				CloseHandle(openproc);
				ShellExecute(NULL, L"open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
			}
		}
		Sleep(1000);
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		CreateThread(NULL, 0, MWT_Guard, NULL, 0, NULL);
	}
	return TRUE;
}