#pragma once

#include <QWidget>
#include <windows.h>

class MythWareTool  : public QWidget
{
	Q_OBJECT

public:
	MythWareTool(QWidget *parent=nullptr);
	~MythWareTool();

public slots:
	void quit_clicked();
	void goto_github_pushbutton_clicked();
	void process_stop_clicked();
	void process_resume_clicked();
	void killprocess_clicked();
	void re_process_clicked();
	void unlocked_clicked();
	void open_ini_profile_clicked();
	int MythWareToolMessageBox(const char msg_text[], const char title[], int btn, int icon_type);
	bool replacefile(QString targetdir, QString filename);
	void injectDLL_clicked();
};

#ifndef MWT_MSG_BOX
#define MWT_MSG_BOX
#define mwtmsgbox MythWareToolMessageBox

#define BTN_YESNO       1
#define BTN_OK          2

#define ICON_QUESTION   3
#define ICON_ERROR      4
#define ICON_NULL       5
#define ICON_WARNING    6
#endif

#ifndef MWT_VER
#define MWT_VER

#define MWT_VERSION "MythWare Tool v5.1.0"
#endif

#ifndef LOAD_DLL
#define LOAD_DLL

extern HINSTANCE Global_HINSTANCE;
typedef DWORD(*Global_ProcessControl)(const wchar_t *exename, int controlmode);
typedef BOOL(*Global_InjectDLL)(const wchar_t *DLLdir, DWORD pid);
typedef DWORD(*Global_GetProcessInfo)(LPCWSTR exename, DWORD ShowProcInfo, LPCWSTR FullPath, LPDWORD lpPidOut);
typedef DWORD(*Global_UninstallDLL)(const wchar_t *dllname, DWORD pid);
extern Global_ProcessControl ProcessControl;
extern Global_InjectDLL InjectDLL;
extern Global_GetProcessInfo GetProcessInfo;
extern Global_UninstallDLL UninstallDLL;
#endif