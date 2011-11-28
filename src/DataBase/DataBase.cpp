#include "DataBase.h"
#include "DataObjects/TypedPathMap.h"

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
	if (m_pathMapsTreeRoot)
		delete m_pathMapsTreeRoot;
}

//////////////////////////////////////////////////////////////////////////
void DataBase::setDefaultValues()
{
	m_ipAddress = "127.0.0.1";
	m_port = 8000;
	m_iidFilePath = "";

	m_pathMapsTreeRoot = new TypedPathMap("iisu");

	// Users #.
	TypedPathMap* path_user1 = new TypedPathMap("user1", m_pathMapsTreeRoot);
	//new Vector3ArrayPathMap("centroids", "USER1.SHAPE.CENTROIDS.Positions", path_user1);
	new IntegerPathMap("status", "USER1.SKELETON.Status", path_user1);
	TypedPathMap* path_joints1 = new TypedPathMap("joints", path_user1);
	new Vector3ArrayPathMap("positions", "USER1.SKELETON.KeyPoints", path_joints1);
	new FloatArrayPathMap("confidences", "USER1.SKELETON.KeyPointsConfidence", path_joints1);

	m_isObservationOn = false;

	m_isFoldAndNameJoints = true;

	m_oscPacketSize = 0;
}

} // namespace SK.