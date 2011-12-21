#include "AbstractDataController.h"

namespace SK
{

AbstractDataController* AbstractDataController::sm_topMostInstance = 0;

//////////////////////////////////////////////////////////////////////////
void AbstractDataController::SetInstance(AbstractDataController* instance)
{
	sm_topMostInstance = instance;
}

//////////////////////////////////////////////////////////////////////////
void AbstractDataController::DestroyInstance()
{
	if (sm_topMostInstance)
	{
		sm_topMostInstance->destroyInstance();
	}
}

//////////////////////////////////////////////////////////////////////////
void AbstractDataController::destroyInstance()
{
	if (sm_topMostInstance)
	{
		delete sm_topMostInstance;
		sm_topMostInstance = 0;
	}
}

} // namespace SK.