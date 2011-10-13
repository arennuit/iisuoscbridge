#pragma once

#include <QtGui/QMainWindow>
#include <QMessageBox>
#include "ui_MainForm.h"
#include "SDK/iisuSDK.h"

class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	MainForm(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainForm();

	// Iisu.
	bool initIisu();
	bool update();

	void newFrameListener(const SK::DataFrameEvent& event);

protected slots:
	void onIpAddressLineEditTextChanged(const QString& text) {m_ipAddress = text;}
	void onPortLineEditTextChanged(const QString& text) {m_port = text.toInt();}

	void onStartButtonClicked();
	void onStopButtonClicked();
	void onSettingsButtonClicked();

private:
	Ui::MainFormClass ui;

	// Iisu.
	SK::Device* m_device;
	SK::DataHandle< SK::Array<SK::Vector3> > m_skeleton;

	// Data.
	QString m_ipAddress;
	int m_port;

	static QString sm_defaultIpAddress;
	static int sm_defaultPort;
};