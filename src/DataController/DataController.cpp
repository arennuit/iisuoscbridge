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

	// Init iisu.
	std::string errorMsg;
	initIisu(errorMsg);
}

//////////////////////////////////////////////////////////////////////////
DataController::~DataController()
{
	// Pause streaming.
	std::string errorMsg;
	pauseStream(errorMsg);

	// Term iisu.
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
void DataController::onStartStopToggleButtonClicked(std::string& errorMsg)
{
	errorMsg = "";

	if (m_dataBase->getIsObservationOn() == false)
		resumeStream(errorMsg);
	else
		pauseStream(errorMsg);
}

//////////////////////////////////////////////////////////////////////////
void DataController::resumeStream(std::string& errorMsg)
{
	// Load IID script.
	// TODO: il faut qu'il soit load� quand je tape mes paths et qu'il se reload automatiquement si je le change.
	if (m_dataBase->getIidFilePath() != std::string(""))
	{
		SK::CommandHandle<SK::Result (const SK::String&)> loadIidGraph = m_device->getCommandManager().registerCommandHandle<SK::Result(const SK::String&)>("IID.loadGraph");
		SK::Result resLoadCmd = loadIidGraph(m_dataBase->getIidFilePath().c_str());
		if (resLoadCmd.failed())
			errorMsg += std::string("Load IID graph : ") + resLoadCmd.getDescription().ptr() + std::string("\n");
		else
			errorMsg += "IID file loaded correctly\n";
	}

	// Linearize path items.
	linearizePathMap(m_dataBase->getPathsTreeRoot());

	// Find the full path of each DataPathMapItem.
	m_fullOscPaths.resize(m_pathMapLinearized.size());
	for (uint i = 0; i < m_pathMapLinearized.size(); ++i)
		m_fullOscPaths[i] = findFullOscPath(m_pathMapLinearized[i]);

	// Register data handles.
	IisuDataRegistrator iisuPathRegistrator(m_device, m_iisuDataHandles, m_pathMapLinearized);
	for (uint i = 0; i < m_pathMapLinearized.size(); ++i)
		m_pathMapLinearized[i]->accept(&iisuPathRegistrator);

	// Start device.
	m_device->start();
	m_dataBase->setIsObservationOn(true);

	errorMsg += "The iisu engine is started\nOscBridge is now streaming OSC...";
}

//////////////////////////////////////////////////////////////////////////
void DataController::pauseStream(std::string& errorMsg)
{
	// Stop device.
	m_dataBase->setIsObservationOn(false);
	m_device->stop();

	// Unregister data handles.
	// TODO: unregister data handles (not possible yet in iisu's API).
	//for (uint i = 0; i < m_pathMapLinearized.size(); ++i)
	//	m_device->unregisterData(m_iisuDataHandles[i]);

	for (uint i = 0; i < m_iisuDataHandles.size(); ++i)
	{
		if (m_iisuDataHandles[i])
			delete m_iisuDataHandles[i];
	}

	m_iisuDataHandles.clear();

	// Clear the full OSC paths.
	m_fullOscPaths.clear();

	// clear the array of linearized path maps.
	m_pathMapLinearized.clear();
}

//////////////////////////////////////////////////////////////////////////
void DataController::onFoldAndNameJointsCheckBoxClicked( bool isFoldAndNameJoints )
{
	m_dataBase->setIsFoldAndNameJoints(isFoldAndNameJoints);
}

//////////////////////////////////////////////////////////////////////////
bool DataController::initIisu(std::string& errorMsg)
{
	// Iisu context.
	SK::Context& context = SK::Context::Instance();

	// Iisu handle.
	SK::Return<SK::ApplicationConfigurator> retAppConf = SK::ApplicationConfigurator::create("");
	if (retAppConf.failed())
	{
		errorMsg += retAppConf.getDescription().ptr();
		return false;
	}
	ApplicationConfigurator appConf = retAppConf.get();

	SK::Return<SK::IisuHandle*> retHandle = context.createHandle(appConf);
	if (retHandle.failed())
	{
		errorMsg += retHandle.getDescription().ptr();
		return false;
	}
	SK::IisuHandle* handle = retHandle.get();

	// Iisu device.
	SK::Return<SK::Device*> retDevice = handle->initializeDevice(appConf);
	if (retDevice.failed())
	{
		// TODO: pb log here.
		errorMsg += retDevice.getDescription().ptr();
		SK::Result result = context.destroyHandle(*handle);
		if (result.failed())
			errorMsg += result.getDescription().ptr();

		return false;
	}
	m_device = retDevice.get();

	// Iisu events registration.
	m_device->getEventManager().registerEventListener("DEVICE.DataFrame", *this, &DataController::newIisuDataFrameListener);

	// Return.
	errorMsg += "The iisu engine inited correctly\n";
	return true;
}

//////////////////////////////////////////////////////////////////////////
void DataController::newIisuDataFrameListener( const SK::DataFrameEvent& event )
{
	m_device->updateFrame(true);
	std::cout << event.getFrameID() << std::endl;

	oscSend();
}

//////////////////////////////////////////////////////////////////////////
void DataController::termIisu()
{
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

	// Create socket and stream.
	UdpTransmitSocket transmitSocket(IpEndpointName(m_dataBase->getIpAddress().c_str(), m_dataBase->getPort()));
	osc::OutboundPacketStream outPacketStream(m_oscBuffer, OUTPUT_BUFFER_SIZE);

	// Build the OSC packet up.
	outPacketStream	<< osc::BeginBundleImmediate;;

	IisuReaderOscSender iisuReaderOscSender(m_dataBase, &outPacketStream);
	for (uint i = 0; i < m_pathMapLinearized.size(); ++i)
	{
		iisuReaderOscSender.setPathItemData(m_fullOscPaths[i], m_iisuDataHandles[i]);
		m_pathMapLinearized[i]->accept(&iisuReaderOscSender);
	}

	outPacketStream	<< osc::EndBundle;

	// Stream OSC packet out.
	transmitSocket.Send(outPacketStream.Data(), outPacketStream.Size());

	// Store packet size.
	m_dataBase->setOscPacketSize(outPacketStream.Size());

	m_device->releaseFrame();
}

} // namespace SK.