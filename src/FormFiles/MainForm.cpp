#include "MainForm.h"

#include "DataBase/DataBase.h"
#include "FormFiles/Mvd/MvdDataModel.h"
#include "DataBase/PathMap.h"

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
	connect(ui.m_ipAddressEdit, SIGNAL(editingFinished()), this, SLOT(onIpAddressEditEditingFinished()));
	connect(ui.m_portEdit, SIGNAL(editingFinished()), this, SLOT(onPortEditEditingFinished()));
	connect(ui.m_iidFilePathEdit, SIGNAL(editingFinished()), this, SLOT(onIidFilePathEditEditingFinished()));

	connect(ui.m_iidFilePathButton, SIGNAL(clicked()), this, SLOT(onIidFilePathButtonClicked()));
	connect(ui.m_startStopToggleButton, SIGNAL(clicked()), this, SLOT(onStartStopToggleButtonClicked()));

	connect(ui.m_foldAndNameJointsCheckBox, SIGNAL(clicked()), this, SLOT(onFoldAndNameJointsCheckBoxClicked()));

	connect(ui.m_addMapButton, SIGNAL(clicked()), this, SLOT(onAddMapButtonClicked()));
	connect(ui.m_insertMapButton, SIGNAL(clicked()), this, SLOT(onInsertMapButtonClicked()));
	connect(ui.m_addChildMapButton, SIGNAL(clicked()), this, SLOT(onAddChildMapButtonClicked()));
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
void MainForm::onIidFilePathEditEditingFinished()
{
	bool isIidFileOk = m_dataController->onIidFilePathEditChanged(ui.m_iidFilePathEdit->text().toStdString());
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onIidFilePathButtonClicked()
{
	// Get the new iid filepath.
	QStringList fileNames;
	if (!m_iidFileSelectDlg.exec())
		return;

	fileNames = m_iidFileSelectDlg.selectedFiles();

	ui.m_iidFilePathEdit->setText(fileNames[0]);

	bool isIidFileOk = m_dataController->onIidFilePathEditChanged(ui.m_iidFilePathEdit->text().toStdString());
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onAddMapButtonClicked()
{
	// Call the controller's method.
	QModelIndex currentIndex = ui.m_pathMapsView->currentIndex();
	if (!currentIndex.isValid())
		return;

	QStandardItem* currentItem = m_mvdModel.itemFromIndex(currentIndex);
	if (!currentItem)
		return;

	int customRole = currentIndex.data(MvdDataModel::RoleIndexRole).toInt();
	if (customRole != MvdDataModel::PathMapRole)
		return;

	PathMap* currentPathMap = currentPathMap = currentIndex.data(MvdDataModel::PathMapRole).value<PathMap*>();
	if (!currentPathMap)
		return;

	PathMap* newPathMap = m_dataController->onAddMapButtonClicked(currentPathMap);
	if (!newPathMap)
		return;

	// Update the model.
	QStandardItem* oscItem = new QStandardItem(newPathMap->getOscPathBit().c_str());
	assert(oscItem);
	oscItem->setData((int)MvdDataModel::PathMapRole, MvdDataModel::RoleIndexRole);
	oscItem->setData(QVariant::fromValue(newPathMap), MvdDataModel::PathMapRole);

	QStandardItem* iisuItem = new QStandardItem(newPathMap->getIisuPath().c_str());
	assert(iisuItem);
	iisuItem->setData((int)MvdDataModel::PathMapRole, MvdDataModel::RoleIndexRole);
	iisuItem->setData(QVariant::fromValue(newPathMap), MvdDataModel::PathMapRole);

	QStandardItem* parentItem = currentItem->parent();
	assert(parentItem);

	int rowIdx = parentItem->rowCount();
	parentItem->setChild(rowIdx, 0, oscItem);
	parentItem->setChild(rowIdx, 1, iisuItem);

	// Update the views.
	QModelIndex oscIndex = m_mvdModel.indexFromItem(oscItem);

	if (oscIndex.isValid())
		ui.m_pathMapsView->setCurrentIndex(oscIndex);	

	//emit dataChanged(index, index);
};

//////////////////////////////////////////////////////////////////////////
void MainForm::onInsertMapButtonClicked()
{
	// Call the controller's method.
	QModelIndex currentIndex = ui.m_pathMapsView->currentIndex();
	if (!currentIndex.isValid())
		return;

	QStandardItem* currentItem = m_mvdModel.itemFromIndex(currentIndex);
	if (!currentItem)
		return;

	int customRole = currentIndex.data(MvdDataModel::RoleIndexRole).toInt();
	if (customRole != MvdDataModel::PathMapRole)
		return;

	PathMap* currentPathMap = currentPathMap = currentIndex.data(MvdDataModel::PathMapRole).value<PathMap*>();
	if (!currentPathMap)
		return;

	PathMap* newPathMap = m_dataController->onInsertMapButtonClicked(currentPathMap);
	if (!newPathMap)
		return;

	// Update the model.
	QStandardItem* oscItem = new QStandardItem(newPathMap->getOscPathBit().c_str());
	assert(oscItem);
	oscItem->setData((int)MvdDataModel::PathMapRole, MvdDataModel::RoleIndexRole);
	oscItem->setData(QVariant::fromValue(newPathMap), MvdDataModel::PathMapRole);

	QStandardItem* iisuItem = new QStandardItem(newPathMap->getIisuPath().c_str());
	assert(iisuItem);
	iisuItem->setData((int)MvdDataModel::PathMapRole, MvdDataModel::RoleIndexRole);
	iisuItem->setData(QVariant::fromValue(newPathMap), MvdDataModel::PathMapRole);

	QStandardItem* parentItem = currentItem->parent();
	assert(parentItem);

	int rowIdx = currentIndex.row();
	parentItem->insertRow(rowIdx, QList<QStandardItem*>() << oscItem << iisuItem);

	// Update the views.
	QModelIndex oscIndex = m_mvdModel.indexFromItem(oscItem);

	if (oscIndex.isValid())
		ui.m_pathMapsView->setCurrentIndex(oscIndex);	

	//emit dataChanged(index, index);
};

//////////////////////////////////////////////////////////////////////////
void MainForm::onAddChildMapButtonClicked()
{
	// Call the controller's method.
	QModelIndex currentIndex = ui.m_pathMapsView->currentIndex();
	if (!currentIndex.isValid())
		return;

	QStandardItem* currentItem = m_mvdModel.itemFromIndex(currentIndex);
	if (!currentItem)
		return;

	int customRole = currentIndex.data(MvdDataModel::RoleIndexRole).toInt();
	if (customRole != MvdDataModel::PathMapRole)
		return;

	PathMap* currentPathMap = currentPathMap = currentIndex.data(MvdDataModel::PathMapRole).value<PathMap*>();
	if (!currentPathMap)
		return;
 
	PathMap* newPathMap = m_dataController->onAddChildMapButtonClicked(currentPathMap);
	if (!newPathMap)
		return;

	// Update the model.
	QStandardItem* oscItem = new QStandardItem(newPathMap->getOscPathBit().c_str());
	assert(oscItem);
	oscItem->setData((int)MvdDataModel::PathMapRole, MvdDataModel::RoleIndexRole);
	oscItem->setData(QVariant::fromValue(newPathMap), MvdDataModel::PathMapRole);

	QStandardItem* iisuItem = new QStandardItem(newPathMap->getIisuPath().c_str());
	assert(iisuItem);
	iisuItem->setData((int)MvdDataModel::PathMapRole, MvdDataModel::RoleIndexRole);
	iisuItem->setData(QVariant::fromValue(newPathMap), MvdDataModel::PathMapRole);

	int rowIdx = currentItem->rowCount();
	currentItem->setChild(rowIdx, 0, oscItem);
	currentItem->setChild(rowIdx, 1, iisuItem);

	// Update the views.
	QModelIndex oscIndex = m_mvdModel.indexFromItem(oscItem);

	if (oscIndex.isValid())
		ui.m_pathMapsView->setCurrentIndex(oscIndex);	

	//emit dataChanged(index, index);
};

//////////////////////////////////////////////////////////////////////////
void MainForm::onDeleteMapButtonClicked()
{
	// Get the current PathMap.
	QModelIndex currentIndex = ui.m_pathMapsView->currentIndex();
	if (!currentIndex.isValid())
		return;

	int customRole = currentIndex.data(MvdDataModel::RoleIndexRole).toInt();
	if (customRole != MvdDataModel::PathMapRole)
		return;
	
	PathMap* currentPathMap = currentPathMap = currentIndex.data(MvdDataModel::PathMapRole).value<PathMap*>();
	if (!currentPathMap)
		return;

	// Call the controller's method. 
	m_dataController->onDeleteMapButtonClicked(currentPathMap);

	// Update the model.
	QModelIndex parentIndex = currentIndex.parent();
	m_mvdModel.removeRow(currentIndex.row(), parentIndex);

	// Update the views.
	ui.m_pathMapsView->setCurrentIndex(parentIndex);

	//emit dataChanged(index, index);
};

//////////////////////////////////////////////////////////////////////////
void MainForm::onClearMapsButtonClicked()
{
	// Call the controller's method. 
	m_dataController->onClearMapsButtonClicked();

	// Update the model.
	m_mvdModel.clear();

	//emit dataChanged(index, index);
};

} // namespace SK.