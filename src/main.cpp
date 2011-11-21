#include "MainForm.h"
#include <QtGui/QApplication>
#include "AppDataBase.h"
#include "DataController/DataController.h"

//////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	SK::MainForm mainForm;

	SK::AppDataBase::CreateInstance();
	SK::DataController::CreateInstance();

	mainForm.setup();

	SK::AppDataBase::GetInstance()->setMainForm(&mainForm);

	mainForm.show();
	app.exec();

	SK::DataController::DestroyInstance();
	SK::DataBase::DestroyInstance();
}