#include "DataController.h"

namespace SK
{

#define OUTPUT_BUFFER_SIZE 1024

DataController* DataController::sm_instance = 0;

//////////////////////////////////////////////////////////////////////////
DataController::DataController()
{
	// Get access to the data model.
	m_dataModel = DataBase::GetInstance();
	assert(m_dataModel);
}

//////////////////////////////////////////////////////////////////////////
DataController::~DataController()
{
	if(NULL != m_device)
		SK::Context::Instance().finalize();
}

//////////////////////////////////////////////////////////////////////////
void DataController::CreateInstance()
{
	if (!sm_instance)
		sm_instance = new DataController();
}

//////////////////////////////////////////////////////////////////////////
void DataController::DestroyInstance()
{
	if (sm_instance)
		delete sm_instance;
}

//////////////////////////////////////////////////////////////////////////
void DataController::onStopButtonClicked()
{

}

//////////////////////////////////////////////////////////////////////////
bool DataController::initIisu()
{
	// Context.
	SK::Context& context = SK::Context::Instance();

	// Handle.
	SK::Return<SK::IisuHandle*> retHandle = context.createHandle(SK::IisuHandle::Configuration());
	if(retHandle.failed())
		return false;
	SK::IisuHandle* handle = retHandle.get();

	// Device.
	SK::Return<SK::Device*> retDevice = handle->initializeDevice(SK::Device::Configuration());
	if(retHandle.failed())
	{
		std::cout << retHandle.getDescription() << std::endl;
		SK::Result result = context.destroyHandle(*handle);
		if(result.failed())
			std::cout << result.getDescription() << std::endl;

		return false;
	}
	m_device = retDevice.get();

	// Data & events registration.
	m_skeleton = m_device->registerDataHandle< SK::Array<SK::Vector3> >("...");
	m_device->getEventManager().registerEventListener("DEVICE.DataFrame", *this, &DataController::newFrameListener);

	SK::GetVersionCommand cmd(m_device->getCommandManager());

	//	SK::CommandHandle<SK::Return<SK::String>()> cmd2(m_device->getCommandManager(), "SYSTEM.GetVersion");

	SK::Return<SK::String> retCmd = cmd();

	if(retCmd.succeeded())
	{
		std::cout << retCmd.get() << std::endl;
	}

	m_device->start();

	return true;
}

//////////////////////////////////////////////////////////////////////////
void DataController::newFrameListener( const SK::DataFrameEvent& event )
{
	m_device->updateFrame(true);
	std::cout << event.getFrameID() << std::endl;
}

//////////////////////////////////////////////////////////////////////////
bool DataController::update()
{
	m_device->lockFrame();

	const SK::Array<SK::Vector3>& keyPoints = m_skeleton.get();

	m_device->releaseFrame();

	return true;
}

} // namespace SK.