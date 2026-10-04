#include "WinHelperLib.h"

DWORD ProcessControl(LPCWSTR exename, DWORD controlmode)
{
	DWORD processpid = 0;
	HANDLE ProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (ProcSnap == INVALID_HANDLE_VALUE)
	{
		return WHL_CREATE_SNAPSHOT_FAILED;
	}
	PROCESSENTRY32 procentry32;
	procentry32.dwSize = sizeof(PROCESSENTRY32);
	BOOL P32ret = Process32First(ProcSnap, &procentry32);

	while (P32ret)
	{
		if (_wcsicmp(exename, procentry32.szExeFile) == 0)
		{
			processpid = procentry32.th32ProcessID;
		}
		P32ret = Process32Next(ProcSnap, &procentry32);
	}
	CloseHandle(ProcSnap);

	if (controlmode == WHL_TERMINATE_PROCESS)
	{
		HANDLE stop_process = OpenProcess(PROCESS_TERMINATE, FALSE, processpid);
		if (!stop_process)
		{
			return WHL_GET_PROC_HANDLE_FAILED;
		}
		else
		{
			if (TerminateProcess(stop_process, 0) == 0)
			{
				CloseHandle(stop_process);
				return WHL_TERMINATE_PROC_FAILED;
			}
			CloseHandle(stop_process);
			return WHL_SUCCESS;
		}
	}

	if (controlmode == WHL_SUSPEND_PROCESS)
	{
		HANDLE TSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, processpid);
		if (TSnap == INVALID_HANDLE_VALUE)
		{
			return WHL_CREATE_SNAPSHOT_FAILED;
		}
		THREADENTRY32 threadentry32;
		threadentry32.dwSize = sizeof(THREADENTRY32);
		BOOL T32ret = Thread32First(TSnap, &threadentry32);

		while (T32ret)
		{
			if (threadentry32.th32OwnerProcessID == processpid)
			{
				HANDLE suspend = OpenThread(THREAD_SUSPEND_RESUME, FALSE, threadentry32.th32ThreadID);
				if (!suspend)
				{
					return WHL_GET_PROC_HANDLE_FAILED;
				}
				else
				{
					if (SuspendThread(suspend) == -1)
					{
						CloseHandle(suspend);
						return WHL_SUSPEND_PROC_FAILED;
					}
					CloseHandle(suspend);
				}
			}
			T32ret = Thread32Next(TSnap, &threadentry32);
		}
		return WHL_SUCCESS;
	}

	if (controlmode == WHL_RESUME_PROCESS)
	{
		HANDLE TSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, processpid);
		if (TSnap == INVALID_HANDLE_VALUE)
		{
			return WHL_CREATE_SNAPSHOT_FAILED;
		}
		THREADENTRY32 threadentry32;
		threadentry32.dwSize = sizeof(THREADENTRY32);
		BOOL T32ret = Thread32First(TSnap, &threadentry32);

		while (T32ret)
		{
			if (threadentry32.th32OwnerProcessID == processpid)
			{
				HANDLE suspend = OpenThread(THREAD_SUSPEND_RESUME, FALSE, threadentry32.th32ThreadID);
				if (!suspend)
				{
					return WHL_GET_PROC_HANDLE_FAILED;
				}
				else
				{
					if (ResumeThread(suspend) == -1)
					{
						CloseHandle(suspend);
						return WHL_SUSPEND_PROC_FAILED;
					}
					CloseHandle(suspend);
				}
			}
			T32ret = Thread32Next(TSnap, &threadentry32);
		}
		return WHL_SUCCESS;
	}
}

DWORD GetProcessInfo(LPCWSTR exename, DWORD ShowProcInfo, LPCWSTR FullPath, LPDWORD lpPidOut)
{
	DWORD processid = NULL;

	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!hsnap)
	{
		return WHL_CREATE_SNAPSHOT_FAILED;
	}
	PROCESSENTRY32 procentry32;
	procentry32.dwSize = sizeof(PROCESSENTRY32);

	if (ShowProcInfo == SHOW_PROC_INFO && exename== NULL)
	{
		BOOL p32ret = Process32First(hsnap, &procentry32);
		std::wofstream clear;
		clear.open(FullPath, std::ios::out);
		clear.close();
		while (p32ret)
		{
			std::wofstream procinfo;
			procinfo.open(FullPath,std::ios::app);
			procinfo << "ProcName:\t" << procentry32.szExeFile << std::endl;
			procinfo << "ProcPid:\t" << procentry32.th32ProcessID << std::endl;
			procinfo << "--------------------------------------------------------" << std::endl;
			if (!procinfo.good())
			{
				CloseHandle(hsnap);
				return SHOW_PROC_INFO_FAILED;
			}
			p32ret = Process32Next(hsnap, &procentry32);
		}
		CloseHandle(hsnap);
		return WHL_SUCCESS;
	}

	BOOL p32ret = Process32First(hsnap, &procentry32);

	while (p32ret)
	{
		if (_wcsicmp(exename, procentry32.szExeFile) == 0)
		{
			if (lpPidOut != NULL)
			{
				*lpPidOut = procentry32.th32ProcessID;
			}

			processid= procentry32.th32ProcessID;
			
			if (ShowProcInfo == SHOW_PROC_INFO)
			{
				std::wofstream clear;
				clear.open(FullPath, std::ios::out);
				clear.close();

				std::wofstream procinfo;
				procinfo.open(FullPath, std::ios::app);
				procinfo << "ProcName:\t" << procentry32.szExeFile << std::endl;
				procinfo << "ProcPid:\t" << procentry32.th32ProcessID << std::endl;
				procinfo << "--------------------------------------------------------" << std::endl;
				if (!procinfo.good())
				{
					CloseHandle(hsnap);
					return SHOW_PROC_INFO_FAILED;
				}
				p32ret = Process32Next(hsnap, &procentry32);
			}
		}

		p32ret = Process32Next(hsnap, &procentry32);
	}

	HANDLE hproc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);
	DWORD exitcode;
	GetExitCodeProcess(hproc, &exitcode);
	if (exitcode == STILL_ACTIVE)
	{
		CloseHandle(hproc);
		CloseHandle(hsnap);
		return WHL_SUCCESS;
	}
	else
	{
		CloseHandle(hproc);
		CloseHandle(hsnap);
		return WHL_FAILED;
	}
}

BOOL InjectDLL(LPCWSTR DLLdir, DWORD pid)
{
	HANDLE OpenProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (!OpenProc)
	{
		return FALSE;
	}
	SIZE_T dirsize = (wcslen(DLLdir) + 1) * sizeof(wchar_t);
	LPVOID CreateMem = VirtualAllocEx(OpenProc, NULL, dirsize, MEM_COMMIT, PAGE_READWRITE);
	if (!CreateMem || !WriteProcessMemory(OpenProc, CreateMem, DLLdir, dirsize, NULL))
	{
		return FALSE;
	}
	HANDLE CreateThread = CreateRemoteThread(OpenProc, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, CreateMem, 0, NULL);
	if (!CreateThread)
	{
		return FALSE;
	}
	WaitForSingleObject(CreateThread, -1);
	VirtualFreeEx(OpenProc, CreateMem, 0, MEM_RELEASE);
	CloseHandle(OpenProc);
	CloseHandle(CreateThread);
	return TRUE;
}

BOOL UninstallDLL(LPCWSTR dllname, DWORD pid)
{
	HANDLE hproc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	HMODULE hmod[1024];
	DWORD modulesize;
	if (!EnumProcessModules(hproc, hmod, sizeof(hmod), &modulesize))
	{
		return FALSE;
	}

	DWORD modules = modulesize / sizeof(HMODULE);
	HMODULE dlladdress = NULL;

	for (DWORD i = 0; i < modules; i++)
	{
		wchar_t modname[MAX_PATH];
		if (GetModuleBaseName(hproc, hmod[i], modname, MAX_PATH))
		{
			if (_wcsicmp(modname, dllname) == 0)
			{
				dlladdress = hmod[i];
				break;
			}
		}
	}

	HANDLE hthread = CreateRemoteThread(hproc, NULL, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, dlladdress, 0, NULL);
	WaitForSingleObject(hthread, -1);
	CloseHandle(hproc);
	CloseHandle(hthread);
	return TRUE;
}