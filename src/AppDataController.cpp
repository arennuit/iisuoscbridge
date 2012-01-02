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
	// Base callback.
	DataController::onIpAddressChanged(ipAddress);

	// Propagate operation up-stream.
	m_mainForm->onIpAddressChanged(ipAddress);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onPortChanged(int port)
{
	// Base callback.
	DataController::onPortChanged(port);

	// Propagate operation up-stream.
	m_mainForm->onPortChanged(port);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onIidFilePathChanged(const std::string& iidFilePath)
{
	// Base callback.
	DataController::onIidFilePathChanged(iidFilePath);

	// Propagate operation up-stream.
	m_mainForm->onIidFilePathChanged(iidFilePath);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onIsObservationOnChanged(bool isObservationOn)
{
	// Base callback.
	DataController::onIsObservationOnChanged(isObservationOn);

	// Propagate operation up-stream.
	m_mainForm->onIsObservationOnChanged(isObservationOn);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onIsFoldAndNameJointsChanged(bool isFoldAndNameJoints)
{
	// Base callback.
	DataController::onIsFoldAndNameJointsChanged(isFoldAndNameJoints);

	// Propagate operation up-stream.
	m_mainForm->onIsFoldAndNameJointsChanged(isFoldAndNameJoints);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onOscPacketSizeChanged(uint oscPacketSize)
{
	// Base callback.
	DataController::onOscPacketSizeChanged(oscPacketSize);

	// Propagate operation up-stream.
	m_mainForm->onOscPacketSizeChanged(oscPacketSize);
}

} // namespace SK.