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
	void onIidFilePathLineEditTextChanged(const std::string& newIidFilePath) {m_dataBase->setIidFilePath(newIidFilePath);}

	void onStartStopToggleButtonClicked();

	void onFoldAndNameJointsCheckBoxClicked(bool isFoldAndNameJoints);

	void onAddMapButtonClicked() {}
	void onInsertMapButtonClicked() {}
	void onDeleteMapButtonClicked() {}
	void onClearMapsButtonClicked();
	//@}

protected:
	DataController();
	virtual ~DataController();

	static DataController* sm_instance;

	/// \name Iisu.
	//@{
	bool initIisu();
	void resumeStream();
	void newIisuDataFrameListener(const SK::DataFrameEvent& event);
	void pauseStream();
	void termIisu();

	SK::Device* m_device;
	std::vector<SK::IIisuDataExtractor*> m_iisuDataHandles;
	//@}

	/// \name Helpers.
	//@{
	DataBase* m_dataBase;

	std::vector<TypedPathMap*> m_pathMapLinearized;
	void linearizePathMap(TypedPathMap* typedPathMap);

	std::vector<std::string> m_fullOscPaths;
	std::string findFullOscPath(TypedPathMap* typedPathMap);

	char m_oscBuffer[OUTPUT_BUFFER_SIZE];
	void oscSend();
	//@}
};

} // namespace SK.

