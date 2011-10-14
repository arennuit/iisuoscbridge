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
	new Vector3ArrayPathAssociation("centroids", m_pathsTreeRoot, "USER#.SHAPE.CENTROIDS.Positions");
	PathAssociation* path_joints = new PathAssociation("joints", m_pathsTreeRoot);
	new BooleanPathAssociation("status", path_joints, "USER#.SKELETON.Status");
	new Vector3ArrayPathAssociation("positions", path_joints, "USER#.SKELETON.KeyPoints");
	new FloatArrayPathAssociation("confidences", path_joints, "USER#.SKELETON.KeyPointsConfidence");
}

} // namespace SK.