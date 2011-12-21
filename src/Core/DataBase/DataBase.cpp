#include "DataBase.h"
#include "PathMap.h"

#define NEW_OSC_PATH_BIT "New Osc Path Bit"
#define NEW_IISU_PATH "New Iisu Path"

namespace SK
{

DEFINE_DATA_BASE(DataBase, AbstractDataBase)

//////////////////////////////////////////////////////////////////////////
DataBase::DataBase()
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

	m_pathMapsRoot = new PathMap("iisu", "");

	// Users 1.
	PathMap* path_user1 = m_pathMapsRoot->addChildMap("user1", "");
	//path_user1->addChildMap("centroids", "USER1.SHAPE.CENTROIDS.Positions");
	path_user1->addChildMap("status", "USER1.SKELETON.Status");
	PathMap* path_joints1 = path_user1->addChildMap("joints", "");
	path_joints1->addChildMap("positions", "USER1.SKELETON.KeyPoints");
	path_joints1->addChildMap("confidences", "USER1.SKELETON.KeyPointsConfidence");

	m_isObservationOn = false;

	m_isFoldAndNameJoints = true;

	m_oscPacketSize = 0;
}

//////////////////////////////////////////////////////////////////////////
const PathMap* DataBase::addPathMap(PathMap* siblingPathMap)
{
	assert(!(siblingPathMap && !m_pathMapsRoot));

	// If there are already PathMaps in the tree but siblingPathMap == 0, we don't know where to attach the new PathMap.
	if (!siblingPathMap && m_pathMapsRoot)
		return 0;

	// Nominal case: siblingPathMap !0 && m_pathMapsRoot != 0.
	// NOTE: with the assert above we know m_pathMapsRoot != 0 if siblingPathMap != 0.
	if (siblingPathMap) 
		return siblingPathMap->addPathMap(NEW_OSC_PATH_BIT, NEW_IISU_PATH);

	// Case where siblingPathMap == 0 && m_pathMapsRoot == 0.
	PathMap* newPathMap = new PathMap(NEW_OSC_PATH_BIT, NEW_IISU_PATH);
	assert(newPathMap);

	assert(!m_pathMapsRoot);
	m_pathMapsRoot = newPathMap;

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
const PathMap* DataBase::insertPathMap(PathMap* siblingPathMap)
{
	assert(!(siblingPathMap && !m_pathMapsRoot));

	// If there are already PathMaps in the tree but siblingPathMap == 0, we don't know where to attach the new PathMap.
	if (!siblingPathMap && m_pathMapsRoot)
		return 0;

	// Nominal case: siblingPathMap !0 && m_pathMapsRoot != 0.
	// NOTE: with the assert above we know m_pathMapsRoot != 0 if siblingPathMap != 0.
	if (siblingPathMap) 
		return siblingPathMap->insertPathMap(NEW_OSC_PATH_BIT, NEW_IISU_PATH);
	
	// Case where siblingPathMap == 0 && m_pathMapsRoot == 0.
	PathMap* newPathMap = new PathMap(NEW_OSC_PATH_BIT, NEW_IISU_PATH);
	assert(newPathMap);

	assert(!m_pathMapsRoot);
	m_pathMapsRoot = newPathMap;

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
const PathMap* DataBase::addChildMap(PathMap* parentPathMap)
{
	assert(!(parentPathMap && !m_pathMapsRoot));

	// If there are already PathMaps in the tree but parentPathMap == 0, we don't know where to attach the new PathMap.
	if (!parentPathMap && m_pathMapsRoot)
		return 0;

	// Nominal case: parentPathMap !0 && m_pathMapsRoot != 0.
	// NOTE: with the assert above we know m_pathMapsRoot != 0 if parentPathMap != 0.
	if (parentPathMap) 
		return parentPathMap->addChildMap(NEW_OSC_PATH_BIT, NEW_IISU_PATH);

	// Case where parentPathMap == 0 && m_pathMapsRoot == 0.
	PathMap* newPathMap = new PathMap(NEW_OSC_PATH_BIT, NEW_IISU_PATH);
	assert(newPathMap);

	assert(!m_pathMapsRoot);
	m_pathMapsRoot = newPathMap;

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
bool DataBase::deletePathMap( PathMap* pathMap )
{
	if (!pathMap)
		return false;

	delete pathMap;

	// Check there is no more root PathMap.
	if (!pathMap->getParent())
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