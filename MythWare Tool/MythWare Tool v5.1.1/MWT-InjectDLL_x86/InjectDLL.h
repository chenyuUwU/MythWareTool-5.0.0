#pragma once

#ifndef INJECT_DLL
#define INJECT_DLL

#include <windows.h>
#include <Tlhelp32.h>
#include <string>
#include <iostream>
#include <Shlwapi.h>
#pragma comment(lib,"shlwapi.lib")

#define PROCESS_NOT_FOUND				0
#define INJECTDLL_SUCCESS				1

#define CREATE_SNAPSHOT_FAILED			2
#define GET_PROC_HANDLE_FAILED			3
#define CREATE_ADDRESS_FAILED			4
#define WRITE_PROC_MEM_FAILED			5

#endif