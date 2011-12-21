#pragma once

#include "Platform/SkPlatform.h"

//////////////////////////////////////////////////////////////////////////
#define DECLARE_DATA_CONTROLLER(DataControllerClass)\
public:\
	static DataControllerClass* CreateInstance();\
	static void SetInstance(DataControllerClass* manager);\
	static DataControllerClass* GetInstance();\
	void destroyInstance() SK_OVERRIDE;\
protected:\
	static DataControllerClass* sm_instance;

//////////////////////////////////////////////////////////////////////////
#define DEFINE_DATA_CONTROLLER(DataControllerClass, ParentDataControllerClass)\
	DataControllerClass* DataControllerClass::sm_instance = 0;\
	DataControllerClass* DataControllerClass::CreateInstance()\
{\
	if (!sm_instance && !sm_topMostInstance)\
	{\
		SetInstance(new DataControllerClass());\
	}\
	return sm_instance;\
}\
	void DataControllerClass::SetInstance(DataControllerClass* instance)\
{\
	sm_instance = instance;\
	ParentDataControllerClass::SetInstance(instance);\
}\
	DataControllerClass* DataControllerClass::GetInstance()\
{\
	assert(sm_instance);\
	return sm_instance;\
}\
	void DataControllerClass::destroyInstance()\
{\
	if (sm_topMostInstance)\
	{\
	sm_instance->ParentDataControllerClass::destroyInstance();\
	sm_instance = 0;\
	}\
}

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \brief Interface for all the data controllers.
class /*FOR_QTIISU_API*/ AbstractDataController
{
public:

	/// \name Singleton management.
	//@{
	static void SetInstance(AbstractDataController* manager);
	static void DestroyInstance();

	virtual void destroyInstance() = 0;
	//@}

protected:
	AbstractDataController() {} ///< Protected because the class is abstract.
	virtual ~AbstractDataController() {} ///< Protected because the class is destroyed via DestroyInstance().

	/// \name  Singleton management.
	//@{
	static AbstractDataController* sm_topMostInstance;
	//@}
};

} // namespace SK.