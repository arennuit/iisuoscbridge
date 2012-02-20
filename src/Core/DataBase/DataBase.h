#pragma once

#include "AbstractDataBase.h"
#include <string>

#define NEW_OSC_PATH_BIT "New Osc Path Bit"
#define NEW_IISU_PATH "New Iisu Path"

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
/// TODO: there is a problem with the architecture here. In order to protect the data and keep the integrity of the
///       different layers of the app (ie keeping the data and the GUI up to date), all the modifications are due
///       to be performed through the DataBase (and not directly on the data themselves). This means outside of the
///       DataBase, all the reference and pointers to the data are consts (the DataBase's get accessors all return
///       const values).
///       In order to allow data edition, the GUI keeps a pointer or ref to each displayed data. These pointers are
///       consts because the DataBase only returns const pointers. As the pointers are consts, one cannot call an
///       editing function against these pointers.
///       Currently we use a workaround: we transform the const points into non-consts in the DataController. This
///       conversion could also be done just before storing the pointers in the GUI (so we would store non-const
///       pointers, as they are due to be used for editing). This situation is not ideal and requires a bit more TLC...
class DataBase : public AbstractDataBase
{
	DECLARE_DATA_BASE(DataBase)

public:

	/// \name API.
	//@{
	virtual void reset();
	//@}

	/// \name Editors.
	//@{
	virtual void setIpAddress(const std::string& ipAddress) {m_ipAddress = ipAddress;}
	virtual void setIpPort(int ipPort) {m_ipPort = ipPort;}
	virtual bool setIidFilePath(const std::string& iidFilePath) {m_iidFilePath = iidFilePath; return true;}
	virtual void setDecorateStream(bool decorateStream) {m_decorateStream = decorateStream;}

	virtual const PathMap* addPathMap(const PathMap* siblingPathMap, const std::string& oscPathBit = NEW_OSC_PATH_BIT, const std::string& iisuPath = NEW_IISU_PATH);
	virtual const PathMap* insertPathMap(const PathMap* siblingPathMap, const std::string& oscPathBit = NEW_OSC_PATH_BIT, const std::string& iisuPath = NEW_IISU_PATH);
	virtual const PathMap* addChildMap(const PathMap* parentPathMap, const std::string& oscPathBit = NEW_OSC_PATH_BIT, const std::string& iisuPath = NEW_IISU_PATH);
	virtual bool deletePathMap(const PathMap* pathMap);
	virtual bool clearPathMaps();
	virtual void editPathMap(PathMap* pathMap, const std::string& newOscPathBit, const std::string& newIisuPath);

	virtual void setMocapState(bool mocapState) {m_mocapState = mocapState;}
	virtual void setOscPacketSize(uint oscPacketSize) {m_oscPacketSize = oscPacketSize;}
	//@}

	/// \name Getters.
	//@{
	virtual const std::string& getIpAddress() const {return m_ipAddress;}
	virtual int getIpPort() const {return m_ipPort;}
	virtual const std::string& getIidFilePath() const {return m_iidFilePath;}
	virtual bool getDecorateStream() const {return m_decorateStream;}

	virtual const PathMap* getPathMapsRoot() const {return m_pathMapsRoot;} ///< The 'const' makes sure the database knows when a data is modified.

	virtual bool getMocapState() const {return m_mocapState;}
	virtual uint getOscPacketSize() const {return m_oscPacketSize;}
	//@}

protected:
	DataBase();
	virtual ~DataBase();

	/// \name Application data.
	//@
	std::string m_ipAddress;
	int m_ipPort;
	std::string m_iidFilePath;
	bool m_decorateStream;

	PathMap* m_pathMapsRoot;

	bool m_mocapState;
	uint m_oscPacketSize;
	//@}

	/// \name Default values.
	//@
	static std::string sm_ipAddressDefaultValue;
	static int sm_ipPortDefaultValue;
	static std::string sm_iidFilePathDefaultValue;
	static bool sm_decorateStreamDefaultValue;

	static PathMap* sm_pathMapsRootDefaultValue;

	static uint sm_oscPacketSizeDefaultValue;
	static bool sm_mocapStateDefaultValue;
	//@}
};

} // namespace SK.