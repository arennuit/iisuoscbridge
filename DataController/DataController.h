#pragma once

#include "DataBase/DataBase.h"
#include "SDK/iisuSDK.h"
#include <string>

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \name This class is the controller in the MVD / MVC pattern.
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
	void onIpAddressLineEditTextChanged(const std::string& newIpAddress) {m_dataModel->setIpAddress(newIpAddress);}
	void onPortLineEditTextChanged(int newPort) {m_dataModel->setPort(newPort);}

	void onStartButtonClicked() {initIisu();}
	void onStopButtonClicked() {termIisu();}
	//@}

protected:
	DataController();
	virtual ~DataController();

	static DataController* sm_instance;

	DataBase* m_dataModel;

	/// \name Iisu.
	//@{
	bool initIisu();
	void newDataFrameListenerIisu(const SK::DataFrameEvent& event);
	void termIisu();

	SK::Device* m_device;
	std::vector<IIisuDataExtractor*> m_dataHandles;
	//SK::DataHandle<SK::Array<SK::Vector3> > m_skeleton;
	//@}

	void linearizePathMap(PathMapItem* pathItem);
	std::vector<PathMapItem*> m_pathMapLinearized;

	std::vector<std::string> m_fullOscPaths;
	std::string findFullOscPath(PathMapItem* pathItem);
	void oscSend();
};

} // namespace SK.

