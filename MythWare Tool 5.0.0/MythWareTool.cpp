#include "MythWareTool.h"
#include <QtWidgets>
#include <windows.h>
#include <shellapi.h>
#include <QSettings>
#include <QFile>

MythWareTool::MythWareTool(QWidget *parent)
	: QWidget(parent)
{
	QStackedWidget *sta = new QStackedWidget;
	sta->setFixedSize(322, 425);
	sta->setParent(this);

	QWidget *page1 = new QWidget;
	QWidget *page2 = new QWidget;
	QWidget *page3 = new QWidget;
	QWidget *settings = new QWidget;

	page1->setParent(sta);
	page2->setParent(sta);
	page3->setParent(sta);
	settings->setParent(sta);

	QPushButton *process_stop = new QPushButton; //挂起进程按钮
	process_stop->setParent(page1);
	process_stop->setFixedSize(100, 50);
	process_stop->move(155, 150);
	process_stop->setText("挂起进程");

	QPushButton *process_resume = new QPushButton; //恢复进程按钮
	process_resume->setParent(page1);
	process_resume->setFixedSize(100, 50);
	process_resume->move(155, 230);
	process_resume->setText("恢复进程");

	sta->addWidget(page1);
	sta->addWidget(page2);
	sta->addWidget(page3);
	sta->addWidget(settings);

	QFrame *vline = new QFrame;
	vline->setParent(this);
	vline->setFrameShape(QFrame::VLine);
	vline->setGeometry(75, 0, 10, 500);
	vline->setFrameShadow(QFrame::Sunken);

	QFrame *hline = new QFrame;
	hline->setParent(page1);
	hline->setFrameShape(QFrame::HLine);
	hline->setGeometry(80, 350, 300, 10);
	hline->setFrameShadow(QFrame::Sunken);

	QPushButton *goto_page1 = new QPushButton; //切换至第一页
	goto_page1->setIcon(QIcon(":icon\\1.png"));
	goto_page1->setFixedSize(55, 55);
	goto_page1->setIconSize(QSize(55, 55));
	goto_page1->setStyleSheet("border:none");
	goto_page1->move(10, 100);
	goto_page1->setParent(this);

	QPushButton *goto_page2 = new QPushButton; //切换至第二页
	goto_page2->setIcon(QIcon(":icon\\2.png"));
	goto_page2->setIconSize(QSize(55, 55));
	goto_page2->setStyleSheet("border:none");
	goto_page2->setFixedSize(55, 55);
	goto_page2->move(10, 180);
	goto_page2->setParent(this);

	QPushButton *goto_page3 = new QPushButton; //切换至第三页
	goto_page3->setIcon(QIcon(":icon\\3.png"));
	goto_page3->setIconSize(QSize(55, 55));
	goto_page3->setStyleSheet("border:none");
	goto_page3->setFixedSize(55, 55);
	goto_page3->move(10, 260);
	goto_page3->setParent(this);

	QPushButton *goto_settings = new QPushButton; //设置按钮
	goto_settings->setIcon(QIcon(":/icon/setting.png"));
	goto_settings->setIconSize(QSize(40, 40));
	goto_settings->setParent(page1);
	goto_settings->setStyleSheet("border:none");
	goto_settings->setFixedSize(55, 55);
	goto_settings->move(270, 300);

	QLabel *re_path = new QLabel;
	re_path->setText("重设学生端路径");
	re_path->setParent(settings);
	re_path->move(100, 100);
	re_path->setFont(QFont("微软雅黑", 15, QFont::Bold));
	re_path->setStyleSheet("color:white");

	QPushButton *input_path = new QPushButton;
	input_path->setParent(settings);
	input_path->setText("确定");
	input_path->setFixedSize(80, 35);
	input_path->move(220, 180);

	QPushButton *open_ini_profile = new QPushButton;
	open_ini_profile->setParent(settings);
	open_ini_profile->setText("打开mwtconfig.ini配置文件");
	open_ini_profile->setFixedSize(200, 25);
	open_ini_profile->move(100, 240);

	QLineEdit *path = new QLineEdit;
	path->setParent(settings);
	path->setPlaceholderText("例：C:\\Mythware\\极域电子教室");
	path->setFixedWidth(200);
	path->move(100, 150);

	QPushButton *quit = new QPushButton; //关闭按钮
	quit->setIcon(QIcon(":icon\\quit.png"));
	quit->setIconSize(QSize(50, 50));
	quit->setStyleSheet("border:none");
	quit->setFixedSize(60, 60);
	quit->move(10, 360);
	quit->setParent(this);

	QPushButton *killprocess = new QPushButton; //结束进程按钮
	killprocess->setParent(page1);
	killprocess->setFixedSize(80, 35);
	killprocess->move(160, 386);
	killprocess->setText("结束");

	QPushButton *re_process = new QPushButton; //恢复进程按钮
	re_process->setParent(page1);
	re_process->setFixedSize(80, 35);
	re_process->move(240, 386);
	re_process->setText("恢复");

	QPushButton *unlocked = new QPushButton; //第二页的解锁屏幕广播最小化按钮
	unlocked->setParent(page2);
	unlocked->setFixedSize(100, 50);
	unlocked->move(150, 180);
	unlocked->setText("解锁");

	QLabel *text = new QLabel; //提示信息：挂起进程
	text->setText("挂起进程");
	text->move(160, 100);
	text->setParent(page1);
	text->setFont(QFont("微软雅黑", 16, QFont::Bold));
	text->setStyleSheet("color:white");

	QLabel *text2 = new QLabel;
	text2->setParent(page1);
	text2->move(120, 363);
	text2->setText("如果挂起进程没有反应请尝试:"); //提示信息：尝试使用结束进程的方法关掉极域电子教室
	text2->setFont(QFont("微软雅黑", 10));
	text2->setStyleSheet("color:white");

	QLabel *text3 = new QLabel;
	text3->setParent(page1);
	text3->move(100, 393);
	text3->setText("结束进程");
	text3->setFont(QFont("微软雅黑", 10, QFont::Bold));
	text3->setStyleSheet("color:white");

	QLabel *text4 = new QLabel;
	text4->setParent(page2);
	text4->setText("请在屏幕广播前解锁");
	text4->setFont(QFont("微软雅黑", 10, QFont::Bold));
	text4->setStyleSheet("color:red");
	text4->move(140, 150);

	QLabel *text5 = new QLabel;
	text5->setParent(page2);
	text5->setText("解锁屏幕广播最小化");
	text5->setFont(QFont("微软雅黑", 13, QFont::Bold));
	text5->move(123, 120);
	text5->setStyleSheet("color:white");

	QLabel *info_page_icon = new QLabel;
	info_page_icon->setParent(page3);
	info_page_icon->setPixmap(QPixmap(":/icon/jiyu_icon.png"));
	info_page_icon->setScaledContents(true);
	info_page_icon->setFixedSize(150, 150);
	info_page_icon->move(130, 50);

	QLabel *info_page_text = new QLabel;
	info_page_text->setParent(page3);
	info_page_text->setText("MythWare Tool v5.0.0");
	info_page_text->move(110, 220);
	info_page_text->setFont(QFont("微软雅黑", 13, QFont::Bold));
	info_page_text->setStyleSheet("color:white");

	QLabel *info_page_text2 = new QLabel;
	info_page_text2->setParent(page3);
	info_page_text2->setText("made by chenyuUwU");
	info_page_text2->setFont(QFont("微软雅黑", 11));
	info_page_text2->move(123, 250);
	info_page_text2->setStyleSheet("color:white");

	QPushButton *goto_github = new QPushButton;
	goto_github->setParent(page3);
	goto_github->setText("查看源码");
	goto_github->move(250, 395);
	goto_github->setFont(QFont("微软雅黑", 10));
	goto_github->setStyleSheet("border:none;color:white");

	connect(quit, &QPushButton::clicked, this, &MythWareTool::quit_clicked);
	connect(goto_page1, &QPushButton::clicked, [sta] {sta->setCurrentIndex(0); });
	connect(goto_page2, &QPushButton::clicked, [sta] {sta->setCurrentIndex(1); });
	connect(goto_page3, &QPushButton::clicked, [sta] {sta->setCurrentIndex(2); });
	connect(goto_settings, &QPushButton::clicked, [sta] {sta->setCurrentIndex(3); });
	connect(goto_github, &QPushButton::clicked, this, &MythWareTool::goto_github_pushbutton_clicked);
	connect(process_stop, &QPushButton::clicked, this, &MythWareTool::process_stop_clicked);
	connect(process_resume, &QPushButton::clicked, this, &MythWareTool::process_resume_clicked);
	connect(killprocess, &QPushButton::clicked, this, &MythWareTool::killprocess_clicked);
	connect(re_process, &QPushButton::clicked, this, &MythWareTool::re_process_clicked);
	connect(unlocked, &QPushButton::clicked, this, &MythWareTool::unlocked_clicked);
	connect(input_path, &QPushButton::clicked, [path] {QString path_in = path->text();
	QSettings ini("C:\\Program Files\\mwtconfig.ini", QSettings::IniFormat);
	ini.setValue("StudentMainpath/path", path_in); });
	connect(open_ini_profile, &QPushButton::clicked, this, &MythWareTool::open_ini_profile_clicked);
}

MythWareTool::~MythWareTool()
{}

void MythWareTool::quit_clicked()
{
	this->close();
	int msgbox;
	msgbox = mwtmsgbox("确定要退出吗?", "退出", BTN_YESNO, ICON_QUESTION);
	if (msgbox == 1)
		exit(0);
	if (msgbox == 2)
		this->show();
}

void MythWareTool::goto_github_pushbutton_clicked()
{
	ShellExecute(NULL, L"open", L"https://github.com/chenyuUwU/MythWareTool-5.0.0", NULL, NULL, SW_SHOWNORMAL);
}

void MythWareTool::process_stop_clicked()
{
	int return_check;
	return_check=system("pssuspend /accepteula -nobanner StudentMain.exe"); //挂起进程
	if (return_check != 0)
		mwtmsgbox("无法挂起进程", "错误", BTN_OK, ICON_ERROR);
}

void MythWareTool::process_resume_clicked()
{
	int return_check;
	return_check = system("pssuspend /accepteula -nobanner -r StudentMain.exe"); //恢复
	if (return_check != 0)
		mwtmsgbox("无法恢复进程", "错误", BTN_OK, ICON_ERROR);
}

void MythWareTool::killprocess_clicked()
{
	int return_check;
	return_check = system("taskkill /F /IM StudentMain.exe"); //结束进程
	if (return_check != 0)
		mwtmsgbox("无法结束进程", "错误", BTN_OK, ICON_ERROR);
}

void MythWareTool::re_process_clicked()
{
	//int start_check;
	QSettings ini("C:\\Program Files\\mwtconfig.ini", QSettings::IniFormat);
	QString path = ini.value("StudentMainpath/path").toString();
	/*
	start_check=(int)ShellExecute(NULL, L"open", path, NULL, NULL, SW_SHOW); //重启极域电子教室
	if (start_check <= 32)
		mwtmsgbox("应用程序无法启动", "错误", BTN_OK, ICON_ERROR);*/
	if (!QProcess::startDetached(path + "\\StudentMain.exe"))
		mwtmsgbox("应用程序无法启动\n原因: 路径无效,请重设学生端路径", "错误", BTN_OK, ICON_ERROR);
}

void MythWareTool::unlocked_clicked() //解锁屏幕广播最小化
{
	system("taskkill /F /IM StudentMain.exe");
	bool remove_check, copy_check;
	QSettings ini("C:\\Program Files\\mwtconfig.ini", QSettings::IniFormat);
	QString path = ini.value("StudentMainpath/path").toString();
	remove_check = QFile::remove(path+"\\LibDeskMonitor.dll");
	if (remove_check)
	{
		copy_check = QFile::copy("LibDeskMonitor.dll", path + "\\LibDeskMonitor.dll");
		if (copy_check)
			QProcess::startDetached(path + "\\StudentMain.exe");
	}
	else
		mwtmsgbox("找不到要替换的文件", "错误", BTN_OK, ICON_ERROR);
}

void MythWareTool::open_ini_profile_clicked()
{
	ShellExecute(NULL, L"open", L"C:\\Program Files\\mwtconfig.ini", NULL, NULL, SW_SHOW);
}

int MythWareTool::MythWareToolMessageBox(const char msg_text[], const char title[], int btn, int icon_type)
{
	QDialog *msg = new QDialog;
	msg->setFixedSize(300, 150);
	msg->setWindowTitle(QString(title));
	msg->setWindowIcon(QIcon(":/icon/jiyu_icon.png"));
	msg->setObjectName("mwtmessagebox");
	msg->setStyleSheet(R"(QWidget#mwtmessagebox {background-color: #1e1e1e;})");

	int returned;

	if (btn == BTN_YESNO)
	{
		QPushButton *btn_yes = new QPushButton;
		QPushButton *btn_no = new QPushButton;
		btn_yes->setParent(msg);
		btn_yes->setFixedSize(80, 40);
		btn_yes->move(120, 110);
		btn_yes->setText("是");
		btn_no->setParent(msg);
		btn_no->setFixedSize(80, 40);
		btn_no->move(220, 110);
		btn_no->setText("否");
		connect(btn_yes, &QPushButton::clicked, [msg,&returned] {returned = 1; msg->close(); });
		connect(btn_no, &QPushButton::clicked, [msg, &returned] {returned = 2; msg->close(); });
	}
	
	if (btn == BTN_OK)
	{
		QPushButton *btn_ok = new QPushButton;
		btn_ok->setParent(msg);
		btn_ok->setFixedSize(80, 40);
		btn_ok->move(220, 110);
		btn_ok->setText("确定");
		connect(btn_ok, &QPushButton::clicked, [msg, &returned] {returned = 3; msg->close(); });
	}

	if (icon_type == ICON_QUESTION)
	{
		QLabel *icon = new QLabel;
		icon->setParent(msg);
		icon->setPixmap(QPixmap(":/icon/question.png"));
		icon->setFixedSize(35, 35);
		icon->setScaledContents(true);
		icon->move(30, 33);
	}

	if (icon_type == ICON_ERROR)
	{
		QLabel *icon = new QLabel;
		icon->setParent(msg);
		icon->setPixmap(QPixmap(":/icon/error.png"));
		icon->setFixedSize(35, 35);
		icon->move(30, 33);
		icon->setScaledContents(true);
	}

	QFrame *line = new QFrame;
	line->setParent(msg);
	line->setFrameShape(QFrame::HLine);
	line->setGeometry(0, 100, 300, 10);
	line->setFrameShadow(QFrame::Sunken);

	QLabel *text = new QLabel;
	text->setText(QString(msg_text));
	text->setParent(msg);
	text->move(80, 40);
	text->setFont(QFont("微软雅黑", 10));
	text->setStyleSheet("color:white");
	msg->exec();

	delete msg;
	return returned;
}