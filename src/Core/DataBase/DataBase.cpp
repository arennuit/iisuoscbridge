#include "DataBase.h"
#include "PathMap.h"

namespace SK
{

DEFINE_DATA_BASE(DataBase, AbstractDataBase)

std::string DataBase::sm_ipAddressDefaultValue = std::string("127.0.0.1");
int DataBase::sm_ipPortDefaultValue = 8000;
std::string DataBase::sm_iidFilePathDefaultValue = std::string();
PathMap* DataBase::sm_pathMapsRootDefaultValue = 0;
bool DataBase::sm_mocapStateDefaultValue = false;
bool DataBase::sm_decorateStreamDefaultValue = true;
uint DataBase::sm_oscPacketSizeDefaultValue = 0;

//////////////////////////////////////////////////////////////////////////
DataBase::DataBase() : 

	m_ipAddress(sm_ipAddressDefaultValue),
	m_ipPort(sm_ipPortDefaultValue),
	m_iidFilePath(sm_iidFilePathDefaultValue),

	m_pathMapsRoot(sm_pathMapsRootDefaultValue),

	m_mocapState(sm_mocapStateDefaultValue),

	m_decorateStream(sm_decorateStreamDefaultValue),
	m_oscPacketSize(sm_oscPacketSizeDefaultValue)
{
}

//////////////////////////////////////////////////////////////////////////
DataBase::~DataBase()
{
	if (m_pathMapsRoot)
		delete m_pathMapsRoot;
}

//////////////////////////////////////////////////////////////////////////
void DataBase::reset()
{
	// The data cannot be edited while streaming.
	if (m_mocapState)
		return;

	setIpAddress(sm_ipAddressDefaultValue);
	setIpPort(sm_ipPortDefaultValue);
	setIidFilePath(sm_iidFilePathDefaultValue);

	clearPathMaps();

	setMocapState(sm_mocapStateDefaultValue);

	setDecorateStream(sm_decorateStreamDefaultValue);
	setOscPacketSize(sm_oscPacketSizeDefaultValue);
}

//////////////////////////////////////////////////////////////////////////
const PathMap* DataBase::addPathMap(const PathMap* siblingPathMap, const std::string& oscPathBit /*= NEW_OSC_PATH_BIT*/, const std::string& iisuPath /*= NEW_IISU_PATH*/)
{
	assert(!(siblingPathMap && !m_pathMapsRoot));

	// If there are already PathMaps in the tree but siblingPathMap == 0, we don't know where to attach the new PathMap.
	if (!siblingPathMap && m_pathMapsRoot)
		return 0;

	// Nominal case: siblingPathMap !0 && m_pathMapsRoot != 0.
	// NOTE: with the assert above we know m_pathMapsRoot != 0 if siblingPathMap != 0.
	if (siblingPathMap) 
		return ((PathMap*)siblingPathMap)->addPathMap(oscPathBit, iisuPath);

	// Case where siblingPathMap == 0 && m_pathMapsRoot == 0.
	PathMap* newPathMap = new PathMap(oscPathBit, iisuPath);
	assert(newPathMap);

	assert(!m_pathMapsRoot);
	m_pathMapsRoot = newPathMap;

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
const PathMap* DataBase::insertPathMap(const PathMap* siblingPathMap, const std::string& oscPathBit /*= NEW_OSC_PATH_BIT*/, const std::string& iisuPath /*= NEW_IISU_PATH*/)
{
	assert(!(siblingPathMap && !m_pathMapsRoot));

	// If there are already PathMaps in the tree but siblingPathMap == 0, we don't know where to attach the new PathMap.
	if (!siblingPathMap && m_pathMapsRoot)
		return 0;

	// Nominal case: siblingPathMap !0 && m_pathMapsRoot != 0.
	// NOTE: with the assert above we know m_pathMapsRoot != 0 if siblingPathMap != 0.
	if (siblingPathMap) 
		return ((PathMap*)siblingPathMap)->insertPathMap(oscPathBit, iisuPath);
	
	// Case where siblingPathMap == 0 && m_pathMapsRoot == 0.
	PathMap* newPathMap = new PathMap(oscPathBit, iisuPath);
	assert(newPathMap);

	assert(!m_pathMapsRoot);
	m_pathMapsRoot = newPathMap;

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
const PathMap* DataBase::addChildMap(const PathMap* parentPathMap, const std::string& oscPathBit /*= NEW_OSC_PATH_BIT*/, const std::string& iisuPath /*= NEW_IISU_PATH*/)
{
	assert(!(parentPathMap && !m_pathMapsRoot));

	// If there are already PathMaps in the tree but parentPathMap == 0, we don't know where to attach the new PathMap.
	if (!parentPathMap && m_pathMapsRoot)
		return 0;

	// Nominal case: parentPathMap !0 && m_pathMapsRoot != 0.
	// NOTE: with the assert above we know m_pathMapsRoot != 0 if parentPathMap != 0.
	if (parentPathMap) 
		return ((PathMap*)parentPathMap)->addChildMap(oscPathBit, iisuPath);

	// Case where parentPathMap == 0 && m_pathMapsRoot == 0.
	PathMap* newPathMap = new PathMap(oscPathBit, iisuPath);
	assert(newPathMap);

	assert(!m_pathMapsRoot);
	m_pathMapsRoot = newPathMap;

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
bool DataBase::deletePathMap( const PathMap* pathMap )
{
	if (!pathMap)
		return false;

	// Get the parent before deleting pathMap (parentMap is used to reset m_pathMapsRoot).
	PathMap* parentMap = pathMap->getParent();

	// Delete.
	delete (PathMap*)pathMap;

	// Check there is no more root PathMap.
	if (!parentMap)
		m_pathMapsRoot = 0;

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool DataBase::clearPathMaps()
{
	if (!m_pathMapsRoot)
		return true;

	delete m_pathMapsRoot;

	// There is no more root PathMap.
	m_pathMapsRoot = 0;

	return true;
}

} // namespace SK.