#include "MainForm.h"

#include "DataBase/DataBase.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
MainForm::MainForm(QWidget *parent, Qt::WFlags flags) :
	QMainWindow(parent, flags),
	m_areSettingsVisible(false)
{
	ui.setupUi(this);

	// Set input masks and validators.
	//QRegExp regEx("^([0-9]{1,3}(\.[0-9]{1,3}){3,3})$");
	QRegExpValidator *validator = new QRegExpValidator(this);
	QRegExp regExp("((1{0,1}[0-9]{0,2}|2[0-4]{1,1}[0-9]{1,1}|25[0-5]{1,1})\\.){3,3}(1{0,1}[0-9]{0,2}|2[0-4]{1,1}[0-9]{1,1}|25[0-5]{1,1})");
	validator->setRegExp(regExp);
	ui.m_ipAddressLineEdit->setValidator(validator);

	//int pos;
	//QValidator::State state = validator->validate(QString("255.1.23.134"), pos);

	// Get access to the DataController.
	m_dataController = DataController::GetInstance();
	assert(m_dataController);

	// Setup model.
	ui.m_pathsView->setModel(&m_mvdModel);

	m_mvdModel.update();

	ui.m_pathsView->expandAll();
	ui.m_pathsView->resizeColumnToContents(0);

	// Taylor UI.
	ui.m_pathsView->setVisible(m_areSettingsVisible);

	// Default texts.
	DataBase* dataBase = DataBase::GetInstance();
	assert(dataBase);

	ui.m_ipAddressLineEdit->setText(QString(dataBase->getIpAddress().c_str()));
	ui.m_portLineEdit->setText(QString::number(dataBase->getPort()));

	// Establish all connections.
	connect(ui.m_ipAddressLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onIpAddressLineEditTextChanged(const QString&)));
	connect(ui.m_portLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onPortLineEditTextChanged(const QString&)));

	connect(ui.m_startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
	connect(ui.m_stopButton, SIGNAL(clicked()), this, SLOT(onStopButtonClicked()));
	connect(ui.m_settingsButton, SIGNAL(clicked()), this, SLOT(onSettingsButtonClicked()));
}

//////////////////////////////////////////////////////////////////////////
MainForm::~MainForm()
{
	m_mvdModel.clear();
}

} // namespace SK.