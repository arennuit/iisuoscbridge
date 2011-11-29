#include "MainForm.h"

#include "DataBase/DataBase.h"
#include "FormFiles/Mvd/MvdDataModel.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
MainForm::MainForm(QWidget *parent, Qt::WFlags flags) :
	QMainWindow(parent, flags),
	m_iidFileSelectDlg(this),
	m_clogStreamBuf()
{
	ui.setupUi(this);

	// Redirect clog streams to the log window.
	m_clogStreamBuf.setTargetTextEdit(ui.m_logTextEdit);
	std::clog.rdbuf(&m_clogStreamBuf);
}

//////////////////////////////////////////////////////////////////////////
MainForm::~MainForm()
{
	m_mvdModel.clear();
}

//////////////////////////////////////////////////////////////////////////
void MainForm::setup()
{
	// Set input masks and validators.
	QRegExpValidator *validator = new QRegExpValidator(this);
	QRegExp regExp("((1{0,1}[0-9]{0,2}|2[0-4]{1,1}[0-9]{1,1}|25[0-5]{1,1})\\.){3,3}(1{0,1}[0-9]{0,2}|2[0-4]{1,1}[0-9]{1,1}|25[0-5]{1,1})");
	validator->setRegExp(regExp);
	ui.m_ipAddressEdit->setValidator(validator);

	// Get access to the DataController.
	m_dataController = DataController::GetInstance();
	assert(m_dataController);

	// Setup model.
	ui.m_pathMapsView->setModel(&m_mvdModel);

	m_mvdModel.cleanAndReBuildAll();

	// Setup dialogs.
	m_iidFileSelectDlg.setFileMode(QFileDialog::ExistingFile);
	m_iidFileSelectDlg.setNameFilter("Interaction Designer (*.iid)");

	// UI setup.
	m_dataBase = DataBase::GetInstance(); // We do not make this pointer a member of the class because the MainForm is not due to modify data, it only uses the data model to perform the initial ui setup.
	assert(m_dataBase);

	ui.m_ipAddressEdit->setText(QString(m_dataBase->getIpAddress().c_str()));
	ui.m_portEdit->setText(QString::number(m_dataBase->getPort()));
	ui.m_iidFilePathEdit->setText(QString(m_dataBase->getIidFilePath().c_str()));

	if (m_dataBase->getIsObservationOn())
		ui.m_startStopToggleButton->setChecked(true);
	else
		ui.m_startStopToggleButton->setChecked(false);

	if (m_dataBase->getIsFoldAndNameJoints())
		ui.m_foldAndNameJointsCheckBox->setChecked(true);
	else
		ui.m_foldAndNameJointsCheckBox->setChecked(false);

	if (m_dataBase->getIsObservationOn() == true)
		ui.m_tabs->setCurrentWidget(ui.m_logTab);
	else
		ui.m_tabs->setCurrentWidget(ui.m_mapsTab);

	ui.m_pathMapsView->setAnimated(true);
	ui.m_pathMapsView->expandAll();
	ui.m_pathMapsView->resizeColumnToContents(0);
	ui.m_pathMapsView->resizeColumnToContents(1);
	ui.m_pathMapsView->setAlternatingRowColors(true);
	ui.m_pathMapsView->setItemDelegate(&m_pathDelegate);

	// Establish all connections.
	connect(ui.m_ipAddressEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onIpAddressLineEditTextChanged(const QString&)));
	connect(ui.m_portEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onPortLineEditTextChanged(const QString&)));
	connect(ui.m_iidFilePathEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onIidFilePathLineEditTextChanged(const QString&)));

	connect(ui.m_iidFilePathButton, SIGNAL(clicked()), this, SLOT(onIidFilePathButtonClicked()));
	connect(ui.m_startStopToggleButton, SIGNAL(clicked()), this, SLOT(onStartStopToggleButtonClicked()));

	connect(ui.m_foldAndNameJointsCheckBox, SIGNAL(clicked()), this, SLOT(onFoldAndNameJointsCheckBoxClicked()));

	connect(ui.m_addMapButton, SIGNAL(clicked()), this, SLOT(onAddMapButtonClicked()));
	connect(ui.m_insertMapButton, SIGNAL(clicked()), this, SLOT(onInsertMapButtonClicked()));
	connect(ui.m_deleteMapButton, SIGNAL(clicked()), this, SLOT(onDeleteMapButtonClicked()));
	connect(ui.m_clearMapsButton, SIGNAL(clicked()), this, SLOT(onClearMapsButtonClicked()));
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onIsObservationOnChanged(bool isObservationOn)
{
	ui.m_startStopToggleButton->setChecked(isObservationOn);
	ui.m_foldAndNameJointsCheckBox->setEnabled(!isObservationOn);
	ui.m_pathMapsView->setEnabled(!isObservationOn);

	// Show log tab when streaming.
	if (isObservationOn == true)
		ui.m_tabs->setCurrentWidget(ui.m_logTab);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onIidFilePathButtonClicked()
{
	QStringList fileNames;
	if (m_iidFileSelectDlg.exec())
	{
		fileNames = m_iidFileSelectDlg.selectedFiles();

		ui.m_iidFilePathEdit->setText(fileNames[0]);
		m_dataBase->setIidFilePath(fileNames[0].toStdString());
	}
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onDeleteMapButtonClicked()
{
	// Check the value of current item's role 'RoleIndexRole' is 'PathMapRole'.
	QModelIndex currentIndex = ui.m_pathMapsView->currentIndex();

	int customRole = currentIndex.data(MvdDataModel::RoleIndexRole).toInt();
	if (customRole != MvdDataModel::PathMapRole)
		return;
	
	// Delete the PathMap.
	PathMap* pathMap = pathMap = currentIndex.data(MvdDataModel::PathMapRole).value<PathMap*>();

	m_dataController->onDeleteMapButtonClicked(pathMap);

	// Update the model.
	QModelIndex parentIndex = currentIndex.parent();
	if (parentIndex.isValid())
		m_mvdModel.removeRow(currentIndex.row(), parentIndex);
	else
		m_mvdModel.removeRow(currentIndex.row(), QModelIndex());

	ui.m_pathMapsView->setCurrentIndex(parentIndex);

	//emit dataChanged(index, index);
};

} // namespace SK.