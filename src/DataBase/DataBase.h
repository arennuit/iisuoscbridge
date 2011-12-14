#pragma once

#include "AbstractDataBase.h"
#include <string>

namespace SK
{

class PathMap;

//////////////////////////////////////////////////////////////////////////
/// \brief This class is a singleton, it keeps all the data handled by the application.
///
/// It is important that the database knows about any changes done to the data (so we can inherit an app db from
/// it that does operations when changes on the data are performed). In order to do so we need to make sure the
/// get accessors return const data and we also need to provide an API that allows to modify any data.
/// Handling the db modifications this way allows to specify the data/GUI synchronization once only and at the
/// lowest level, so the GUI update is the same whether we perform the modification via the GUI or by code and the
/// maintenance is easy (as things are only done once).
/// It would be even better to have an observers' mechanism on data change with registered callbacks but this is
/// a more involving solution. It probably needs properties in order not to have to code the callback registrators
/// mechanism for any single piece of data.
class DataBase : public AbstractDataBase
{
	DECLARE_DATA_BASE(DataBase)

public:

	/// \name API.
	//@{
	void reset();

	virtual PathMap* addPathMap(PathMap* siblingPathMap);
	virtual PathMap* insertPathMap(PathMap* siblingPathMap);
	virtual PathMap* addChildMap(PathMap* parentPathMap);
	virtual void deletePathMap(PathMap* pathMap);
	virtual void clearPathMaps();
	//@}

	/// \name Application.
	//@{
	virtual const std::string& getIpAddress() const {return m_ipAddress;}
	virtual void setIpAddress(const std::string& ipAddress) {m_ipAddress = ipAddress;}
	
	virtual int getPort() const {return m_port;}
	virtual void setPort(int port) {m_port = port;}

	virtual const std::string& getIidFilePath() const {return m_iidFilePath;}
	virtual void setIidFilePath(const std::string& iidFilePath) {m_iidFilePath = iidFilePath;}

	virtual const PathMap* getPathMapsRoot() const {return m_pathMapsRoot;} ///< The 'const' makes sure the database knows when a data is modified.

	virtual bool getIsObservationOn() const {return m_isObservationOn;}
	virtual void setIsObservationOn(bool isObservationOn) {m_isObservationOn = isObservationOn;}

	virtual bool getIsFoldAndNameJoints() const {return m_isFoldAndNameJoints;}
	virtual void setIsFoldAndNameJoints(bool isFoldAndNameJoints) {m_isFoldAndNameJoints = isFoldAndNameJoints;}

	virtual uint getOscPacketSize() const {return m_oscPacketSize;}
	virtual void setOscPacketSize(uint oscPacketSize) {m_oscPacketSize = oscPacketSize;}
	//@}

protected:
	DataBase();
	virtual ~DataBase();

	void setDefaultValues();

	/// \name Application data.
	//@
	std::string m_ipAddress;
	int m_port;
	std::string m_iidFilePath;

	PathMap* m_pathMapsRoot;

	bool m_isObservationOn;

	bool m_isFoldAndNameJoints;

	uint m_oscPacketSize;
	//@}
};

} // namespace SK.