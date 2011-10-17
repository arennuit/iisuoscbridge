#pragma once

#include "DataBase/DataBase.h"
#include "SDK/iisuSDK.h"
#include <string>

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \name This class is the controller in the MVD / MVC pattern.
class MvdController
{
public:
	/// \name Singleton management.
	//@{
	static void CreateInstance();
	static void DestroyInstance();
	static MvdController* GetInstance() {return sm_instance;}
	//@}

	/// \name Data control.
	//@{
	void onIpAddressLineEditTextChanged(const std::string& newIpAddress) {m_dataModel->setIpAddress(newIpAddress);}
	void onPortLineEditTextChanged(int newPort) {m_dataModel->setPort(newPort);}

	void onStartButtonClicked() {initIisu();}
	void onStopButtonClicked();
	//@}

protected:
	MvdController();
	virtual ~MvdController();

	static MvdController* sm_instance;

	DataBase* m_dataModel;

	/// \name Iisu.
	//@{
	bool initIisu();
	bool update();
	void newFrameListener(const SK::DataFrameEvent& event);

	SK::Device* m_device;
	SK::DataHandle<SK::Array<SK::Vector3> > m_skeleton;
	//@}
};

} // namespace SK.

