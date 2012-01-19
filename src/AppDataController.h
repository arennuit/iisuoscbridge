#pragma once

#include "Core/DataController.h"
#include "MainForm.h"

namespace SK
{

/// \brief This class adds the UI update service on data change.
/// Read the large comment in AppDataBase.h to get an overview of the application's architecture.
class AppDataController : public DataController
{
	DECLARE_DATA_BASE(AppDataController)

public:

	/// \name API.
	//@{
	void editSelection(const PathMap* newSelectedPathMap) SK_OVERRIDE;

	void loadProjectFromFile(std::string& filePath) SK_OVERRIDE;
	void newProject() SK_OVERRIDE;
	void saveProjectToFile(std::string& filePath) SK_OVERRIDE;
	//@}

	/// \name Callbacks.
	//@{
	void onAddPathMap(const PathMap* newPathMap) SK_OVERRIDE;
	void onInsertPathMap(const PathMap* newPathMap) SK_OVERRIDE;
	void onAddChildMap(const PathMap* newPathMap) SK_OVERRIDE;
	void onDeletePathMap(const PathMap* pathMapToBeDeleted) SK_OVERRIDE;
	void onClearPathMaps() SK_OVERRIDE;

	void onIpAddressChanged(const std::string& ipAddress) SK_OVERRIDE;
	void onIpPortChanged(int ipPort) SK_OVERRIDE;
	void onIidFilePathChanged(const std::string& iidFilePath) SK_OVERRIDE;
	bool onMocapStateChanged(bool desiredMocapState) SK_OVERRIDE;
	void onDecorateStreamChanged(bool decorateStream) SK_OVERRIDE;
	void onOscPacketSizeChanged(uint oscPacketSize) SK_OVERRIDE;
	//@}

	void setMainForm(MainForm* mainForm) {m_mainForm = mainForm;}

protected:
	AppDataController() : DataController(), m_mainForm(0) {}
	virtual ~AppDataController() {}

	MainForm* m_mainForm;
};

} // namespace SK.