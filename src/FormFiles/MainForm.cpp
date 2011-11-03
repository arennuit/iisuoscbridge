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
	ui.m_ipAddressEdit->setValidator(validator);

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
	ui.m_pathsView->resizeColumnToContents(1);

	// UI setup.
	DataBase* dataBase = DataBase::GetInstance(); // We do not make this pointer a member of the class because the MainForm is not due to modify data, it only uses the data model to perform the initial ui setup.
	assert(dataBase);

	ui.m_tabs->setVisible(m_areSettingsVisible);

	ui.m_ipAddressEdit->setText(QString(dataBase->getIpAddress().c_str()));
	ui.m_portEdit->setText(QString::number(dataBase->getPort()));

	if (dataBase->getIsObservationOn())
		ui.m_startStopToggleButton->setChecked(true);
	else
		ui.m_startStopToggleButton->setChecked(false);

	if (dataBase->getIsFoldAndNameJoints())
		ui.m_foldAndNameJointsCheckBox->setChecked(true);
	else
		ui.m_foldAndNameJointsCheckBox->setChecked(false);

	// Establish all connections.
	connect(ui.m_ipAddressEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onIpAddressLineEditTextChanged(const QString&)));
	connect(ui.m_portEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onPortLineEditTextChanged(const QString&)));

	connect(ui.m_startStopToggleButton, SIGNAL(clicked()), this, SLOT(onStartStopToggleButtonClicked()));
	connect(ui.m_settingsButton, SIGNAL(clicked()), this, SLOT(onSettingsButtonClicked()));

	connect(ui.m_foldAndNameJointsCheckBox, SIGNAL(clicked()), this, SLOT(onFoldAndNameJointsCheckBoxClicked()));
}

//////////////////////////////////////////////////////////////////////////
MainForm::~MainForm()
{
	m_mvdModel.clear();
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onIsObservationOnChanged(bool isObservationOn)
{
	ui.m_startStopToggleButton->setChecked(isObservationOn);
	ui.m_foldAndNameJointsCheckBox->setEnabled(!isObservationOn);
	ui.m_pathsView->setEnabled(!isObservationOn);
}

} // namespace SK.