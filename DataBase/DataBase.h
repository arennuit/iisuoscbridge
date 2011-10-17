#pragma once

#include <string>

namespace SK
{

class PathAssociation;

//////////////////////////////////////////////////////////////////////////
/// \class This class is a singleton, it keeps all the data handled by the application.
class DataBase
{
public:

	/// \name Singleton management.
	//@{
	static void CreateInstance();
	static void DestroyInstance();
	static DataBase* GetInstance() {return sm_instance;}
	//@}

	/// \name Accessors.
	//@{
	virtual const std::string& getIpAddress() {return m_ipAddress;}
	virtual void setIpAddress(const std::string& ipAddress) {m_ipAddress = ipAddress;}
	
	virtual int getPort() {return m_port;}
	virtual void setPort(int port) {m_port = port;}

	virtual PathAssociation* getPathsTreeRoot() {return m_pathsTreeRoot;}
	virtual void setPathsTreeRoot(PathAssociation* pathsTreeRoot) {m_pathsTreeRoot = pathsTreeRoot;}
	//@}

protected:
	DataBase();
	virtual ~DataBase();

	static DataBase* sm_instance;

	void setDefaultValues();

	/// \name Application data.
	//@{
	std::string m_ipAddress;
	int m_port;

	PathAssociation* m_pathsTreeRoot;
	//@}
};

} // namespace SK.