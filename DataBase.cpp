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

	m_pathsTreeRoot = new PathAssociation("iisu");
	PathAssociation* path_joints = new PathAssociation("joints", m_pathsTreeRoot);
	new Vector3ArrayPathAssociation("positions", path_joints, "USER#.SKELETON.KeyPoints");
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


}

} // namespace SK.