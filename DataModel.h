#pragma once

#include <string>

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \class This class is a singleton, it keeps all the data handled by the application.
class DataModel
{
public:

	/// \name Singleton management.
	//@{
	static void CreateInstance();
	static void DestroyInstance();
	static DataModel* GetInstance() {return sm_instance;}
	//@}

	/// \name Application data.
	//@{
	std::string m_ipAddress;
	int m_port;
	//@}

protected:
	DataModel() {setDefaultValues();}
	~DataModel() {}

	static DataModel* sm_instance;

	void setDefaultValues();
};

} // namespace SK.