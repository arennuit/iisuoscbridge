#include "DataBase.h"
#include "PathAssociation.h"

namespace SK
{

DataBase* DataBase::sm_instance = 0;

//////////////////////////////////////////////////////////////////////////
DataBase::DataBase() :
	m_pathsTreeRoot(0)
{
	setDefaultValues();
}

//////////////////////////////////////////////////////////////////////////
DataBase::~DataBase()
{
	delete m_pathsTreeRoot;
}

//////////////////////////////////////////////////////////////////////////
void DataBase::CreateInstance()
{
	if (!sm_instance)
		sm_instance = new DataBase();
}

//////////////////////////////////////////////////////////////////////////
void DataBase::DestroyInstance()
{
	if (sm_instance)
		delete sm_instance;
}

//////////////////////////////////////////////////////////////////////////
void DataBase::setDefaultValues()
{
	m_ipAddress = std::string("127.0.0.1");
	m_port = 8000;

	m_pathsTreeRoot = new PathAssociation("iisu");
	// Users #.

	PathAssociation* path_user1 = new PathAssociation("user1", m_pathsTreeRoot);
	new Vector3ArrayPathAssociation("centroids", "USER1.SHAPE.CENTROIDS.Positions", path_user1);
	new BooleanPathAssociation("status", "USER1.SKELETON.Status", path_user1);
	PathAssociation* path_joints1 = new PathAssociation("joints", path_user1);
	new Vector3ArrayPathAssociation("positions", "USER1.SKELETON.KeyPoints", path_joints1);
	new FloatArrayPathAssociation("confidences", "USER1.SKELETON.KeyPointsConfidence", path_joints1);

	PathAssociation* path_user2 = new PathAssociation("user2", m_pathsTreeRoot);
	new Vector3ArrayPathAssociation("centroids", "USER2.SHAPE.CENTROIDS.Positions", path_user2);
	new BooleanPathAssociation("status", "USER2.SKELETON.Status", path_user2);
	PathAssociation* path_joints2 = new PathAssociation("joints", path_user2);
	new Vector3ArrayPathAssociation("positions", "USER2.SKELETON.KeyPoints", path_joints2);
	new FloatArrayPathAssociation("confidences", "USER2.SKELETON.KeyPointsConfidence", path_joints2);
}

} // namespace SK.