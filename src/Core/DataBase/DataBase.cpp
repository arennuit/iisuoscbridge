#include "DataBase.h"
#include "PathMap.h"

namespace SK
{

DEFINE_DATA_BASE(DataBase, AbstractDataBase)

//////////////////////////////////////////////////////////////////////////
DataBase::DataBase() : 
	m_pathMapsRoot(0)
{
	setDefaultValues();
}

//////////////////////////////////////////////////////////////////////////
DataBase::~DataBase()
{
	if (m_pathMapsRoot)
		delete m_pathMapsRoot;
}

//////////////////////////////////////////////////////////////////////////
void DataBase::setDefaultValues()
{
	m_ipAddress = "127.0.0.1";
	m_port = 8000;
	m_iidFilePath = "";

	// Root.
	addPathMap(0, "iisu", "");

	// Users 1.
	const PathMap* path_user1 = addChildMap(m_pathMapsRoot, "user1", "");
	//addChildMap(path_user1, "centroids", "USER1.SHAPE.CENTROIDS.Positions");
	addChildMap(path_user1, "status", "USER1.SKELETON.Status");
	const PathMap* path_joints1 = addChildMap(path_user1, "joints", "");
	addChildMap(path_joints1, "positions", "USER1.SKELETON.KeyPoints");
	addChildMap(path_joints1, "confidences", "USER1.SKELETON.KeyPointsConfidence");

	m_mocapState = false;

	m_decorateStream = true;

	m_oscPacketSize = 0;
}

//////////////////////////////////////////////////////////////////////////
void DataBase::reset()
{
	// The data cannot be edited while streaming.
	if (m_mocapState)
		return;

	setMocapState(false);

	setIpAddress("127.0.0.1");
	setPort(8000);
	setIidFilePath("");

	clearPathMaps();

	setDecorateStream(true);
	setOscPacketSize(0);
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