#include "MainForm.h"
#include <QtGui/QApplication>
#include "DataBase/DataBase.h"
#include "DataBase/DataController.h"

int main(int argc, char *argv[])
{
	SK::DataBase::CreateInstance();
	SK::DataController::CreateInstance();

	QApplication a(argc, argv);
	SK::MainForm mainForm;
	mainForm.show();
	a.exec();

	SK::DataController::DestroyInstance();
	SK::DataBase::DestroyInstance();
}