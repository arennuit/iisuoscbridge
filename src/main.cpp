#include "MainForm.h"
#include <QtGui/QApplication>
#include "AppDataBase.h"
#include "AppDataController.h"

//////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	// Create application and splash screen.
	QApplication app(argc, argv);
	app.setApplicationName("iisuOscBridge");
	app.setOrganizationName("SoftKinetic");
	app.setOrganizationDomain("sofkinetic.com");

	QSplashScreen splashScreen;
	splashScreen.setPixmap(QPixmap("SplashScreen.png"));
	splashScreen.show();

	// The main form needs to be existing before the database and the data controller are instantiated. And the
	// data base and controller need to be existing before the main form is setup. Hence we separated the form's
	// instantiation and setup.
	SK::MainForm mainForm;
	SK::AppDataBase* dataBase = SK::AppDataBase::CreateInstance();
	SK::AppDataController* dataController = SK::AppDataController::CreateInstance();

	dataBase->setDataController(dataController);
	dataController->setMainForm(&mainForm);
	mainForm.setup();

	// Load project.
	// NOTE: use the project in argument, or the last opened project or reset.
	std::string filePath;
	if (argc == 1)
	{
		QSettings settings;
		filePath = settings.value("CurrentFilePath").toString().toStdString();
	}
	else
	{
		filePath = std::string(argv[1]);
	}

	if (filePath == "")
		dataController->resetProject();
	else
		dataController->loadProjectFromFile(filePath);

	// Start application.
	splashScreen.finish(&mainForm);

	mainForm.show();
	app.exec();

	SK::DataController::DestroyInstance();
	SK::DataBase::DestroyInstance();
}