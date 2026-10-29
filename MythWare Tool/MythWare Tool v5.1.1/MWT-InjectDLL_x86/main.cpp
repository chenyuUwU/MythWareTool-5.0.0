#include "InjectDLL.h"

int main(int argc, wchar_t*argv[])
{
	DWORD processid = NULL;
	HANDLE SnapProc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (SnapProc == INVALID_HANDLE_VALUE)
	{
		return CREATE_SNAPSHOT_FAILED;
	}
	PROCESSENTRY32 processentry32;
	processentry32.dwSize = sizeof(PROCESSENTRY32);
	BOOL p32ret = Process32First(SnapProc, &processentry32);

	while (p32ret)
	{
		if (_wcsicmp(L"StudentMain.exe", processentry32.szExeFile) == 0)
		{
			processid = processentry32.th32ProcessID;
		}
		p32ret = Process32Next(SnapProc, &processentry32);
	}
	CloseHandle(SnapProc);

	if (processid == NULL)
	{
		return PROCESS_NOT_FOUND;
	}
	
	HANDLE OpenProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processid);
	if (!OpenProc)
	{
		return GET_PROC_HANDLE_FAILED;
	}
	
	std::wstring DllBaseName = L"\\HSS_x86.dll";
	wchar_t exename[MAX_PATH];
	GetModuleFileName(NULL, exename, MAX_PATH);
	PathRemoveFileSpec(exename);
	std::wstring WSExepath = exename;
	std::wstring DLLDir = WSExepath + DllBaseName;

	SIZE_T DllDirSize = (wcslen(DLLDir.c_str()) + 1) * sizeof(wchar_t);
	LPVOID CreateAddress = VirtualAllocEx(OpenProc, NULL, DllDirSize, MEM_COMMIT, PAGE_READWRITE);
	if (!CreateAddress)
	{
		return CREATE_ADDRESS_FAILED;
	}

	BOOL WriteProcMem = WriteProcessMemory(OpenProc, CreateAddress, DLLDir.c_str(), DllDirSize, NULL);
	if (!WriteProcMem)
	{
		return WRITE_PROC_MEM_FAILED;
	}

	HANDLE hthread = CreateRemoteThread(OpenProc, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, CreateAddress, 0, NULL);
	WaitForSingleObject(hthread, -1);
	VirtualFreeEx(OpenProc, CreateAddress, 0, MEM_RELEASE);
	CloseHandle(OpenProc);
	CloseHandle(hthread);
	return INJECTDLL_SUCCESS;
}