#include "DataController.h"

#include "Core/DataBase/PathMap.h"
#include "LogSystem/Logger.h"

#include "src/pugixml.hpp"

namespace SK
{

DEFINE_DATA_CONTROLLER(DataController, AbstractDataController)

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
	if (m_dataBase->getMocapState() == false)
		m_dataBase->setMocapState(true);
	else
		m_dataBase->setMocapState(false);
}

//////////////////////////////////////////////////////////////////////////
void DataController::loadProjectFromFile( const std::string& filePath )
{
	// Load the file.
	pugi::xml_document docXml;
	pugi::xml_parse_result result = docXml.load_file(filePath.c_str());
	if (!result)
	{
		SK_LOGGER(LOG_ERROR) << std::string("Could not open file \'") + filePath + "\'.";
		return;
	}

	// Node 'IisuOscBridge'.
	pugi::xml_node iisuOscBridge_node = docXml.child("IisuOscBridge");
	if (!iisuOscBridge_node)
	{
		SK_LOGGER(LOG_ERROR) << "Unexpected formating of file\'" + filePath + "\'.";
		return;
	}

	// Reset current project to pave the way for the project about to be loaded.
	m_dataBase->reset();

	// Attribute 'iidFilePath'.
	pugi::xml_attribute iidFilePath_attrib = iisuOscBridge_node.attribute("iidFilePath");
	if (!iidFilePath_attrib)
	{
		SK_LOGGER(LOG_ERROR) << "Could not find attribute \'iidFilePath\' in node \'IisuOscBridge\'.";
		return;
	}
	std::string iidFilePath = iidFilePath_attrib.value();
	m_dataBase->setIidFilePath(iidFilePath);

	// Attribute 'ipAddress'.
	pugi::xml_attribute ipAddress_attrib = iisuOscBridge_node.attribute("ipAddress");
	if (!ipAddress_attrib)
	{
		SK_LOGGER(LOG_ERROR) << "Could not find attribute \'ipAddress\' in node \'IisuOscBridge\'.";
		return;
	}
	std::string ipAddress = ipAddress_attrib.value();
	m_dataBase->setIpAddress(ipAddress);

	// Attribute 'ipPort'.
	pugi::xml_attribute ipPort_attrib = iisuOscBridge_node.attribute("ipPort");
	if (!ipPort_attrib)
	{
		SK_LOGGER(LOG_ERROR) << "Could not find attribute \'ipPort\' in node \'IisuOscBridge\'.";
		return;
	}
	int ipPort;
	std::istringstream(ipPort_attrib.value()) >> ipPort;
	m_dataBase->setIpPort(ipPort);

	// Attribute 'decorateStream'.
	pugi::xml_attribute decorateStream_attrib = iisuOscBridge_node.attribute("decorateStream");
	if (!decorateStream_attrib)
	{
		SK_LOGGER(LOG_ERROR) << "Could not find attribute \'decorateStream\' in node \'IisuOscBridge\'.";
		return;
	}
	std::string decorateStream = decorateStream_attrib.value();
	m_dataBase->setDecorateStream(decorateStream == "true" ? true : false);

	// Recursive dive into PathMaps.
	loadProjectFromFile_recursive(iisuOscBridge_node, 0);
}

//////////////////////////////////////////////////////////////////////////
void DataController::loadProjectFromFile_recursive( pugi::xml_node& pathMapNode, PathMap* parentPathMap )
{
	PathMap* pathMap = 0;
	if (std::string(pathMapNode.name()) == "PathMap")
	{
		// Attribute 'oscPathBit'.
		pugi::xml_attribute oscPathBit_attrib = pathMapNode.attribute("oscPathBit");
		if (!oscPathBit_attrib)
		{
			SK_LOGGER(LOG_ERROR) << "Could not find attribute \'oscPathBit\' in node \'PathMap\'.";
			return;
		}
		std::string oscPathBit = oscPathBit_attrib.value();

		// Attribute 'iisuPath'.
		pugi::xml_attribute iisuPath_attrib = pathMapNode.attribute("iisuPath");
		if (!iisuPath_attrib)
		{
			SK_LOGGER(LOG_ERROR) << "Could not find attribute \'iisuPath\' in node \'PathMap\'.";
			return;
		}
		std::string iisuPath = iisuPath_attrib.value();

		// Create new PathMap.
		pathMap = (PathMap*)m_dataBase->addChildMap(parentPathMap, oscPathBit, iisuPath);
	}

	// Node 'PathMap'.
	for (pugi::xml_node childPathMapNode = pathMapNode.child("PathMap"); childPathMapNode; childPathMapNode = childPathMapNode.next_sibling("PathMap"))
	{
		loadProjectFromFile_recursive(childPathMapNode, pathMap);
	}
}

//////////////////////////////////////////////////////////////////////////
void DataController::saveProjectToFile( const std::string& filePath )
{
	// Create the xml document and root node. 
	pugi::xml_document docXml;
	pugi::xml_node node_iisuOscBride = docXml.append_child("IisuOscBridge");

	// Iid file path, IP address and port are stored as attributes.
	node_iisuOscBride.append_attribute("iidFilePath") = m_dataBase->getIidFilePath().c_str();
	node_iisuOscBride.append_attribute("ipAddress") = m_dataBase->getIpAddress().c_str();
	node_iisuOscBride.append_attribute("ipPort") = m_dataBase->getIpPort();
	node_iisuOscBride.append_attribute("decorateStream") = m_dataBase->getDecorateStream();

	// Recursive dive into PathMaps.
	saveProjectToFile_recursive(node_iisuOscBride, m_dataBase->getPathMapsRoot());

	// Actually save.
	bool isSaveOk = docXml.save_file(filePath.c_str());

	if (!isSaveOk)
	{
		SK_LOGGER(LOG_ERROR) << std::string("Could not create file \'") + filePath + "\'.";
	}
}

//////////////////////////////////////////////////////////////////////////
void DataController::saveProjectToFile_recursive( pugi::xml_node& parent, const PathMap* pathMap )
{
	if (!pathMap)
		return;

	// Create node and attributes.
	pugi::xml_node node_pathMap = parent.append_child("PathMap");

	node_pathMap.append_attribute("oscPathBit") = pathMap->getOscPathBit().c_str();
	node_pathMap.append_attribute("iisuPath") = pathMap->getIisuPath().c_str();

	// Recursion into children.
	for (uint i = 0; i < pathMap->getChildren().size(); ++i)
		saveProjectToFile_recursive(node_pathMap, pathMap->getChildren()[i]);
}

//////////////////////////////////////////////////////////////////////////
void DataController::onDeletePathMap(const PathMap* pathMapToBeDeleted)
{
	const PathMap* parentPathMap = pathMapToBeDeleted->getParent();

	editSelection(parentPathMap);
}

//////////////////////////////////////////////////////////////////////////
bool DataController::onMocapStateChanged( bool desiredMocapState )
{
	// Returns the new mocap state (it may differ from desiredMocapState).
	if (desiredMocapState == true)
		return m_iisuManager.resumeStream();

	return m_iisuManager.pauseStream();
}

} // namespace SK.