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
void DataController::editDecorateStreamOption( bool decorateStream )
{
	m_dataBase->setDecorateStream(decorateStream);
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
	node_iisuOscBride.append_attribute("decorateStream") = m_dataBase->getDecorateStream();

	// Recursive dive into PathMaps.
	saveProjectToFile_recursive(node_iisuOscBride, m_dataBase->getPathMapsRoot());

	// Actually save.
	bool isSaveOk = docXml.save_file(filePath.c_str());

	if (!isSaveOk)
	{
		SK_LOGGER(LOG_ERROR) << std::string("Could not create file ") + filePath + ".";
	}
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

//////////////////////////////////////////////////////////////////////////
void DataController::loadProjectFromFile(std::string& filePath)
{
	// Reset.
	m_dataBase->reset();

	// Load the file.
	pugi::xml_document docXml;
	pugi::xml_parse_result result = docXml.load_file(filePath.c_str());
	if (!result)
	{
		SK_LOGGER(LOG_ERROR) << std::string("Could not open file ") + filePath + ".";
		return;
	}

	// Node 'IisuOscBridge'.
	pugi::xml_node iisuOscBridge_node = docXml.child("IisuOscBridge");
	if (!iisuOscBridge_node)
	{
		SK_LOGGER(LOG_ERROR) << "Could not find node \'IisuOscBridge\' in file " + filePath + ".";
		return;
	}

	// Attribute 'iidFilePath'.
	pugi::xml_attribute iidFilePath_attrib = iisuOscBridge_node.attribute("iidFilePath");
	if (!iidFilePath_attrib)
	{
		SK_LOGGER(LOG_ERROR) << "Could not attribute \'iidFilePath\' in node \'IisuOscBridge\'.";
		return;
	}
	std::string iidFilePath = iidFilePath_attrib.value();
	m_dataBase->setIidFilePath(iidFilePath);

	// Attribute 'ipAddress'.
	pugi::xml_attribute ipAddress_attrib = iisuOscBridge_node.attribute("ipAddress");
	if (!ipAddress_attrib)
	{
		SK_LOGGER(LOG_ERROR) << "Could not attribute \'ipAddress\' in node \'IisuOscBridge\'.";
		return;
	}
	std::string ipAddress = ipAddress_attrib.value();
	m_dataBase->setIpAddress(ipAddress);

	// Attribute 'ipPort'.
	pugi::xml_attribute ipPort_attrib = iisuOscBridge_node.attribute("ipPort");
	if (!ipPort_attrib)
	{
		SK_LOGGER(LOG_ERROR) << "Could not attribute \'ipPort\' in node \'IisuOscBridge\'.";
		return;
	}
	int ipPort;
	std::istringstream(ipPort_attrib.value()) >> ipPort;
	m_dataBase->setPort(ipPort);

	// Attribute 'decorateStream'.
	pugi::xml_attribute decorateStream_attrib = iisuOscBridge_node.attribute("decorateStream");
	if (!decorateStream_attrib)
	{
		SK_LOGGER(LOG_ERROR) << "Could not attribute \'decorateStream\' in node \'IisuOscBridge\'.";
		return;
	}
	std::string decorateStream = decorateStream_attrib.value();
	m_dataBase->setDecorateStream(decorateStream == "true" ? true : false);
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