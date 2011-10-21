#pragma once

#include <QtGui/QMainWindow>
#include <QMessageBox>
#include "ui_MainForm.h"
#include "DataController/DataController.h"
#include "Mvd/MvdDataModel.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \name This class is the main window of the application.
class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	MainForm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainForm();

protected slots:
	/// \name UI logic.
	//@{
	void onIpAddressLineEditTextChanged(const QString& text) {m_dataController->onIpAddressLineEditTextChanged(text.toStdString());}
	void onPortLineEditTextChanged(const QString& text) {m_dataController->onPortLineEditTextChanged(text.toInt());}

	void onStartButtonClicked() {m_dataController->onStartButtonClicked();}
	void onStopButtonClicked() {m_dataController->onStopButtonClicked();}
	void onSettingsButtonClicked() {m_areSettingsVisible = !m_areSettingsVisible; ui.m_pathsView->setVisible(m_areSettingsVisible);}
	//@}

protected:
	/// \name UI.
	//@{
	Ui::MainFormClass ui;

	MvdDataModel m_mvdModel;
	//@}

	DataController* m_dataController;

	/// \name UI logic.
	//@{
	bool m_areSettingsVisible;
	//@}
};

} // namespace SK.