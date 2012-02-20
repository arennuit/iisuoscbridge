#include "IisuManager.h"

#include "LogSystem/Logger.h"
#include "Core/DataBase/DataBase.h"
#include "Core/DataBase/PathMap.h"

#include "Core/IisuManager/TypedPathMap/TypedPathMap.h"
#include "Core/IisuManager/TypedPathMap/TypedPathMapFactory.h"
#include "Core/IisuManager/Visitors/IisuDataRegistrator.h"
#include "Core/IisuManager/Visitors/IisuReaderOscSender.h"

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
bool IisuManager::initIisu()
{
	// Iisu context.
	SK::Context& context = SK::Context::Instance();

	SK_LOGGER(LOG_INFO) << "The context instance was obtained.";

	// Iisu handle.
	char* iisuSdkDir_char = getenv("IISU_SDK_DIR");
	if (iisuSdkDir_char == 0)
	{
		SK_LOGGER(LOG_ERROR) << "Cannot find environment variable \'IISU_SDK_DIR\':";
		SK_LOGGER(LOG_ERROR) << "     -> the iisu runtime may not have been installed correctly.";
		return false;
	}

	std::string iisuSdkDir(iisuSdkDir_char);
	std::string iisuBinDir = iisuSdkDir + "\\bin";

	SK::IisuHandle::Configuration handleConf(iisuBinDir.c_str());
	SK::Return<SK::IisuHandle*> retHandle = context.createHandle(handleConf);
	if (retHandle.failed())
	{
		SK_LOGGER(LOG_ERROR) << retHandle.getDescription().ptr();
		return false;
	}
	SK::IisuHandle* handle = retHandle.get();

	SK_LOGGER(LOG_INFO) << "The application handle was obtained.";

	// Iisu device.
	SK::Device::Configuration deviceConf;
	SK::Return<SK::Device*> retDevice = handle->initializeDevice(deviceConf);
	if (retDevice.failed())
	{
		SK_LOGGER(LOG_ERROR) << retDevice.getDescription().ptr();

		SK::Result result = context.destroyHandle(*handle);
		if (result.failed())
			SK_LOGGER(LOG_ERROR) << result.getDescription().ptr();

		return false;
	}
	m_device = retDevice.get();

	SK_LOGGER(LOG_INFO) << "The iisu device was obtained.";

	// Iisu events registration.
	m_device->getEventManager().registerEventListener("SYSTEM.Error", *this, &IisuManager::iisuErrorListener);
	m_device->getEventManager().registerEventListener("DEVICE.DataFrame", *this, &IisuManager::newIisuDataFrameListener);

	SK_LOGGER(LOG_INFO) << "The event listeners were registered.";

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool IisuManager::resumeStream()
{
	// Check device.
	if (!m_device)
	{
		SK_LOGGER(LOG_ERROR) << "No iisu device available: cannot stream.";
		return false;
	}

	// Linearize PathMaps.
	linearizePathMap(m_dataBase->getPathMapsRoot());
	SK_LOGGER(LOG_INFO) << "Path maps linearization OK.";

	// Create the TypedPathMaps (depending of their type returned by iisu).
	for (uint i = 0; i < m_pathMapsLinearized.size(); ++i)
	{
		const PathMap* pathMap = m_pathMapsLinearized[i];
		assert(pathMap);

		if (pathMap->getIisuPath() == "")
			continue;

		// Check the path exists and get its type.
		SK::Return<SK::TypeInfo> retType = m_device->getDataType(pathMap->getIisuPath().c_str()) ;
		if (retType.failed())
		{
			SK_LOGGER(LOG_ERROR) << "Path \'" << pathMap->getIisuPath() << "\' does not exist.";

			continue;
		}

		std::string fullOscPaths = findFullOscPath(m_pathMapsLinearized[i]);

		SK::TypeInfo typeInfo = retType.get() ;
		TypedPathMap* typedPathMap = SK::TypeInfo::injectIisuType<BaseTypedPathMapFactory, TypedPathMapFactory>(typeInfo)->create(fullOscPaths, pathMap->getIisuPath());
	
		if (!typedPathMap)
		{
			SK_LOGGER(LOG_WARNING) << "Type \'" << typeInfo.name() << "\' is not handled by the OSC stream. Data \'" << pathMap->getIisuPath() << "\' will not stream.";

			continue;
		}

		m_typedPathMapsLinearized.push_back(typedPathMap);
	}

	SK_LOGGER(LOG_INFO) << "TypedPathMaps instantiated.";

	// Register data handles.
	IisuDataRegistrator iisuPathRegistrator(m_device, m_iisuDataHandles);
	for (uint i = 0; i < m_typedPathMapsLinearized.size(); ++i)
		m_typedPathMapsLinearized[i]->accept(&iisuPathRegistrator);

	// Start device.
	m_device->start();

	SK_LOGGER(LOG_INFO) << "The iisu engine is started.";
	SK_LOGGER(LOG_INFO) << "OscBridge is now streaming OSC...";

	return true;
}

//////////////////////////////////////////////////////////////////////////
void IisuManager::iisuErrorListener( const SK::ErrorEvent& event )
{
	SK_LOGGER(LOG_ERROR) << event.getError().getDescription();
}

//////////////////////////////////////////////////////////////////////////
void IisuManager::newIisuDataFrameListener( const SK::DataFrameEvent& event )
{
	m_device->updateFrame(true);

	oscSend();
}

//////////////////////////////////////////////////////////////////////////
bool IisuManager::pauseStream()
{
	// Stop device.
	if (m_device)
	{
		m_device->stop();

		SK_LOGGER(LOG_INFO) << "The iisu engine is stopped.";
	}

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

	// Delete the TypedPathMaps.
	for (uint i = 0; i < m_typedPathMapsLinearized.size(); ++i)
	{
		TypedPathMap* typedPathMap = m_typedPathMapsLinearized[i];
		if (typedPathMap)
			delete typedPathMap;
	}

	m_typedPathMapsLinearized.clear();

	// clear the array of linearized path maps.
	m_pathMapsLinearized.clear();

	return false;
}

//////////////////////////////////////////////////////////////////////////
void IisuManager::termIisu()
{
	if (m_device)
	{
		SK::Context::Instance().finalize();
		m_device = 0;
	}

	SK_LOGGER(LOG_INFO) << "The iisu engine was destroyed.";
}

//////////////////////////////////////////////////////////////////////////
bool IisuManager::loadIidGraph(const std::string& newIidFilePath)
{
	if (!m_device)
	{
		SK_LOGGER(LOG_ERROR) << "Load IID graph : device does not exist, cannot load iid graph.";

		return false;
	}

	SK::CommandHandle<SK::Result (const SK::String&)> loadIidGraph = m_device->getCommandManager().registerCommandHandle<SK::Result(const SK::String&)>("IID.loadGraph");
	SK::Result resLoadCmd = loadIidGraph(newIidFilePath.c_str());
	if (resLoadCmd.failed())
	{
		SK_LOGGER(LOG_ERROR) << std::string("Load IID graph : ") + resLoadCmd.getDescription().ptr();

		return false;
	}

	SK_LOGGER(LOG_INFO) << "IID file loaded correctly.";

	return true;
}

//////////////////////////////////////////////////////////////////////////
void IisuManager::retrieveIisuDataPaths(std::vector<std::string>& iisuDataPaths)
{
	iisuDataPaths.clear();

	if (!m_device)
		return;

	SK::Return<uint32_t> iisuDataNum_return = m_device->getDataCount();
	if (iisuDataNum_return.failed())
		return;

	// Fills in iisuDataPaths with the iisu data paths.
	int iisuDataNum = iisuDataNum_return.get();
	for (uint i = 0; i < iisuDataNum; ++i)
	{
		SK::Return<SK::String> iisuDataPath_return = m_device->getDataName(i);
		if (iisuDataPath_return.failed())
			continue;

		iisuDataPaths.push_back(std::string(iisuDataPath_return.get().ptr()));
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuManager::linearizePathMap( const PathMap* pathMap )
{
	if (!pathMap)
		return;

	m_pathMapsLinearized.push_back(pathMap);
	for (uint i = 0; i < pathMap->getChildren().size(); ++i)
		linearizePathMap(pathMap->getChildren()[i]);
}

//////////////////////////////////////////////////////////////////////////
std::string IisuManager::findFullOscPath( const PathMap* pathMap ) const
{
	if (!pathMap)
		return "";

	// Parse PathMaps up-tree.
	std::string fullOscPath;
	const PathMap* currentPath = pathMap;
	while (currentPath != 0)
	{
		// Concatenate fullOscPath only if the PathMap's oscPathBit contains something.
		// NOTE: if the oscPathBit of a PathMap is empty, it does not modify the fullOscPath of its children,
		//       this is so that this PathMap is an organizational placeholder.
		if (currentPath->getOscPathBit()!= "")
			fullOscPath = std::string("/") + currentPath->getOscPathBit() + fullOscPath;

		currentPath = currentPath->getParent();
	}

	return fullOscPath;
}

//////////////////////////////////////////////////////////////////////////
void IisuManager::oscSend()
{
	m_device->lockFrame();

	// Create socket and stream.
	UdpTransmitSocket transmitSocket(IpEndpointName(m_dataBase->getIpAddress().c_str(), m_dataBase->getIpPort()));
	osc::OutboundPacketStream outPacketStream(m_oscBuffer, OUTPUT_BUFFER_SIZE);

	// Build the OSC packet up.
	outPacketStream	<< osc::BeginBundleImmediate;;

	IisuReaderOscSender iisuReaderOscSender(m_dataBase, &outPacketStream);
	for (uint i = 0; i < m_typedPathMapsLinearized.size(); ++i)
	{
		TypedPathMap* typedPathMap = m_typedPathMapsLinearized[i];
		assert(typedPathMap);

		iisuReaderOscSender.setPathMapData(typedPathMap->m_fullOscPath, m_iisuDataHandles[i]);
		typedPathMap->accept(&iisuReaderOscSender);
	}

	outPacketStream	<< osc::EndBundle;

	// Stream OSC packet out.
	transmitSocket.Send(outPacketStream.Data(), outPacketStream.Size());

	// Store packet size.
	m_dataBase->setOscPacketSize(outPacketStream.Size());

	m_device->releaseFrame();
}

} // namespace SK.