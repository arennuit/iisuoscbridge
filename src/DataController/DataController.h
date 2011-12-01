#pragma once

#include "DataBase/DataBase.h"
#include "DataBase/PathMap.h"
#include "SDK/iisuSDK.h"
#include <string>

#define OUTPUT_BUFFER_SIZE 32768

#define NEW_OSC_PATH_BIT "New Osc Path Bit"
#define NEW_IISU_PATH "New Iisu Path"

namespace SK
{

class TypedPathMap;

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

	PathMap* onAddMapButtonClicked(PathMap* siblingPathMap);
	PathMap* onInsertMapButtonClicked(PathMap* siblingPathMap);
	PathMap* onAddChildMapButtonClicked(PathMap* parentPathMap);
	void onDeleteMapButtonClicked(PathMap* pathMap);
	void onClearMapsButtonClicked();

	void onMvdPathDelegateEditorCreation(std::vector<std::string>& iisuDataPaths);
	//@}

protected:
	DataController();
	virtual ~DataController();

	static DataController* sm_instance;

	/// \name Iisu.
	//@{
	bool initIisu();
	void resumeStream();
	void iisuErrorListener( const SK::ErrorEvent& event );
	void newIisuDataFrameListener( const SK::DataFrameEvent& event );
	void pauseStream();
	void termIisu();

	SK::Device* m_device;
	std::vector<SK::IIisuDataExtractor*> m_iisuDataHandles;
	//@}

	/// \name Helpers.
	//@{
	DataBase* m_dataBase;

	std::vector<PathMap*> m_pathMapsLinearized;
	void linearizePathMap(PathMap* PathMap);

	std::string findFullOscPath(PathMap* PathMap);

	std::vector<TypedPathMap*> m_typedPathMapsLinearized;

	// TODO: check buffer is large enough when putting the message together.
	char m_oscBuffer[OUTPUT_BUFFER_SIZE];
	void oscSend();
	//@}
};

} // namespace SK.

