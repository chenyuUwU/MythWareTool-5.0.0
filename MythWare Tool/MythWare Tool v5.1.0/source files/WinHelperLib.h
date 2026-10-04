#pragma once

#ifndef WINHELPERLIB
#define WINHELPERLIB

#include <windows.h>
#include <Tlhelp32.h>
#include <psapi.h>
#include <fstream>
#include <iostream>

#define DLL_EXPORT extern "C" _declspec(dllexport)

DLL_EXPORT DWORD ProcessControl(LPCWSTR exename, DWORD controlmode);
DLL_EXPORT DWORD GetProcessInfo(LPCWSTR exename, DWORD ShowProcInfo, LPCWSTR FullPath, LPDWORD lpPidOut);
DLL_EXPORT BOOL InjectDLL(LPCWSTR DLLdir, DWORD pid);
DLL_EXPORT BOOL UninstallDLL(LPCWSTR dllname, DWORD pid);

#endif

#ifndef WHL_PROCESS_CONTROL
#define WHL_PROCESS_CONTROL

#define WHL_SUSPEND_PROCESS					1
#define WHL_RESUME_PROCESS					2 
#define WHL_TERMINATE_PROCESS				3

#define WHL_GET_PROC_HANDLE_FAILED          4
#define WHL_TERMINATE_PROC_FAILED           5
#define WHL_SUSPEND_PROC_FAILED             6
#define WHL_RESUME_PROC_FAILED              7
#define WHL_CREATE_SNAPSHOT_FAILED			8

#define SHOW_PROC_INFO					    9
#define SHOW_PROC_INFO_FAILED				10

#define WHL_SUCCESS						    1
#define WHL_FAILED							0

#endif