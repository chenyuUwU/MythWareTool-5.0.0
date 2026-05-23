#define _CRT_SECURE_NO_WARNINGS
#include <QtWidgets>
#include <MythWareTool.h>

int main(int argc, char *argv[])
{
	QApplication mwt(argc, argv);

	QFile::copy("pssuspend.exe", "C:/Windows/System32/pssuspend.exe");

	MythWareTool window;
	window.setWindowTitle("MythWare Tool");
	window.setWindowIcon(QIcon(":icon\\jiyu_icon.png"));
	window.setFixedSize(322, 425);
	window.setObjectName("mwtwindow");
	window.setStyleSheet(R"(QWidget#mwtwindow {background-color: #1e1e1e;})");

	FILE *ini;
	ini = fopen("C:\\Program Files\\mwtconfig.ini", "r");

	if (ini == NULL)
	{
		QSettings ini("C:\\Program Files\\mwtconfig.ini", QSettings::IniFormat); 
		ini.setValue("StudentMainpath/path", "C:\\Program Files (x86)\\Mythware\\极域电子教室软件 v4.0 2015 豪华版");
	}
	window.show();
	return  mwt.exec();
}