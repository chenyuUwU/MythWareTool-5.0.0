#pragma once

#include <QWidget>

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
	bool mwtProcessControl(const wchar_t* exename, int controlmode);
	
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

#ifndef MWT_PROCESS_CONTROL
#define MWT_PROCESS_CONTROL

#define MWT_SUSPEND_PROCESS          11
#define MWT_RESUME_PROCESS           12 
#define MWT_TERMINATE_PROCESS        13

#endif

#ifndef MWT_VER
#define MWT_VER

#define MWT_VERSION "MythWare Tool v5.0.2"
#endif