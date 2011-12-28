#pragma once

#include "Core/DataBase/DataBase.h"

namespace SK
{

class DataController;

//////////////////////////////////////////////////////////////////////////
/// \brief This class adds the UI update service on data change.
///
/// When creating a new PathMap, we perform the actual operation before updating the controller, because
/// updating the controller needs to know about the newly created PathMap. On the opposite, when deleting
/// a PathMap, we perform the actual operation after updating the controller, because updating the
/// controller needs to know about the PathMaps to be deleted. When editing, the operations can be done
/// in any order.
class AppDataBase : public DataBase
{
	DECLARE_DATA_BASE(AppDataBase)

public:

	/// \name API redefinitions.
	//@{
	const PathMap* addPathMap(const PathMap* siblingPathMap, const std::string& oscPathBit = NEW_OSC_PATH_BIT, const std::string& iisuPath = NEW_IISU_PATH) SK_OVERRIDE;
	const PathMap* insertPathMap(const PathMap* siblingPathMap, const std::string& oscPathBit = NEW_OSC_PATH_BIT, const std::string& iisuPath = NEW_IISU_PATH) SK_OVERRIDE;
	const PathMap* addChildMap(const PathMap* parentPathMap, const std::string& oscPathBit = NEW_OSC_PATH_BIT, const std::string& iisuPath = NEW_IISU_PATH) SK_OVERRIDE;
	bool deletePathMap(const PathMap* pathMap) SK_OVERRIDE;
	bool clearPathMaps() SK_OVERRIDE;
	//@}

	/// \name Accessors redefinitions.
	//@{
	void setIsObservationOn(bool isObservationOn) SK_OVERRIDE;
	void setOscPacketSize(uint oscPacketSize) SK_OVERRIDE;
	//@}

	/// \name Accessors.
	//@{
	void setDataController(DataController* dataController) {m_dataController = dataController;}
	//@}

protected:
	AppDataBase() : DataBase(), m_dataController(0) {}
	virtual ~AppDataBase() {}

	DataController* m_dataController;
};

} // namespace SK.