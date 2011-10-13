#include "DataModel.h"
#include "PathAssociation.h"

namespace SK
{

DataModel* DataModel::sm_instance = 0;

//////////////////////////////////////////////////////////////////////////
DataModel::DataModel() :
	m_pathsTreeRoot(0)
{
	setDefaultValues();

	m_pathsTreeRoot = new PathAssociation("iisu");
	PathAssociation* path_joints = new PathAssociation("joints", m_pathsTreeRoot);
	new Vector3ArrayPathAssociation("positions", path_joints, "USER#.SKELETON.KeyPoints");
}

//////////////////////////////////////////////////////////////////////////
void DataModel::CreateInstance()
{
	if (!sm_instance)
		sm_instance = new DataModel();
}

//////////////////////////////////////////////////////////////////////////
void DataModel::DestroyInstance()
{
	if (sm_instance)
		delete sm_instance;
}

//////////////////////////////////////////////////////////////////////////
void DataModel::setDefaultValues()
{
	m_ipAddress = std::string("127.0.0.1");
	m_port = 8000;


}

} // namespace SK.