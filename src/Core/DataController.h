#pragma once

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
class DataController
{
public:
	/// \name Singleton management.
	//@{
	static void CreateInstance();
	static void DestroyInstance();
	static DataController* GetInstance() {return sm_instance;}
	//@}

	/// \name Helpers.
	//@{
	void retrieveIisuDataPaths(std::vector<std::string>& iisuDataPaths) {m_iisuManager.retrieveIisuDataPaths(iisuDataPaths);}
	//@}

	/// \name API.
	//@{
	void editIpAddress(const std::string& newIpAddress) {m_dataBase->setIpAddress(newIpAddress);}
	void editPort(int newPort) {m_dataBase->setPort(newPort);}
	bool editIidFilePath(const std::string& newIidFilePath);

	void toggleResumePause();

	void editFoldAndNameJointsOption(bool isFoldAndNameJoints);

	void onSelectionChanged(const PathMap* newSelectedPathMap) {m_selectedPathMap = (PathMap*)newSelectedPathMap;}

	const PathMap* addPathMap() {return m_dataBase->addPathMap(m_selectedPathMap);}
	const PathMap* insertPathMap() {return m_dataBase->insertPathMap(m_selectedPathMap);}
	const PathMap* addChildMap() {return m_dataBase->addChildMap(m_selectedPathMap);}
	void deletePathMap() {m_dataBase->deletePathMap(m_selectedPathMap);}
	void clearPathMaps() {m_dataBase->clearPathMaps();}

	void newProject();
	void saveProjectToFile(std::string& filePath);
	void loadProjectFromFile(std::string& filePath);
	//@}

protected:
	/// \name Singleton management.
	//@{
	DataController();
	virtual ~DataController();

	static DataController* sm_instance;
	//@}

	DataBase* m_dataBase;

	IisuManager m_iisuManager;

	PathMap* m_selectedPathMap;

	void saveProjectToFile_recursive(pugi::xml_node& parent, const PathMap* pathMap);
};

} // namespace SK.

