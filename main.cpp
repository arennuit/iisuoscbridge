#include "MainForm.h"
#include <QtGui/QApplication>
#include "DataModel.h"

int main(int argc, char *argv[])
{
	SK::DataModel::CreateInstance();

	QApplication a(argc, argv);
	SK::MainForm w;
	w.show();
	return a.exec();

	SK::DataModel::DestroyInstance();
}