#include "MainForm.h"

#include "Core/DataBase/DataBase.h"
#include "FormFiles/Mvd/MvdDataModel.h"
#include "Core/DataBase/PathMap.h"
#include "LogSystem/Logger.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
MainForm::MainForm(QWidget *parent, Qt::WFlags flags) :
	QMainWindow(parent, flags),
	m_iidFileSelectDlg(this),
	m_openFileSelectDlg(this),
	m_saveAsFileSelectDlg(this),
	m_clogStreamBuf(),
	m_selectedItem(0)
{
	// Designer-defined UI setup.
	ui.setupUi(this);

	// Custom UI setup.
	m_recentFilesSeparatorAction = ui.m_fileMenu->addSeparator();
	m_recentFilesSeparatorAction->setVisible(false);
	for (int i = 0; i < RECENT_FILES_MAX_NUM; ++i)
	{
		m_recentFileActions[i] = new QAction(this);
		ui.m_fileMenu->addAction(m_recentFileActions[i]);
		m_recentFileActions[i]->setVisible(false);
	}

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
	m_iidFileSelectDlg.setAcceptMode(QFileDialog::AcceptOpen);

	m_openFileSelectDlg.setFileMode(QFileDialog::ExistingFile);
	m_openFileSelectDlg.setNameFilter("Iisu Osc Bridge (*.iob)");
	m_openFileSelectDlg.setAcceptMode(QFileDialog::AcceptOpen);

	m_saveAsFileSelectDlg.setFileMode(QFileDialog::AnyFile);
	m_saveAsFileSelectDlg.setNameFilter("Iisu Osc Bridge (*.iob)");
	m_saveAsFileSelectDlg.setAcceptMode(QFileDialog::AcceptSave);
	m_saveAsFileSelectDlg.setDefaultSuffix("iob");

	// Setup UI.
	m_dataBase = DataBase::GetInstance(); // We do not make this pointer a member of the class because the MainForm is not due to modify data, it only uses the data model to perform the initial ui setup.
	assert(m_dataBase);

	ui.m_ipAddressEdit->setText(QString(m_dataBase->getIpAddress().c_str()));
	ui.m_portEdit->setText(QString::number(m_dataBase->getPort()));
	ui.m_iidFilePathEdit->setText(QString(m_dataBase->getIidFilePath().c_str()));

	if (m_dataBase->getMocapState())
		ui.m_startStopToggleButton->setChecked(true);
	else
		ui.m_startStopToggleButton->setChecked(false);

	if (m_dataBase->getIsFoldAndNameJoints())
		ui.m_foldAndNameJointsCheckBox->setChecked(true);
	else
		ui.m_foldAndNameJointsCheckBox->setChecked(false);

	if (m_dataBase->getMocapState() == true)
		ui.m_tabs->setCurrentWidget(ui.m_logTab);
	else
		ui.m_tabs->setCurrentWidget(ui.m_mapsTab);

	ui.m_pathMapsView->setAnimated(true);
	ui.m_pathMapsView->expandAll();
	ui.m_pathMapsView->resizeColumnToContents(0);
	ui.m_pathMapsView->resizeColumnToContents(1);
	ui.m_pathMapsView->setAlternatingRowColors(true);
	ui.m_pathMapsView->setItemDelegate(&m_pathDelegate);

	updateRecentFileActions();

	// Establish all connections.
	connect(ui.m_newAction, SIGNAL(triggered()), this, SLOT(onNewActionTriggered()));
	connect(ui.m_openAction, SIGNAL(triggered()), this, SLOT(onOpenActionTriggered()));
	connect(ui.m_saveAction, SIGNAL(triggered()), this, SLOT(onSaveActionTriggered()));
	connect(ui.m_saveAsAction, SIGNAL(triggered()), this, SLOT(onSaveAsActionTriggered()));
	connect(ui.m_quitAction, SIGNAL(triggered()), this, SLOT(onQuitActionTriggered()));

	connect(ui.m_mapsViewAction, SIGNAL(triggered()), this, SLOT(onMapsViewActionTriggered()));
	connect(ui.m_logViewAction, SIGNAL(triggered()), this, SLOT(onLogViewActionTriggered()));
	connect(ui.m_fullScreenAction, SIGNAL(triggered()), this, SLOT(onFullScreenAction()));

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

	for (uint i = 0; i < RECENT_FILES_MAX_NUM; ++i)
		connect(m_recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));

	connect(ui.m_pathMapsView->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onSelectionModelCurrentChanged(const QModelIndex&, const QModelIndex&)));
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onEditSelection(const PathMap* newSelectedPathMap)
{
	if (!newSelectedPathMap)
	{
		m_selectedItem = 0;

		ui.m_pathMapsView->setCurrentIndex(QModelIndex());

		return;
	}

	// Look for newSelectedPathMap in m_pathMapItemMap.
	std::map<const PathMap*, QStandardItem*>::const_iterator it = m_pathMapItemMap.find(newSelectedPathMap);
	assert(it != m_pathMapItemMap.end());

	// Update the selection.
	m_selectedItem = it->second;

	QModelIndex oscIndex = m_mvdModel.indexFromItem(m_selectedItem);
	assert(oscIndex.isValid());

	ui.m_pathMapsView->setCurrentIndex(oscIndex);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onAddPathMap(const PathMap* newPathMap)
{
	assert(newPathMap);
	assert((bool)m_selectedItem == (bool)newPathMap->getParent()); // A new PathMap can be added to a clear model only if the selection is empty.

	// Create the new model's items.
	QStandardItem* oscItem = new QStandardItem(newPathMap->getOscPathBit().c_str());
	assert(oscItem);
	oscItem->setData((int)MvdDataModel::PathMapRole, MvdDataModel::RoleIndexRole);
	oscItem->setData(QVariant::fromValue((PathMap*)newPathMap), MvdDataModel::PathMapRole);

	QStandardItem* iisuItem = new QStandardItem(newPathMap->getIisuPath().c_str());
	assert(iisuItem);
	iisuItem->setData((int)MvdDataModel::PathMapRole, MvdDataModel::RoleIndexRole);
	iisuItem->setData(QVariant::fromValue((PathMap*)newPathMap), MvdDataModel::PathMapRole);

	// Attach the new items.
	if (newPathMap->getParent())
	{
		QStandardItem* parentItem = m_selectedItem->parent();
		assert(parentItem);
	
		int rowIdx = parentItem->rowCount();
		parentItem->setChild(rowIdx, 0, oscItem);
		parentItem->setChild(rowIdx, 1, iisuItem);
	}
	else
	{
		m_mvdModel.setItem(0, 0, oscItem);
		m_mvdModel.setItem(0, 1, iisuItem);
	}

	// Update m_pathMapItemMap.
	m_pathMapItemMap.insert(std::make_pair(newPathMap, oscItem));
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onInsertPathMap(const PathMap* newPathMap)
{
	assert(newPathMap);
	assert((bool)m_selectedItem == (bool)newPathMap->getParent()); // A new PathMap can be added to a clear model only if the selection is empty.

	// Create the new model's items.
	QStandardItem* oscItem = new QStandardItem(newPathMap->getOscPathBit().c_str());
	assert(oscItem);
	oscItem->setData((int)MvdDataModel::PathMapRole, MvdDataModel::RoleIndexRole);
	oscItem->setData(QVariant::fromValue((PathMap*)newPathMap), MvdDataModel::PathMapRole);

	QStandardItem* iisuItem = new QStandardItem(newPathMap->getIisuPath().c_str());
	assert(iisuItem);
	iisuItem->setData((int)MvdDataModel::PathMapRole, MvdDataModel::RoleIndexRole);
	iisuItem->setData(QVariant::fromValue((PathMap*)newPathMap), MvdDataModel::PathMapRole);

	// Attach the new items.
	if (newPathMap->getParent())
	{
		QStandardItem* parentItem = m_selectedItem->parent();
		assert(parentItem);

		int rowIdx = m_selectedItem->row();
		parentItem->insertRow(rowIdx, QList<QStandardItem*>() << oscItem << iisuItem);
	}
	else
	{
		m_mvdModel.setItem(0, 0, oscItem);
		m_mvdModel.setItem(0, 1, iisuItem);
	}

	// Update m_pathMapItemMap.
	m_pathMapItemMap.insert(std::make_pair(newPathMap, oscItem));
};

//////////////////////////////////////////////////////////////////////////
void MainForm::onAddChildMap(const PathMap* newPathMap)
{
	assert(newPathMap);
	assert((bool)m_selectedItem == (bool)newPathMap->getParent()); // A new PathMap can be added to a clear model only if the selection is empty.

	// Create the new model's items.
	QStandardItem* oscItem = new QStandardItem(newPathMap->getOscPathBit().c_str());
	assert(oscItem);
	oscItem->setData((int)MvdDataModel::PathMapRole, MvdDataModel::RoleIndexRole);
	oscItem->setData(QVariant::fromValue((PathMap*)newPathMap), MvdDataModel::PathMapRole);

	QStandardItem* iisuItem = new QStandardItem(newPathMap->getIisuPath().c_str());
	assert(iisuItem);
	iisuItem->setData((int)MvdDataModel::PathMapRole, MvdDataModel::RoleIndexRole);
	iisuItem->setData(QVariant::fromValue((PathMap*)newPathMap), MvdDataModel::PathMapRole);

	// Attach the new items.
	if (newPathMap->getParent())
	{
		int rowIdx = m_selectedItem->rowCount();
		m_selectedItem->setChild(rowIdx, 0, oscItem);
		m_selectedItem->setChild(rowIdx, 1, iisuItem);
	}
	else
	{
		m_mvdModel.setItem(0, 0, oscItem);
		m_mvdModel.setItem(0, 1, iisuItem);
	}

	// Update m_pathMapItemMap.
	m_pathMapItemMap.insert(std::make_pair(newPathMap, oscItem));
};

//////////////////////////////////////////////////////////////////////////
void MainForm::onDeletePathMap(const PathMap* pathMapToBeDeleted)
{
	assert(pathMapToBeDeleted);

	// Delete the model's items.
	// NOTE: we do not assert on parentIndex, as the parent can be invalid if selectedIndex is the root index.
	std::map<const PathMap*, QStandardItem*>::const_iterator it = m_pathMapItemMap.find(pathMapToBeDeleted);
	assert(it != m_pathMapItemMap.end());

	QStandardItem* itemToBeDeleted = it->second;
	assert(itemToBeDeleted);

	QModelIndex indexToBeDeleted = m_mvdModel.indexFromItem(itemToBeDeleted);
	assert(indexToBeDeleted.isValid());

	QModelIndex parentIndex = indexToBeDeleted.parent();

	m_mvdModel.removeRow(indexToBeDeleted.row(), parentIndex);

	// Update m_pathMapItemMap.
	std::vector<PathMap*> pathMapsToBeDeleted;
	pathMapsToBeDeleted.push_back((PathMap*)pathMapToBeDeleted);
	addChildrenToArray_recursive((PathMap*)pathMapToBeDeleted, pathMapsToBeDeleted);

	for (uint i = 0; i < pathMapsToBeDeleted.size(); ++i)
		m_pathMapItemMap.erase(pathMapsToBeDeleted[i]);
};

//////////////////////////////////////////////////////////////////////////
void MainForm::onClearPathMaps()
{
	// Clear the model.
	// NOTE: we only clear all the model's top rows, in order to keep the columns headers.
	for (uint i = 0; i < m_mvdModel.rowCount(); ++i)
		m_mvdModel.removeRow(i, QModelIndex());

	// Update m_pathMapItemMap.
	m_pathMapItemMap.clear();
}

//////////////////////////////////////////////////////////////////////////
void MainForm::addChildrenToArray_recursive(PathMap* pathMap, std::vector<PathMap*>& pathMapsToBeDeleted)
{
	// Add children to the list.
	for (uint i = 0; i < pathMap->getChildren().size(); ++i)
		pathMapsToBeDeleted.push_back(pathMap->getChildren()[i]);

	// Recursion into children.
	for (uint i = 0; i < pathMap->getChildren().size(); ++i)
		addChildrenToArray_recursive(pathMap->getChildren()[i], pathMapsToBeDeleted);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onMocapStateChanged( bool mocapState )
{
	ui.m_startStopToggleButton->setChecked(mocapState);

	ui.m_foldAndNameJointsCheckBox->setEnabled(!mocapState);
	ui.m_pathMapsView->setEnabled(!mocapState);

	// Show log tab when streaming.
	if (mocapState == true)
		ui.m_tabs->setCurrentWidget(ui.m_logTab);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onNewActionTriggered()
{
	m_dataController->newProject();

	// Update the GUI.
	setCurrentFilePath(std::string(""));
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onOpenActionTriggered()
{
	// Get the filepath.
	if (!m_openFileSelectDlg.exec())
		return;

	std::string filePath = m_openFileSelectDlg.selectedFiles()[0].toStdString();
	if (filePath == "")
	{
		SK_LOGGER(LOG_WARNING) << "Selected file for \'Open\' command is invalid.";
		return;
	}

	m_dataController->loadProjectFromFile(filePath);

	// Update the GUI.
	setCurrentFilePath(filePath);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onSaveActionTriggered()
{
	QString filePath = windowFilePath();

	// If there is no current file then the behavior is the same as for 'Save As'.
	if (filePath.isEmpty())
		return onSaveAsActionTriggered();

	// Save in the current file.
	m_dataController->saveProjectToFile(filePath.toStdString());

	// Update the GUI.
	setCurrentFilePath(filePath.toStdString());
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onSaveAsActionTriggered()
{
	// Get the filepath (add the extension if needed).
	if (!m_saveAsFileSelectDlg.exec())
		return;

	std::string filePath = m_saveAsFileSelectDlg.selectedFiles()[0].toStdString();
	if (filePath == "")
	{
		SK_LOGGER(LOG_WARNING) << "Selected file for \'Save As\' command is invalid.";
		return;
	}

	m_dataController->saveProjectToFile(filePath);

	// Update the GUI.
	setCurrentFilePath(filePath);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::openRecentFile()
{
	QAction *action = qobject_cast<QAction*>(sender());
	if (!action)
		return;

	m_dataController->loadProjectFromFile(action->data().toString().toStdString());
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onFullScreenAction()
{
	Qt::WindowStates windowStates = windowState();
	if (windowStates & Qt::WindowFullScreen)
		showNormal();
	else
		showFullScreen();
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onIidFilePathEditEditingFinished()
{
	bool isIidFileOk = m_dataController->editIidFilePath(ui.m_iidFilePathEdit->text().toStdString());
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

	bool isIidFileOk = m_dataController->editIidFilePath(ui.m_iidFilePathEdit->text().toStdString());
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onSelectionModelCurrentChanged( const QModelIndex& newModelIndex, const QModelIndex& /*oldModelIndex*/ )
{
	if (!newModelIndex.isValid())
	{
		m_selectedItem = 0;
		m_dataController->editSelection(0);

		return;
	}

	// Get the underlying PathMap.
	m_selectedItem = m_mvdModel.itemFromIndex(newModelIndex);
	assert(m_selectedItem);

	int customRole = newModelIndex.data(MvdDataModel::RoleIndexRole).toInt();
	assert(customRole == MvdDataModel::PathMapRole);

	PathMap* newSelectedPathMap = newModelIndex.data(MvdDataModel::PathMapRole).value<PathMap*>();

	// Call the controller's method.
	m_dataController->editSelection(newSelectedPathMap);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::setCurrentFilePath( std::string& filePath )
{
	// Update the window.
	setWindowFilePath(filePath.c_str());

	// Update the settings' list of recent files.
	if (filePath == "")
		return;

	QString filePath_asQString = QString().fromStdString(filePath);
	QSettings settings;
	QStringList recentFilesList = settings.value("recentFileList").toStringList();
	recentFilesList.removeAll(filePath_asQString);
	recentFilesList.prepend(filePath_asQString);
	while (recentFilesList.size() > RECENT_FILES_MAX_NUM)
		recentFilesList.removeLast();

	settings.setValue("recentFileList", recentFilesList);

	// Update recent file actions.
	updateRecentFileActions();
}

//////////////////////////////////////////////////////////////////////////
void MainForm::updateRecentFileActions()
{
	QSettings settings;
	QStringList recentFilesList = settings.value("recentFileList").toStringList();

	m_recentFilesSeparatorAction->setVisible(recentFilesList.size() > 0);

	for (int i = 0; i < recentFilesList.size(); ++i)
	{
		m_recentFileActions[i]->setText(QFileInfo(recentFilesList[i]).fileName());
		m_recentFileActions[i]->setData(recentFilesList[i]);
		m_recentFileActions[i]->setVisible(true);
	}

	for (int i = recentFilesList.size(); i < RECENT_FILES_MAX_NUM; ++i)
		m_recentFileActions[i]->setVisible(false);
}

} // namespace SK.