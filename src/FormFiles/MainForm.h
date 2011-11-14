#pragma once

#include <QtGui/QMainWindow>
#include <QMainWindow>
#include "ui_MainForm.h"
#include "DataController/DataController.h"
#include "Mvd/MvdDataModel.h"

namespace SK
{

class DataBase;

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
	void onIsObservationOnChanged(bool isObservationOn);
	void onOscPacketSizeChanged(uint oscPacketSize) {ui.m_oscPacketSizeLineEdit->setText(QString::number(oscPacketSize));}
	//@}

protected slots:

	/// \name UI -> app logic.
	//@{
	void onIpAddressLineEditTextChanged(const QString& text) {m_dataController->onIpAddressLineEditTextChanged(text.toStdString());}
	void onPortLineEditTextChanged(const QString& text) {m_dataController->onPortLineEditTextChanged(text.toInt());}
	void onIidFilePathLineEditTextChanged(const QString& text) {m_dataController->onIidFilePathLineEditTextChanged(text.toStdString());}

	void onStartStopToggleButtonClicked();

	void onFoldAndNameJointsCheckBoxClicked() {m_dataController->onFoldAndNameJointsCheckBoxClicked(ui.m_foldAndNameJointsCheckBox->isChecked());}
	//@}

protected:
	/// \name UI.
	//@{
	Ui::MainFormClass ui;

	MvdDataModel m_mvdModel;
	//@}

	DataBase* m_dataBase;
	DataController* m_dataController;
};

} // namespace SK.