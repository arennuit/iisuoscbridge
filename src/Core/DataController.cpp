#include "DataController.h"

#include "Core/DataBase/PathMap.h"
#include "LogSystem/Logger.h"

#include "src/pugixml.hpp"

namespace SK
{

DataController* DataController::sm_instance = 0;

//////////////////////////////////////////////////////////////////////////
DataController::DataController() :
	m_dataBase(DataBase::GetInstance()),
	m_iisuManager(DataBase::GetInstance()),
	m_selectedPathMap(0)
{
	assert(m_dataBase);

	// Init iisu.
	m_iisuManager.initIisu();
}

//////////////////////////////////////////////////////////////////////////
DataController::~DataController()
{
	// Pause streaming.
	m_iisuManager.pauseStream();

	// Term iisu.
	m_iisuManager.termIisu();
}

//////////////////////////////////////////////////////////////////////////
void DataController::CreateInstance()
{
	if (!sm_instance)
		sm_instance = new DataController();
}

//////////////////////////////////////////////////////////////////////////
void DataController::DestroyInstance()
{
	if (sm_instance)
		delete sm_instance;
}

//////////////////////////////////////////////////////////////////////////
bool DataController::editIidFilePath( const std::string& newIidFilePath )
{
	// Update the database.
	m_dataBase->setIidFilePath(newIidFilePath);

	// Load the IID script.
	return m_iisuManager.loadIidGraph(newIidFilePath);
}

//////////////////////////////////////////////////////////////////////////
void DataController::toggleResumePause()
{
	if (m_dataBase->getIsObservationOn() == false)
		m_iisuManager.resumeStream();
	else
		m_iisuManager.pauseStream();
}

//////////////////////////////////////////////////////////////////////////
void DataController::editFoldAndNameJointsOption( bool isFoldAndNameJoints )
{
	m_dataBase->setIsFoldAndNameJoints(isFoldAndNameJoints);
}

//////////////////////////////////////////////////////////////////////////
const PathMap* DataController::addPathMap()
{
	const PathMap* newPathMap = m_dataBase->addPathMap(m_selectedPathMap);

	// Update selection.
	// TODO: to be done as a callback in the AppDataController.
	if (newPathMap)
		editSelection(newPathMap);

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
const PathMap* DataController::insertPathMap()
{
	const PathMap* newPathMap = m_dataBase->insertPathMap(m_selectedPathMap);
	
	// Update selection.
	// TODO: to be done as a callback in the AppDataController.
	if (newPathMap)
		editSelection(newPathMap);

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
const PathMap* DataController::addChildMap()
{
	const PathMap* newPathMap = m_dataBase->addChildMap(m_selectedPathMap);

	// Update selection.
	// TODO: to be done as a callback in the AppDataController.
	if (newPathMap)
		editSelection(newPathMap);

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
bool DataController::deletePathMap()
{
	// Update selection (1/2).
	const PathMap* parentPathMap = m_selectedPathMap->getParent();

	// Actually perform the action.
	bool retState = m_dataBase->deletePathMap(m_selectedPathMap);

	if (!retState)
		return false;

	// Update selection (2/2).
	// TODO: to be done as a callback in the AppDataController.
	editSelection(parentPathMap);

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool DataController::clearPathMaps()
{
	bool retState = m_dataBase->clearPathMaps();

	if (!retState)
		return false;

	// Update selection.
	// TODO: to be done as a callback in the AppDataController.
	editSelection(0);

	return true;
}

//////////////////////////////////////////////////////////////////////////
void DataController::newProject()
{
	
}

//////////////////////////////////////////////////////////////////////////
void DataController::saveProjectToFile(std::string& filePath)
{
	// Create the xml document and root node. 
	pugi::xml_document docXml;
	pugi::xml_node node_iisuOscBride = docXml.append_child("IisuOscBridge");

	// Iid file path, IP address and port are stored as attributes.
	node_iisuOscBride.append_attribute("iidFilePath") = m_dataBase->getIidFilePath().c_str();
	node_iisuOscBride.append_attribute("ipAddress") = m_dataBase->getIpAddress().c_str();
	node_iisuOscBride.append_attribute("ipPort") = m_dataBase->getPort();
	node_iisuOscBride.append_attribute("foldAndNameJoints") = m_dataBase->getIsFoldAndNameJoints();

	// Recursive dive into PathMaps.
	saveProjectToFile_recursive(node_iisuOscBride, m_dataBase->getPathMapsRoot());

	docXml.save_file(filePath.c_str());
}

//////////////////////////////////////////////////////////////////////////
void DataController::loadProjectFromFile(std::string& filePath)
{

}

//////////////////////////////////////////////////////////////////////////
void DataController::saveProjectToFile_recursive( pugi::xml_node& parent, const PathMap* pathMap )
{
	// Create node and attributes.
	pugi::xml_node node_pathMap = parent.append_child("PathMap");

	node_pathMap.append_attribute("oscPathBit") = pathMap->getOscPathBit().c_str();
	node_pathMap.append_attribute("iisuPath") = pathMap->getIisuPath().c_str();

	// Recursion into children.
	for (uint i = 0; i < pathMap->getChildren().size(); ++i)
		saveProjectToFile_recursive(node_pathMap, pathMap->getChildren()[i]);
}

} // namespace SK.