#include "IisuOscBridge.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	IisuOscBridge w;
	w.show();
	return a.exec();
}
