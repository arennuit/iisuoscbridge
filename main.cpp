#include "MainForm.h"
#include <QtGui/QApplication>
#include "DataBase/DataBase.h"

int main(int argc, char *argv[])
{
	SK::DataBase::CreateInstance();

	QApplication a(argc, argv);
	SK::MainForm mainForm;
	mainForm.show();
	a.exec();

	SK::DataBase::DestroyInstance();
}