#include "AppDataController.h"

namespace SK
{

DEFINE_DATA_BASE(AppDataController, DataController)

//////////////////////////////////////////////////////////////////////////
void AppDataController::editSelection(const PathMap* newSelectedPathMap)
{
	// Perform operation.
	DataController::editSelection(newSelectedPathMap);

	// Propagate operation up-stream.
	m_mainForm->onEditSelection(newSelectedPathMap);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::loadProjectFromFile(std::string& filePath)
{
	// Perform operation.
	DataController::loadProjectFromFile(filePath);

	// Propagate operation up-stream.
	m_mainForm->onLoadProjectFromFile();
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onAddPathMap(const PathMap* newPathMap)
{
	// Propagate operation up-stream.
	m_mainForm->onAddPathMap(newPathMap);

	// Base callback.
	DataController::onAddPathMap(newPathMap);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onInsertPathMap(const PathMap* newPathMap)
{
	// Propagate operation up-stream.
	m_mainForm->onInsertPathMap(newPathMap);

	// Base callback.
	DataController::onInsertPathMap(newPathMap);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onAddChildMap(const PathMap* newPathMap)
{
	// Propagate operation up-stream.
	m_mainForm->onAddChildMap(newPathMap);

	// Base callback.
	DataController::onAddChildMap(newPathMap);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onDeletePathMap(const PathMap* pathMapToBeDeleted)
{
	// Base callback.
	DataController::onDeletePathMap(pathMapToBeDeleted);

	// Propagate operation up-stream.
	m_mainForm->onDeletePathMap(pathMapToBeDeleted);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onClearPathMaps()
{
	// Base callback.
	DataController::onClearPathMaps();

	// Propagate operation up-stream.
	m_mainForm->onClearPathMaps();
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onIpAddressChanged(const std::string& ipAddress)
{
	// Propagate operation up-stream.
	m_mainForm->onIpAddressChanged(ipAddress);

	// Base callback.
	DataController::onIpAddressChanged(ipAddress);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onIpPortChanged(int ipPort)
{
	// Propagate operation up-stream.
	m_mainForm->onIpPortChanged(ipPort);

	// Base callback.
	DataController::onIpPortChanged(ipPort);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onIidFilePathChanged(const std::string& iidFilePath)
{
	// Propagate operation up-stream.
	m_mainForm->onIidFilePathChanged(iidFilePath);

	// Base callback.
	DataController::onIidFilePathChanged(iidFilePath);
}

//////////////////////////////////////////////////////////////////////////
bool AppDataController::onMocapStateChanged(bool desiredMocapState)
{
	// Base callback.
	bool mocapState = DataController::onMocapStateChanged(desiredMocapState);

	// Actually call the database modification function (it is here that DataBase::m_mocapState is set
	// depending on the result of DataController::onMocapStateChanged()).
	m_dataBase->DataBase::setMocapState(mocapState);

	// Propagate operation up-stream.
	m_mainForm->onMocapStateChanged(mocapState);

	return mocapState;
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onDecorateStreamChanged(bool decorateStream)
{
	// Propagate operation up-stream.
	m_mainForm->decorateStreamChanged(decorateStream);

	// Base callback.
	DataController::onDecorateStreamChanged(decorateStream);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onOscPacketSizeChanged(uint oscPacketSize)
{
	// Propagate operation up-stream.
	m_mainForm->onOscPacketSizeChanged(oscPacketSize);

	// Base callback.
	DataController::onOscPacketSizeChanged(oscPacketSize);
}

} // namespace SK.