#pragma once

#include "Platform/SkPlatform.h"

//#include <fstream>
//#include <map>
//#include <string>
//#include <list>

//////////////////////////////////////////////////////////////////////////
#define DECLARE_DATA_BASE(DataBaseClass)\
public:\
	static DataBaseClass* CreateInstance();\
	static void SetInstance(DataBaseClass* manager);\
	static DataBaseClass* GetInstance();\
	void destroyInstance() SK_OVERRIDE;\
protected:\
	static DataBaseClass* sm_instance;

//////////////////////////////////////////////////////////////////////////
#define DEFINE_DATA_BASE(DataBaseClass, ParentDataBaseClass)\
	DataBaseClass* DataBaseClass::sm_instance = 0;\
	DataBaseClass* DataBaseClass::CreateInstance()\
{\
	if (!sm_instance && !sm_topMostInstance)\
	{\
		SetInstance(new DataBaseClass());\
	}\
	return sm_instance;\
}\
	void DataBaseClass::SetInstance(DataBaseClass* instance)\
{\
	sm_instance = instance;\
	ParentDataBaseClass::SetInstance(instance);\
}\
	DataBaseClass* DataBaseClass::GetInstance()\
{\
	assert(sm_instance);\
	return sm_instance;\
}\
	void DataBaseClass::destroyInstance()\
{\
	if (sm_topMostInstance)\
	{\
	sm_instance->ParentDataBaseClass::destroyInstance();\
	sm_instance = 0;\
	}\
}

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \brief Interface for all the databases.
class /*FOR_QTIISU_API*/ AbstractDataBase
{
public:

	/// \name Singleton management.
	//@{
	static void SetInstance(AbstractDataBase* manager);
	static void DestroyInstance();

	virtual void destroyInstance() = 0;
	//@}

protected:
	AbstractDataBase() {} ///< Protected because the class is abstract.
	virtual ~AbstractDataBase() {} ///< Protected because the class is destroyed via DestroyInstance().

	/// \name  Singleton management.
	//@{
	static AbstractDataBase* sm_topMostInstance;
	//@}
};

} // namespace SK.