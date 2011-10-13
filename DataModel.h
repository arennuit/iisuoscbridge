#pragma once

#include <string>

namespace SK
{

class PathAssociation;

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

	/// \name Accessors.
	//@{
	virtual const std::string& getIpAddress() {return m_ipAddress;}
	virtual void setIpAddress(const std::string& ipAddress) {m_ipAddress = ipAddress;}
	
	virtual int getPort() {return m_port;}
	virtual void setPort(int port) {m_port = port;}
	//@}

protected:
	DataModel();
	virtual ~DataModel() {}

	static DataModel* sm_instance;

	PathAssociation* m_pathsTreeRoot;

	void setDefaultValues();

	/// \name Application data.
	//@{
	std::string m_ipAddress;
	int m_port;
	//@}
};

} // namespace SK.