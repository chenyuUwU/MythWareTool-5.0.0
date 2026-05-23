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
};

#ifndef MWT_MSG_BOX
#define MWT_MSG_BOX
#define mwtmsgbox MythWareToolMessageBox

#define BTN_YESNO       1
#define BTN_OK          2

#define ICON_QUESTION   3
#define ICON_ERROR      4
#define ICON_NULL       5

#endif
