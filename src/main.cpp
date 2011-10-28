#include "MainForm.h"
#include <QtGui/QApplication>
#include "AppDataBase.h"
#include "DataController/DataController.h"

//////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	SK::AppDataBase::CreateInstance();
	SK::DataController::CreateInstance();

	QApplication app(argc, argv);
	SK::MainForm mainForm;

	mainForm.show();
	app.exec();

	SK::DataController::DestroyInstance();
	SK::DataBase::DestroyInstance();
}