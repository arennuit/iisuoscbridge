#pragma once

#include <QtGui/QMainWindow>
#include <QMessageBox>
#include "ui_MainForm.h"
#include "DataController/DataController.h"
#include "Mvd/MvdDataModel.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \brief This class is the main window of the application.
class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	MainForm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainForm();

	/// \name App -> UI logic.
	//@{
	void onOscPacketSizeChanged(uint oscPacketSize) {ui.m_oscPacketSizeLineEdit->setText(QString::number(oscPacketSize));}
	//@}

protected slots:

	/// \name UI -> app logic.
	//@{
	void onIpAddressLineEditTextChanged(const QString& text) {m_dataController->onIpAddressLineEditTextChanged(text.toStdString());}
	void onPortLineEditTextChanged(const QString& text) {m_dataController->onPortLineEditTextChanged(text.toInt());}

	void onStartStopToggleButtonClicked() {m_dataController->onStartStopToggleButtonClicked();}
	void onSettingsButtonClicked() {m_areSettingsVisible = !m_areSettingsVisible; ui.m_tabs->setVisible(m_areSettingsVisible);}
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