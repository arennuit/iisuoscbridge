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
	assert(SK::DataController::GetInstance());

	m_dataController = SK::DataController::GetInstance();

	// Set input masks and validators.
	QRegExpValidator *validator = new QRegExpValidator(this);
	QRegExp regExp("((1{0,1}[0-9]{0,2}|2[0-4]{1,1}[0-9]{1,1}|25[0-5]{1,1})\\.){3,3}(1{0,1}[0-9]{0,2}|2[0-4]{1,1}[0-9]{1,1}|25[0-5]{1,1})");
	validator->setRegExp(regExp);
	ui.m_ipAddressEdit->setValidator(validator);

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
	ui.m_pathMapsView->setAnimated(true);
	ui.m_pathMapsView->setAlternatingRowColors(true);
	ui.m_pathMapsView->setItemDelegate(&m_pathDelegate);

	// Setup context menu.
	ui.m_pathMapsView->setContextMenuPolicy(Qt::CustomContextMenu);
	m_pathMapsViewContextMenu.addAction(ui.m_copyOscPathAction);
	m_pathMapsViewContextMenu.addSeparator();
	m_pathMapsViewContextMenu.addAction(ui.m_addMapAction);
	m_pathMapsViewContextMenu.addAction(ui.m_insertMapAction);
	m_pathMapsViewContextMenu.addAction(ui.m_addChildMapAction);
	m_pathMapsViewContextMenu.addSeparator();
	m_pathMapsViewContextMenu.addAction(ui.m_deleteMapAction);
	m_pathMapsViewContextMenu.addAction(ui.m_clearMapsAction);

	// Establish all connections.
	connect(ui.m_newAction, SIGNAL(triggered()), this, SLOT(onNewActionTriggered()));
	connect(ui.m_openAction, SIGNAL(triggered()), this, SLOT(onOpenActionTriggered()));
	connect(ui.m_saveAction, SIGNAL(triggered()), this, SLOT(onSaveActionTriggered()));
	connect(ui.m_saveAsAction, SIGNAL(triggered()), this, SLOT(onSaveAsActionTriggered()));
	connect(ui.m_quitAction, SIGNAL(triggered()), this, SLOT(onQuitActionTriggered()));

	connect(ui.m_iisuToolboxAction, SIGNAL(triggered()), this, SLOT(onIisuToolboxActionTriggered()));
	connect(ui.m_logViewAction, SIGNAL(triggered()), this, SLOT(onLogViewActionTriggered()));
	connect(ui.m_fullScreenAction, SIGNAL(triggered()), this, SLOT(onFullScreenAction()));

	connect(ui.m_ipAddressEdit, SIGNAL(editingFinished()), this, SLOT(onIpAddressEditEditingFinished()));
	connect(ui.m_ipPortEdit, SIGNAL(editingFinished()), this, SLOT(onIpPortEditEditingFinished()));
	connect(ui.m_iidFilePathEdit, SIGNAL(editingFinished()), this, SLOT(onIidFilePathEditEditingFinished()));

	connect(ui.m_iidFilePathButton, SIGNAL(clicked()), this, SLOT(onIidFilePathButtonClicked()));
	connect(ui.m_startStopToggleButton, SIGNAL(clicked()), this, SLOT(onStartStopToggleButtonClicked()));

	connect(ui.m_decorateStreamCheckBox, SIGNAL(clicked()), this, SLOT(onDecorateStreamCheckBoxClicked()));

	connect(ui.m_addMapButton, SIGNAL(clicked()), this, SLOT(onAddMapButtonClicked()));
	connect(ui.m_insertMapButton, SIGNAL(clicked()), this, SLOT(onInsertMapButtonClicked()));
	connect(ui.m_addChildMapButton, SIGNAL(clicked()), this, SLOT(onAddChildMapButtonClicked()));
	connect(ui.m_deleteMapButton, SIGNAL(clicked()), this, SLOT(onDeleteMapButtonClicked()));
	connect(ui.m_clearMapsButton, SIGNAL(clicked()), this, SLOT(onClearMapsButtonClicked()));

	connect(ui.m_clearLogButton, SIGNAL(clicked()), this, SLOT(onClearLogButtonClicked()));

	for (uint i = 0; i < RECENT_FILES_MAX_NUM; ++i)
		connect(m_recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));

	connect(ui.m_pathMapsView->selectionModel(), SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onSelectionModelCurrentChanged(const QModelIndex&, const QModelIndex&)));

	connect(ui.m_pathMapsView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(onPathMapsViewContextMenuRequested(const QPoint&)));
	connect(ui.m_copyOscPathAction, SIGNAL(triggered()), this, SLOT(onCopyOscPathActionTriggered()));
	connect(ui.m_addMapAction, SIGNAL(triggered()), this, SLOT(onAddMapActionTriggered()));
	connect(ui.m_insertMapAction, SIGNAL(triggered()), this, SLOT(onInsertMapActionTriggered()));
	connect(ui.m_addChildMapAction, SIGNAL(triggered()), this, SLOT(onAddChildMapActionTriggered()));
	connect(ui.m_deleteMapAction, SIGNAL(triggered()), this, SLOT(onDeleteMapActionTriggered()));
	connect(ui.m_clearMapsAction, SIGNAL(triggered()), this, SLOT(onClearMapsActionTriggered()));
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
void MainForm::onLoadProjectFromFile( const std::string& filePath )
{
	ui.m_pathMapsView->expandAll();
	ui.m_pathMapsView->resizeColumnToContents(0);
	ui.m_pathMapsView->resizeColumnToContents(1);

	setCurrentFilePath(filePath);

	// Tell Qt the project is saved.
	setWindowModified(false);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onSaveProjectToFile( const std::string& filePath )
{
	setCurrentFilePath(filePath);

	// Tell Qt the project is saved.
	setWindowModified(false);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onReset()
{
	setCurrentFilePath(std::string());

	// Tell Qt the project is saved.
	setWindowModified(false);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onAddPathMap(const PathMap* newPathMap)
{
	assert(newPathMap);

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
		QStandardItem* parentItem = m_pathMapItemMap[newPathMap->getParent()];
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

	// Tell Qt the project was modified.
	setWindowModified(true);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onInsertPathMap(const PathMap* newPathMap)
{
	assert(newPathMap);

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
		PathMap* parentPathMap = newPathMap->getParent();

		QStandardItem* parentItem = m_pathMapItemMap[parentPathMap];
		assert(parentItem);

		int rowIdx;
		for (rowIdx = 0; rowIdx < parentPathMap->getChildren().size(); ++rowIdx)
		{
			if (parentPathMap->getChildren()[rowIdx] == newPathMap)
				break;
		}

		parentItem->insertRow(rowIdx, QList<QStandardItem*>() << oscItem << iisuItem);
	}
	else
	{
		m_mvdModel.setItem(0, 0, oscItem);
		m_mvdModel.setItem(0, 1, iisuItem);
	}

	// Update m_pathMapItemMap.
	m_pathMapItemMap.insert(std::make_pair(newPathMap, oscItem));

	// Tell Qt the project was modified.
	setWindowModified(true);
};

//////////////////////////////////////////////////////////////////////////
void MainForm::onAddChildMap(const PathMap* newPathMap)
{
	assert(newPathMap);

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
		QStandardItem* parentItem = m_pathMapItemMap[newPathMap->getParent()];
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

	// Tell Qt the project was modified.
	setWindowModified(true);
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

	// Tell Qt the project was modified.
	setWindowModified(true);
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

	// Tell Qt the project was modified.
	setWindowModified(true);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onEditPathMap(const PathMap* pathMap)
{
	// Update the views.
	// TODO.

	// Tell Qt the project was modified.
	setWindowModified(true);
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
void MainForm::onIpAddressChanged(const std::string& ipAddress)
{
	ui.m_ipAddressEdit->setText(ipAddress.c_str());

	// Tell Qt the project was modified.
	setWindowModified(true);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onIpPortChanged(int ipPort)
{
	ui.m_ipPortEdit->setText(QString::number(ipPort));

	// Tell Qt the project was modified.
	setWindowModified(true);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onIidFilePathChanged(const std::string& iidFilePath)
{
	ui.m_iidFilePathEdit->setText(iidFilePath.c_str());

	// Tell Qt the project was modified.
	setWindowModified(true);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onMocapStateChanged( bool mocapState )
{
	ui.m_startStopToggleButton->setChecked(mocapState);

	ui.m_decorateStreamCheckBox->setEnabled(!mocapState);
	ui.m_pathMapsView->setEnabled(!mocapState);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::decorateStreamChanged(bool decorateStream)
{
	ui.m_decorateStreamCheckBox->setChecked(decorateStream);

	// Tell Qt the project was modified.
	setWindowModified(true);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onOscPacketSizeChanged(uint oscPacketSize)
{
	ui.m_oscPacketSizeLineEdit->setText(QString::number(oscPacketSize));
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onOpenActionTriggered()
{
	// Get the filepath.
	if (!m_openFileSelectDlg.exec())
		return;

	std::string filePath = m_openFileSelectDlg.selectedFiles()[0].toStdString();
	m_dataController->loadProjectFromFile(filePath);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onNewActionTriggered()
{
	m_dataController->resetProject();
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onSaveActionTriggered()
{
	QSettings settings;
	std::string filePath = settings.value("CurrentFilePath").toString().toStdString();

	// If there is no current file then the behavior is the same as for 'Save As'.
	if (filePath == "")
		return onSaveAsActionTriggered();

	// Save in the current file.
	m_dataController->saveProjectToFile(filePath);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onSaveAsActionTriggered()
{
	// Get the filepath (add the extension if needed).
	if (!m_saveAsFileSelectDlg.exec())
		return;

	std::string filePath = m_saveAsFileSelectDlg.selectedFiles()[0].toStdString();
	m_dataController->saveProjectToFile(filePath);
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
void MainForm::onIisuToolboxActionTriggered()
{

}

//////////////////////////////////////////////////////////////////////////
void MainForm::onLogViewActionTriggered()
{
	if (ui.m_logDock->isVisible())
		ui.m_logDock->hide();
	else
		ui.m_logDock->show();
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
void MainForm::onCopyOscPathActionTriggered()
{
	QClipboard *clipboard = QApplication::clipboard();
	assert(clipboard);

	std::string fullOscPath = m_dataController->findFullOscPath();
	clipboard->setText(QString::fromStdString(fullOscPath));
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onIidFilePathEditEditingFinished()
{
	std::string filePath = ui.m_iidFilePathEdit->text().toStdString();

	m_dataController->editIidFilePath(filePath);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::onIidFilePathButtonClicked()
{
	// Get the new iid filepath.
	if (!m_iidFileSelectDlg.exec())
		return;

	std::string filePath = m_iidFileSelectDlg.selectedFiles()[0].toStdString();

	bool isIidFileOk = m_dataController->editIidFilePath(filePath);
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
void MainForm::showEvent(QShowEvent *event)
{
	QMainWindow::showEvent(event);

	// Make sure 'setWindowFilePath()' is called after QWidget::show() is called.
	// NOTE: this is a workaround for a bug in Qt.
	QString file_path = windowFilePath();
	setWindowFilePath("Anything to have a file path change at next line.");
	setWindowFilePath(file_path);
}

//////////////////////////////////////////////////////////////////////////
void MainForm::setCurrentFilePath( const std::string& filePath )
{
	// Update the current path.
	QString filePath_asQString = QString().fromStdString(filePath);
	QSettings settings;
	settings.setValue("CurrentFilePath", filePath_asQString);

	// Update the window.
	if (filePath == "")
		setWindowFilePath("untitled.iob");
	else
		setWindowFilePath(filePath.c_str());

	// Update the settings' list of recent files.
	if (filePath != "")
	{
		QStringList recentFilesList = settings.value("RecentFilesList").toStringList();
		recentFilesList.removeAll(filePath_asQString);
		recentFilesList.prepend(filePath_asQString);
		while (recentFilesList.size() > RECENT_FILES_MAX_NUM)
			recentFilesList.removeLast();
	
		settings.setValue("RecentFilesList", recentFilesList);
	}

	// Update recent file actions.
	updateRecentFileActions();
}

//////////////////////////////////////////////////////////////////////////
void MainForm::updateRecentFileActions()
{
	QSettings settings;
	QStringList recentFilesList = settings.value("RecentFilesList").toStringList();

	m_recentFilesSeparatorAction->setVisible(recentFilesList.size() > 0);

	for (int i = 0; i < RECENT_FILES_MAX_NUM; ++i)
		m_recentFileActions[i]->setVisible(false);

	for (int i = 0; i < recentFilesList.size(); ++i)
	{
		if (!recentFilesList[i].isEmpty())
		{
			m_recentFileActions[i]->setText(QFileInfo(recentFilesList[i]).fileName());
			m_recentFileActions[i]->setData(recentFilesList[i]);
			m_recentFileActions[i]->setVisible(true);
		}
	}
}

} // namespace SK.