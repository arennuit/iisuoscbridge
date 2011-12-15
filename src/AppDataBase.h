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

	/// \name Application data accessors redefinitions.
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