#pragma once

#include <QtGui/QMainWindow>
#include <QMessageBox>
#include "ui_MainForm.h"
#include "FormFiles/SettingsForm.h"
#include "DataController/DataController.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \name This class is the main window of the application.
class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	MainForm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainForm() {}

protected slots:
	void onIpAddressLineEditTextChanged(const QString& text) {m_mvdController->onIpAddressLineEditTextChanged(text.toStdString());}
	void onPortLineEditTextChanged(const QString& text) {m_mvdController->onPortLineEditTextChanged(text.toInt());}

	void onStartButtonClicked() {m_mvdController->onStartButtonClicked();}
	void onStopButtonClicked();
	void onSettingsButtonClicked();

protected:
	/// \name UI.
	//@{
	Ui::MainFormClass ui;
	SettingsForm m_settingsForm;
	//@}

	DataController* m_mvdController;
};

} // namespace SK.