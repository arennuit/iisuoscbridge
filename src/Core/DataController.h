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

	void onSelectionChanged(const PathMap* newSelectedPathMap) {m_selectedPathMap = newSelectedPathMap;}

	const PathMap* addPathMap(const PathMap* siblingPathMap) {return m_dataBase->addPathMap((PathMap*)siblingPathMap);}
	const PathMap* insertPathMap(const PathMap* siblingPathMap) {return m_dataBase->insertPathMap((PathMap*)siblingPathMap);}
	const PathMap* addChildMap(const PathMap* parentPathMap) {return m_dataBase->addChildMap((PathMap*)parentPathMap);}
	void deletePathMap(const PathMap* pathMap) {m_dataBase->deletePathMap((PathMap*)pathMap);}
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

	const PathMap* m_selectedPathMap;

	void saveProjectToFile_recursive(pugi::xml_node& parent, const PathMap* pathMap);
};

} // namespace SK.

