#include "MainForm.h"
#include <QtGui/QApplication>
#include "DataBase/DataBase.h"

int main(int argc, char *argv[])
{
	SK::DataBase::CreateInstance();

	QApplication a(argc, argv);
	SK::MainForm w;
	w.show();
	return a.exec();

	SK::DataBase::DestroyInstance();
}