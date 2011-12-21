#pragma once

#include "Core/DataBase/DataBase.h"

namespace SK
{

class MainForm;

//////////////////////////////////////////////////////////////////////////
/// \brief This class adds the UI update service on data change.
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
	void setMainForm(MainForm* mainForm) {m_mainForm = mainForm;}
	//@}

protected:
	AppDataBase() : DataBase(), m_mainForm(0) {}
	virtual ~AppDataBase() {}

	MainForm* m_mainForm;
};

} // namespace SK.