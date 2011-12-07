#pragma once

#include <QtGui/QMainWindow>
#include <QMainWindow>
#include <QFileDialog>
#include "ui_MainForm.h"
#include "DataController/DataController.h"
#include "Mvd/MvdDataModel.h"
#include "Mvd/MvdPathDelegate.h"

namespace SK
{

class DataBase;

//////////////////////////////////////////////////////////////////////////
/// \brief This class allows to send its content towards the log window.
class StreamBufToLogEdit : public std::basic_streambuf<char, std::char_traits<char> >
{
typedef	std::basic_streambuf<char, std::char_traits<char> >::int_type int_type;

public:
	StreamBufToLogEdit() : std::basic_streambuf<char, std::char_traits<char> >() {}

	void setTargetTextEdit(QPlainTextEdit* targetEdit) {assert(targetEdit); m_targetEdit = targetEdit;}

protected:
	int_type overflow(int_type c)
	{
		assert(m_targetEdit);

		m_targetEdit->insertPlainText(QString(c));

		return c;
	}

	QPlainTextEdit* m_targetEdit;
};

//////////////////////////////////////////////////////////////////////////
/// \brief This class is the main window of the application.
class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	MainForm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainForm();

	void setup();

	/// \name App -> UI logic.
	//@{
	void onIsObservationOnChanged(bool isObservationOn);
	void onOscPacketSizeChanged(uint oscPacketSize) {ui.m_oscPacketSizeLineEdit->setText(QString::number(oscPacketSize));}
	//@}

protected slots:

	/// \name UI -> app logic.
	//@{
	void onIpAddressEditEditingFinished() {m_dataController->onIpAddressEditEditingFinished(ui.m_ipAddressEdit->text().toStdString());}
	void onPortEditEditingFinished() {m_dataController->onPortEditEditingFinished(ui.m_portEdit->text().toInt());}
	void onIidFilePathEditEditingFinished();

	void onIidFilePathButtonClicked();
	void onStartStopToggleButtonClicked() {m_dataController->onStartStopToggleButtonClicked();}

	void onFoldAndNameJointsCheckBoxClicked() {m_dataController->onFoldAndNameJointsCheckBoxClicked(ui.m_foldAndNameJointsCheckBox->isChecked());}
	
	void onAddMapButtonClicked();
	void onInsertMapButtonClicked();
	void onAddChildMapButtonClicked();
	void onDeleteMapButtonClicked();
	void onClearMapsButtonClicked();
	//@}

protected:
	/// \name UI.
	//@{
	Ui::MainFormClass ui;

	MvdDataModel m_mvdModel;
	MvdPathDelegate m_pathDelegate;
	//@}

	QFileDialog m_iidFileSelectDlg;
	StreamBufToLogEdit m_clogStreamBuf;

	DataBase* m_dataBase;
	DataController* m_dataController;
};

} // namespace SK.