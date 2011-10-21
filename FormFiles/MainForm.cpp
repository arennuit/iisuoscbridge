#include "MainForm.h"

#include "DataBase/DataBase.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
MainForm::MainForm(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	// Setup model.
	ui.m_pathsView->setModel(&m_mvdModel);

	m_mvdModel.update();

	ui.m_pathsView->expandAll();
	ui.m_pathsView->resizeColumnToContents(0);

	// Get access to the MvdController.
	m_dataController = DataController::GetInstance();
	assert(m_dataController);

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