#include "MainForm.h"
#include <QtGui/QApplication>
#include "DataBase/DataBase.h"

int main(int argc, char *argv[])
{
	SK::DataBase::CreateInstance();
	SK::MvdController::CreateInstance();

	QApplication a(argc, argv);
	SK::MainForm mainForm;
	mainForm.show();
	a.exec();

	SK::MvdController::DestroyInstance();
	SK::DataBase::DestroyInstance();
}