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
	virtual void editIpAddress(const std::string& newIpAddress) {m_dataBase->setIpAddress(newIpAddress);}
	virtual void editPort(int newPort) {m_dataBase->setPort(newPort);}
	virtual bool editIidFilePath(const std::string& newIidFilePath);

	virtual void toggleResumePause();

	virtual void editFoldAndNameJointsOption(bool isFoldAndNameJoints);

	virtual void editSelection(const PathMap* newSelectedPathMap) {m_selectedPathMap = (PathMap*)newSelectedPathMap;}

	virtual const PathMap* addPathMap() {return m_dataBase->addPathMap(m_selectedPathMap);}
	virtual const PathMap* insertPathMap() {return m_dataBase->insertPathMap(m_selectedPathMap);}
	virtual const PathMap* addChildMap() {return m_dataBase->addChildMap(m_selectedPathMap);}
	virtual bool deletePathMap() {return m_dataBase->deletePathMap(m_selectedPathMap);}
	virtual bool clearPathMaps() {return m_dataBase->clearPathMaps();}

	virtual void newProject();
	virtual void saveProjectToFile(std::string& filePath);
	virtual void loadProjectFromFile(std::string& filePath);
	//@}

	/// \name Helpers.
	//@{
	virtual void retrieveIisuDataPaths(std::vector<std::string>& iisuDataPaths) {m_iisuManager.retrieveIisuDataPaths(iisuDataPaths);}
	//@}

	/// \name Callbacks.
	//@{
	virtual void onAddPathMap(const PathMap* newPathMap) {editSelection(newPathMap);}
	virtual void onInsertPathMap(const PathMap* newPathMap) {editSelection(newPathMap);}
	virtual void onAddChildMap(const PathMap* newPathMap) {editSelection(newPathMap);}
	virtual void onDeletePathMap(const PathMap* pathMapToBeDeleted);
	virtual void onClearPathMaps() {editSelection(0);}

	virtual void onIsObservationOnChanged(bool isObservationOn) {}
	virtual void onOscPacketSizeChanged(uint oscPacketSize) {}
	//@}

protected:
	DataController();
	virtual ~DataController();

	DataBase* m_dataBase;

	IisuManager m_iisuManager;

	PathMap* m_selectedPathMap;

	void saveProjectToFile_recursive(pugi::xml_node& parent, const PathMap* pathMap);
};

} // namespace SK.

