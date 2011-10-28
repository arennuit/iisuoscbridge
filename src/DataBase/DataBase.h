#pragma once

#include "AbstractDataBase.h"
#include <string>

namespace SK
{

class PathMapItem;

//////////////////////////////////////////////////////////////////////////
/// \brief This class is a singleton, it keeps all the data handled by the application.
class DataBase : public AbstractDataBase
{
	DECLARE_DATA_BASE(DataBase)

public:

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

	virtual uint getOscPacketSize() {return m_oscPacketSize;}
	virtual void setOscPacketSize(uint oscPacketSize) {m_oscPacketSize = oscPacketSize;}
	//@}

protected:
	DataBase();
	virtual ~DataBase();

	void setDefaultValues();

	/// \name Application data.
	//@{
	std::string m_ipAddress;
	int m_port;

	PathMapItem* m_pathsTreeRoot;

	bool m_isObservationOn;

	uint m_oscPacketSize;
	//@}
};

} // namespace SK.