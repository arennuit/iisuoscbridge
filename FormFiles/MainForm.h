#pragma once

#include <QtGui/QMainWindow>
#include <QMessageBox>
#include "ui_MainForm.h"
#include "SDK/iisuSDK.h"
#include "DataBase/DataBase.h"
#include "FormFiles/SettingsForm.h"

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

	/// \name Iisu.
	//@{
	bool initIisu();
	bool update();
	void newFrameListener(const SK::DataFrameEvent& event);
	//@}

protected slots:
	void onIpAddressLineEditTextChanged(const QString& text) {m_dataModel->setIpAddress(text.toStdString());}
	void onPortLineEditTextChanged(const QString& text) {m_dataModel->setPort(text.toInt());}

	void onStartButtonClicked();
	void onStopButtonClicked();
	void onSettingsButtonClicked();

protected:
	/// \name UI.
	//@{
	Ui::MainFormClass ui;
	SettingsForm m_settingsForm;
	//@}

	DataBase* m_dataModel;

	/// \name Iisu.
	//@{
	SK::Device* m_device;
	SK::DataHandle<SK::Array<SK::Vector3> > m_skeleton;
	//@}
};

} // namespace SK.