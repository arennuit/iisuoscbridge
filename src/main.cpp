#include "MainForm.h"
#include <QtGui/QApplication>
#include "AppDataBase.h"
#include "DataController/DataController.h"

//////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setApplicationName("IisuOscBridge");
	app.setOrganizationName("SoftKinetic");
	app.setOrganizationDomain("sofkinetic.com");

	// The main form needs to be existing before the database and data controller are instantiated. And the data base
	// and controller need to be existing before the main form is setup. Hence we separated the form's instantiation
	// and setup.
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