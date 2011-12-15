#pragma once

#include <QtGui/QMainWindow>
#include <QMainWindow>
#include <QFileDialog>
#include "ui_MainForm.h"
#include "Core/DataController.h"
#include "Mvd/MvdDataModel.h"
#include "Mvd/MvdPathDelegate.h"

#define RECENT_FILES_MAX_NUM 5

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
	void onNewActionTriggered();
	void onOpenActionTriggered();
	void onSaveActionTriggered();
	void onSaveAsActionTriggered();
	void onQuitActionTriggered() {QApplication::quit();}
	void openRecentFile();

	void onMapsViewActionTriggered() {ui.m_tabs->setCurrentWidget(ui.m_mapsTab);}
	void onLogViewActionTriggered() {ui.m_tabs->setCurrentWidget(ui.m_logTab);}
	void onFullScreenAction();

	void onIpAddressEditEditingFinished() {m_dataController->editIpAddress(ui.m_ipAddressEdit->text().toStdString());}
	void onPortEditEditingFinished() {m_dataController->editPort(ui.m_portEdit->text().toInt());}
	void onIidFilePathEditEditingFinished();

	void onIidFilePathButtonClicked();
	void onStartStopToggleButtonClicked() {m_dataController->toggleResumePause();}

	void onFoldAndNameJointsCheckBoxClicked() {m_dataController->editFoldAndNameJointsOption(ui.m_foldAndNameJointsCheckBox->isChecked());}
	
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
	QFileDialog m_openFileSelectDlg;
	QFileDialog m_saveAsFileSelectDlg;
	StreamBufToLogEdit m_clogStreamBuf;

	DataBase* m_dataBase;
	DataController* m_dataController;

	void setCurrentFilePath(std::string& filePath);
	void updateRecentFileActions();
	QAction* m_recentFilesSeparatorAction;
	QAction* m_recentFileActions[RECENT_FILES_MAX_NUM];
};

} // namespace SK.