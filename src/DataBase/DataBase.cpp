#include "DataBase.h"
#include "DataObjects/PathMap.h"

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

	m_pathMapsRoot = new PathMap("iisu");

	// Users #.
	PathMap* path_user1 = new PathMap("user1", "", m_pathMapsRoot);
	//new PathMap("centroids", "USER1.SHAPE.CENTROIDS.Positions", path_user1);
	new PathMap("status", "USER1.SKELETON.Status", path_user1);
	PathMap* path_joints1 = new PathMap("joints", "", path_user1);
	new PathMap("positions", "USER1.SKELETON.KeyPoints", path_joints1);
	new PathMap("confidences", "USER1.SKELETON.KeyPointsConfidence", path_joints1);

	m_isObservationOn = false;

	m_isFoldAndNameJoints = true;

	m_oscPacketSize = 0;
}

} // namespace SK.