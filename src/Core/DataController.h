#pragma once

#include "Core/AbstractDataController.h"
#include "Core/DataBase/DataBase.h"
#include "Core/IisuManager/IisuManager.h"
#include <string>

namespace pugi
{
	class xml_node;
}

namespace SK
{

class PathMap;

//////////////////////////////////////////////////////////////////////////
/// \brief This class makes the different parts of the system work together.
///
/// The DataController keeps track of the selection and calls actions on it depending on its own state.
class DataController : public AbstractDataController
{
	DECLARE_DATA_CONTROLLER(DataController)

public:

	/// \name API.
	//@{
	virtual void toggleResumePause();

	virtual void editSelection(const PathMap* newSelectedPathMap) {m_selectedPathMap = (PathMap*)newSelectedPathMap;}

	virtual void loadProjectFromFile(std::string& filePath);
	virtual void newProject() {m_dataBase->reset();}
	virtual void saveProjectToFile(std::string& filePath);
	//@}

	/// \name Editors.
	//@{
	virtual void editIpAddress(const std::string& newIpAddress) {m_dataBase->setIpAddress(newIpAddress);}
	virtual void editIpPort(int newIpPort) {m_dataBase->setIpPort(newIpPort);}
	virtual bool editIidFilePath(const std::string& newIidFilePath);
	virtual void editDecorateStreamOption(bool decorateStream) {m_dataBase->setDecorateStream(decorateStream);}

	virtual const PathMap* addPathMap() {return m_dataBase->addPathMap(m_selectedPathMap);}
	virtual const PathMap* insertPathMap() {return m_dataBase->insertPathMap(m_selectedPathMap);}
	virtual const PathMap* addChildMap() {return m_dataBase->addChildMap(m_selectedPathMap);}
	virtual bool deletePathMap() {return m_dataBase->deletePathMap(m_selectedPathMap);}
	virtual bool clearPathMaps() {return m_dataBase->clearPathMaps();}
	virtual void editPathMap(PathMap* pathMap, const std::string& oscPathBit, const std::string& iisuPath) {m_dataBase->editPathMap(pathMap, oscPathBit, iisuPath);}
	//@}

	/// \name Callbacks.
	//@{
	virtual void onIpAddressChanged(const std::string& ipAddress) {}
	virtual void onIpPortChanged(int ipPort) {}
	virtual void onIidFilePathChanged(const std::string& iidFilePath) {}
	virtual void onDecorateStreamChanged(bool decorateStream) {}

	virtual void onAddPathMap(const PathMap* newPathMap) {editSelection(newPathMap);}
	virtual void onInsertPathMap(const PathMap* newPathMap) {editSelection(newPathMap);}
	virtual void onAddChildMap(const PathMap* newPathMap) {editSelection(newPathMap);}
	virtual void onDeletePathMap(const PathMap* pathMapToBeDeleted);
	virtual void onClearPathMaps() {editSelection(0);}
	virtual void onEditPathMap(const PathMap* pathMap) {}

	virtual void onOscPacketSizeChanged(uint oscPacketSize) {}
	virtual bool onMocapStateChanged(bool desiredMocapState); ///< Returns the obtained mocap state (which may differ from desiredMocapState).
	//@}

	/// \name Helpers.
	//@{
	virtual void retrieveIisuDataPaths(std::vector<std::string>& iisuDataPaths) {m_iisuManager.retrieveIisuDataPaths(iisuDataPaths);}
	//@}

protected:
	DataController();
	virtual ~DataController();

	DataBase* m_dataBase;

	IisuManager m_iisuManager;

	PathMap* m_selectedPathMap;

	void saveProjectToFile_recursive(pugi::xml_node& parent, const PathMap* pathMap);
	void loadProjectFromFile_recursive( pugi::xml_node& pathMapNode, PathMap* parentPathMap );
};

} // namespace SK.

