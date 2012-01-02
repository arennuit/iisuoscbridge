#include "AppDataBase.h"

#include "Core/DataController.h"

namespace SK
{

DEFINE_DATA_BASE(AppDataBase, DataBase)

//////////////////////////////////////////////////////////////////////////
const PathMap* AppDataBase::addPathMap(const PathMap* siblingPathMap, const std::string& oscPathBit /*= NEW_OSC_PATH_BIT*/, const std::string& iisuPath /*= NEW_IISU_PATH*/)
{
	// Perform operation.
	const PathMap* newPathMap = DataBase::addPathMap(siblingPathMap, oscPathBit, iisuPath);
	if (!newPathMap)
		return 0;

	// Propagate operation up-stream.
	m_dataController->onAddPathMap(newPathMap);

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
const PathMap* AppDataBase::insertPathMap(const PathMap* siblingPathMap, const std::string& oscPathBit /*= NEW_OSC_PATH_BIT*/, const std::string& iisuPath /*= NEW_IISU_PATH*/)
{
	// Perform operation.
	const PathMap* newPathMap = DataBase::insertPathMap(siblingPathMap, oscPathBit, iisuPath);
	if (!newPathMap)
		return 0;

	// Propagate operation up-stream.
	m_dataController->onInsertPathMap(newPathMap);

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
const PathMap* AppDataBase::addChildMap(const PathMap* parentPathMap, const std::string& oscPathBit /*= NEW_OSC_PATH_BIT*/, const std::string& iisuPath /*= NEW_IISU_PATH*/)
{
	// Perform operation.
	const PathMap* newPathMap = DataBase::addChildMap(parentPathMap, oscPathBit, iisuPath);
	if (!newPathMap)
		return 0;

	// Propagate operation up-stream.
	m_dataController->onAddChildMap(newPathMap);

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
bool AppDataBase::deletePathMap(const PathMap* pathMap)
{
	// Propagate operation up-stream.
	m_dataController->onDeletePathMap(pathMap);

	// Perform operation.
	return DataBase::deletePathMap(pathMap);
}

//////////////////////////////////////////////////////////////////////////
bool AppDataBase::clearPathMaps()
{
	// Propagate operation up-stream.
	m_dataController->onClearPathMaps();

	// Perform operation.
	return DataBase::clearPathMaps();
}

//////////////////////////////////////////////////////////////////////////
void AppDataBase::setIpAddress(const std::string& ipAddress)
{
	// Perform operation.
	DataBase::setIpAddress(ipAddress);

	// Propagate operation up-stream.
	m_dataController->onIpAddressChanged(ipAddress);
}

//////////////////////////////////////////////////////////////////////////
void AppDataBase::setPort(int port)
{
	// Perform operation.
	DataBase::setPort(port);

	// Propagate operation up-stream.
	m_dataController->onPortChanged(port);
}

//////////////////////////////////////////////////////////////////////////
void AppDataBase::setIidFilePath(const std::string& iidFilePath)
{
	// Perform operation.
	DataBase::setIidFilePath(iidFilePath);

	// Propagate operation up-stream.
	m_dataController->onIidFilePathChanged(iidFilePath);
}

//////////////////////////////////////////////////////////////////////////
void AppDataBase::setIsObservationOn(bool isObservationOn)
{
	// Perform operation.
	DataBase::setIsObservationOn(isObservationOn);

	// Propagate operation up-stream.
	m_dataController->onIsObservationOnChanged(isObservationOn);
}

//////////////////////////////////////////////////////////////////////////
void AppDataBase::setIsFoldAndNameJoints(bool isFoldAndNameJoints)
{
	// Perform operation.
	DataBase::setIsFoldAndNameJoints(isFoldAndNameJoints);

	// Propagate operation up-stream.
	m_dataController->onIsFoldAndNameJointsChanged(isFoldAndNameJoints);
}

//////////////////////////////////////////////////////////////////////////
void AppDataBase::setOscPacketSize(uint oscPacketSize)
{
	// Perform operation.
	DataBase::setOscPacketSize(oscPacketSize);

	// Propagate operation up-stream.
	m_dataController->onOscPacketSizeChanged(m_oscPacketSize);
}

} // namespace SK.