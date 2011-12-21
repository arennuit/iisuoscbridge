#pragma once

#include "Core/DataController.h"

namespace SK
{

/// \brief This class adds the UI update service on data change.
class AppDataController : public DataController
{
public:

	/// \name Accessors.
	//@{
	void setMainForm(MainForm* mainForm) {m_mainForm = mainForm;}
	//@}

protected:
	AppDataController() : DataController(), m_mainForm(0) {}
	virtual ~AppDataController() {}

	MainForm* m_mainForm;
};

} // namespace SK.