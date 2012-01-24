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

	/// \name API.
	//@{
	void setup();
	//@}

	/// \name Callbacks.
	//@{
	void onEditSelection(const PathMap* newSelectedPathMap);
	void onLoadProjectFromFile(std::string& filePath);
	void onSaveProjectToFile(std::string& filePath);

	void onReset();

	void onIpAddressChanged(const std::string& ipAddress);
	void onIpPortChanged(int ipPort);
	void onIidFilePathChanged(const std::string& iidFilePath);
	void decorateStreamChanged(bool decorateStream);

	void onAddPathMap(const PathMap* newPathMap);
	void onInsertPathMap(const PathMap* newPathMap);
	void onAddChildMap(const PathMap* newPathMap);
	void onDeletePathMap(const PathMap* pathMapToBeDeleted);
	void onClearPathMaps();
	void onEditPathMap(const PathMap* pathMap);

	void onMocapStateChanged(bool mocapState);
	void onOscPacketSizeChanged(uint oscPacketSize);
	//@}

protected slots:

	/// \name UI -> app logic.
	//@{
	void onStartStopToggleButtonClicked() {m_dataController->toggleResumePause();}

	void onSelectionModelCurrentChanged( const QModelIndex& newModelIndex, const QModelIndex& oldModelIndex );

	void onOpenActionTriggered();
	void onNewActionTriggered();
	void onSaveActionTriggered();
	void onSaveAsActionTriggered();
	void onQuitActionTriggered() {QApplication::quit();}
	void openRecentFile();

	void onIpAddressEditEditingFinished() {m_dataController->editIpAddress(ui.m_ipAddressEdit->text().toStdString());}
	void onIpPortEditEditingFinished() {m_dataController->editIpPort(ui.m_ipPortEdit->text().toInt());}
	void onIidFilePathEditEditingFinished();
	void onIidFilePathButtonClicked();
	void onDecorateStreamCheckBoxClicked() {m_dataController->editDecorateStreamOption(ui.m_decorateStreamCheckBox->isChecked());}

	void onAddMapButtonClicked() {m_dataController->addPathMap();}
	void onInsertMapButtonClicked() {m_dataController->insertPathMap();}
	void onAddChildMapButtonClicked() {m_dataController->addChildMap();}
	void onDeleteMapButtonClicked() {m_dataController->deletePathMap();}
	void onClearMapsButtonClicked() {m_dataController->clearPathMaps();}

	void onMapsViewActionTriggered() {ui.m_tabs->setCurrentWidget(ui.m_mapsTab);}
	void onLogViewActionTriggered() {ui.m_tabs->setCurrentWidget(ui.m_logTab);}
	void onFullScreenAction();
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

	void showEvent(QShowEvent *event) SK_OVERRIDE; ///< Workaround for a bug in Qt.
	void setCurrentFilePath(std::string& filePath);
	void updateRecentFileActions();
	QAction* m_recentFilesSeparatorAction;
	QAction* m_recentFileActions[RECENT_FILES_MAX_NUM];

	QStandardItem* m_selectedItem;

	std::map<const PathMap*, QStandardItem*> m_pathMapItemMap;
	void addChildrenToArray_recursive(PathMap* pathMap, std::vector<PathMap*>& pathMapsToBeDeleted);
};

} // namespace SK.