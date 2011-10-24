#include "DataController.h"
#include "DataBase/PathMapItem.h"
#include "Visitors/IisuDataRegistrator.h"
#include "Visitors/IisuReaderOscSender.h"

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

namespace SK
{

DataController* DataController::sm_instance = 0;

//////////////////////////////////////////////////////////////////////////
DataController::DataController() :
	m_device(0)
{
	// Get access to the data model.
	m_dataBase = DataBase::GetInstance();
	assert(m_dataBase);
}

//////////////////////////////////////////////////////////////////////////
DataController::~DataController()
{
	m_pathMapLinearized.clear();

	termIisu();
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
bool DataController::initIisu()
{
	// Linearize path items.
	if (!m_dataBase->getPathsTreeRoot())
		return false;

	m_pathMapLinearized.clear();
	linearizePathMap(m_dataBase->getPathsTreeRoot());

	// Find the full path of each DataPathMapItem.
	m_fullOscPaths.clear();
	m_fullOscPaths.resize(m_pathMapLinearized.size());
	for (uint i = 0; i < m_pathMapLinearized.size(); ++i)
		m_fullOscPaths[i] = findFullOscPath(m_pathMapLinearized[i]);

	// Iisu context.
	SK::Context& context = SK::Context::Instance();

	// Iisu handle.
	SK::IisuHandle::Configuration conf;
	conf.iisuBinDir = "d:/DevRoot/bin";
	conf.configFileName = "iisu_config.xml";
	conf.isLocal = true;

	SK::Return<SK::IisuHandle*> retHandle = context.createHandle(conf);
	if(retHandle.failed())
	{
		std::cout << retHandle.getDescription() << std::endl;
		return false;
	}
	SK::IisuHandle* handle = retHandle.get();

	// Iisu device.
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

	// Iisu events registration.
	m_device->getEventManager().registerEventListener("DEVICE.DataFrame", *this, &DataController::newDataFrameListenerIisu);

	// Iisu data handles registration.
	m_iisuDataHandles.clear();
	IisuDataRegistrator iisuPathRegistrator(m_device, m_iisuDataHandles, m_pathMapLinearized);
	for (uint i = 0; i < m_pathMapLinearized.size(); ++i)
		m_pathMapLinearized[i]->accept(&iisuPathRegistrator);

	//SK::GetVersionCommand cmd(m_device->getCommandManager());
	////	SK::CommandHandle<SK::Return<SK::String>()> cmd2(m_device->getCommandManager(), "SYSTEM.GetVersion");
	//SK::Return<SK::String> retCmd = cmd();
	//if(retCmd.succeeded())
	//	std::cout << retCmd.get() << std::endl;

	m_device->start();

	return true;
}

//////////////////////////////////////////////////////////////////////////
void DataController::newDataFrameListenerIisu( const SK::DataFrameEvent& event )
{
	m_device->updateFrame(true);
	std::cout << event.getFrameID() << std::endl;

	oscSend();
}

//////////////////////////////////////////////////////////////////////////
void DataController::termIisu()
{
	m_iisuDataHandles.clear();

	if (m_device)
	{
		SK::Context::Instance().finalize();
		m_device = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
void DataController::linearizePathMap(PathMapItem* pathItem)
{
	m_pathMapLinearized.push_back(pathItem);

	for (uint i = 0; i < pathItem->m_children.size(); ++i)
		linearizePathMap(pathItem->m_children[i]);
}

//////////////////////////////////////////////////////////////////////////
std::string DataController::findFullOscPath( PathMapItem* pathItem )
{
	if (!pathItem)
		return "";

	// Parse PathMapItems up-tree.
	std::string fullPath;
	PathMapItem* currentPath = pathItem;
	while (currentPath != 0)
	{
		fullPath = std::string("/") + currentPath->m_oscPathItem + fullPath;

		currentPath = currentPath->m_parent;
	}

	return fullPath;
}

//////////////////////////////////////////////////////////////////////////
void DataController::oscSend()
{
	m_device->lockFrame();

	UdpTransmitSocket transmitSocket(IpEndpointName(m_dataBase->getIpAddress().c_str(), m_dataBase->getPort()));
	osc::OutboundPacketStream outPacketStream(m_oscBuffer, OUTPUT_BUFFER_SIZE);

	outPacketStream	<< osc::BeginBundleImmediate;;

	IisuReaderOscSender iisuReaderOscSender(&outPacketStream);
	for (uint i = 0; i < m_pathMapLinearized.size(); ++i)
	{
		iisuReaderOscSender.setPathItemData(m_fullOscPaths[i], m_iisuDataHandles[i]);
		m_pathMapLinearized[i]->accept(&iisuReaderOscSender);
	}

	outPacketStream	<< osc::EndBundle;

	transmitSocket.Send(outPacketStream.Data(), outPacketStream.Size());

	m_device->releaseFrame();
}

} // namespace SK.