#pragma once

#include "DataBase/DataBase.h"
#include "SDK/iisuSDK.h"
#include <string>

#define OUTPUT_BUFFER_SIZE 32768

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \brief This class is the controller in the MVD / MVC pattern.
class DataController
{
public:
	/// \name Singleton management.
	//@{
	static void CreateInstance();
	static void DestroyInstance();
	static DataController* GetInstance() {return sm_instance;}
	//@}

	/// \name Data control.
	//@{
	void onIpAddressLineEditTextChanged(const std::string& newIpAddress) {m_dataBase->setIpAddress(newIpAddress);}
	void onPortLineEditTextChanged(int newPort) {m_dataBase->setPort(newPort);}

	void onStartStopToggleButtonClicked();
	//@}

protected:
	DataController();
	virtual ~DataController();

	static DataController* sm_instance;

	/// \name Temporaries.
	//@{
	DataBase* m_dataBase;

	void linearizePathMap(PathMapItem* pathItem);
	std::vector<PathMapItem*> m_pathMapLinearized;
	//@}

	/// \name Iisu.
	//@{
	bool initIisu();
	void newIisuDataFrameListener(const SK::DataFrameEvent& event);
	void termIisu();

	SK::Device* m_device;
	std::vector<SK::IIisuDataExtractor*> m_iisuDataHandles;
	//@}

	/// \name Osc.
	//@{
	std::vector<std::string> m_fullOscPaths;
	std::string findFullOscPath(PathMapItem* pathItem);
	void oscSend();

	char m_oscBuffer[OUTPUT_BUFFER_SIZE];
	//@}
};

} // namespace SK.

