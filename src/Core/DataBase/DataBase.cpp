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
PathMap* DataBase::addPathMap(PathMap* siblingPathMap)
{
	if (!siblingPathMap)
		return 0;

	return siblingPathMap->addPathMap(NEW_OSC_PATH_BIT, NEW_IISU_PATH);
}

//////////////////////////////////////////////////////////////////////////
PathMap* DataBase::insertPathMap(PathMap* siblingPathMap)
{
	if (!siblingPathMap)
		return 0;

	return siblingPathMap->insertPathMap(NEW_OSC_PATH_BIT, NEW_IISU_PATH);
}


//////////////////////////////////////////////////////////////////////////
PathMap* DataBase::addChildMap(PathMap* parentPathMap)
{
	if (!parentPathMap)
		return 0;

	return parentPathMap->addChildMap(NEW_OSC_PATH_BIT, NEW_IISU_PATH);
}

//////////////////////////////////////////////////////////////////////////
void DataBase::deletePathMap(PathMap* pathMap)
{
	if (!pathMap)
		return;

	if (!pathMap->getParent())
		m_pathMapsRoot = 0;

	delete pathMap;
}

//////////////////////////////////////////////////////////////////////////
void DataBase::clearPathMaps()
{
	if (m_pathMapsRoot)
	{
		delete m_pathMapsRoot;
		m_pathMapsRoot = 0;
	}
}

} // namespace SK.