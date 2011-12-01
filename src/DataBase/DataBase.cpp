#include "DataBase.h"
#include "PathMap.h"

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

} // namespace SK.