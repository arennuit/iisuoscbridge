#include "DataBase.h"
#include "PathMapItem.h"

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
	delete m_pathsTreeRoot;
}

//////////////////////////////////////////////////////////////////////////
void DataBase::setDefaultValues()
{
	m_ipAddress = std::string("127.0.0.1");
	m_port = 8000;

	m_pathsTreeRoot = new PathMapItem("iisu");
	// Users #.

	PathMapItem* path_user1 = new PathMapItem("user1", m_pathsTreeRoot);
	//new Vector3ArrayPathMapItem("centroids", "USER1.SHAPE.CENTROIDS.Positions", path_user1);
	new BooleanPathMapItem("status", "USER1.SKELETON.Status", path_user1);
	PathMapItem* path_joints1 = new PathMapItem("joints", path_user1);
	new Vector3ArrayPathMapItem("positions", "USER1.SKELETON.KeyPoints", path_joints1);
	new FloatArrayPathMapItem("confidences", "USER1.SKELETON.KeyPointsConfidence", path_joints1);

	PathMapItem* path_user2 = new PathMapItem("user2", m_pathsTreeRoot);
	//new Vector3ArrayPathMapItem("centroids", "USER2.SHAPE.CENTROIDS.Positions", path_user2);
	new BooleanPathMapItem("status", "USER2.SKELETON.Status", path_user2);
	PathMapItem* path_joints2 = new PathMapItem("joints", path_user2);
	new Vector3ArrayPathMapItem("positions", "USER2.SKELETON.KeyPoints", path_joints2);
	new FloatArrayPathMapItem("confidences", "USER2.SKELETON.KeyPointsConfidence", path_joints2);

	m_isObservationOn = false;

	m_isFoldAndNameJoints = true;

	m_oscPacketSize = 0;
}

} // namespace SK.