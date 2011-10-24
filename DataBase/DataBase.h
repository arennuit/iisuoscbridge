#pragma once

#include <string>

namespace SK
{

class PathMapItem;

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

	virtual PathMapItem* getPathsTreeRoot() {return m_pathsTreeRoot;}
	virtual void setPathsTreeRoot(PathMapItem* pathsTreeRoot) {m_pathsTreeRoot = pathsTreeRoot;}

	virtual bool getIsObservationOn() {return m_isObservationOn;}
	virtual void setIsObservationOn(bool isObservationOn) {m_isObservationOn = isObservationOn;} 
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

	PathMapItem* m_pathsTreeRoot;

	bool m_isObservationOn;
	//@}
};

} // namespace SK.