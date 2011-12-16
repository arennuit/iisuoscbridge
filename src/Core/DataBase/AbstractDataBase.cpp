#include "AbstractDataBase.h"

namespace SK
{

AbstractDataBase* AbstractDataBase::sm_topMostInstance = 0;

//////////////////////////////////////////////////////////////////////////
void AbstractDataBase::SetInstance(AbstractDataBase* instance)
{
	sm_topMostInstance = instance;
}

//////////////////////////////////////////////////////////////////////////
void AbstractDataBase::DestroyInstance()
{
	if (sm_topMostInstance)
	{
		sm_topMostInstance->destroyInstance();
	}
}

//////////////////////////////////////////////////////////////////////////
void AbstractDataBase::destroyInstance()
{
	if (sm_topMostInstance)
	{
		delete sm_topMostInstance;
		sm_topMostInstance = 0;
	}
}

} // namespace SK.