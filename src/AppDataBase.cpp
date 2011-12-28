#include "AppDataBase.h"

#include "Core/DataController.h"

namespace SK
{

DEFINE_DATA_BASE(AppDataBase, DataBase)

//////////////////////////////////////////////////////////////////////////
const PathMap* AppDataBase::addPathMap(const PathMap* siblingPathMap, const std::string& oscPathBit /*= NEW_OSC_PATH_BIT*/, const std::string& iisuPath /*= NEW_IISU_PATH*/)
{
	// Actually perform the operation.
	const PathMap* newPathMap = DataBase::addPathMap(siblingPathMap, oscPathBit, iisuPath);
	if (!newPathMap)
		return 0;

	// Controller.
	m_dataController->onAddPathMap(newPathMap);

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
const PathMap* AppDataBase::insertPathMap(const PathMap* siblingPathMap, const std::string& oscPathBit /*= NEW_OSC_PATH_BIT*/, const std::string& iisuPath /*= NEW_IISU_PATH*/)
{
	// Actually perform the operation.
	const PathMap* newPathMap = DataBase::insertPathMap(siblingPathMap, oscPathBit, iisuPath);
	if (!newPathMap)
		return 0;

	// Controller.
	m_dataController->onInsertPathMap(newPathMap);

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
const PathMap* AppDataBase::addChildMap(const PathMap* parentPathMap, const std::string& oscPathBit /*= NEW_OSC_PATH_BIT*/, const std::string& iisuPath /*= NEW_IISU_PATH*/)
{
	// Actually perform the operation.
	const PathMap* newPathMap = DataBase::addChildMap(parentPathMap, oscPathBit, iisuPath);
	if (!newPathMap)
		return 0;

	// Controller.
	m_dataController->onAddChildMap(newPathMap);

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
bool AppDataBase::deletePathMap(const PathMap* pathMap)
{
	// Controller.
	m_dataController->onDeletePathMap(pathMap);

	// Actually perform the operation.
	return DataBase::deletePathMap(pathMap);
}

//////////////////////////////////////////////////////////////////////////
bool AppDataBase::clearPathMaps()
{
	// Controller.
	m_dataController->onClearPathMaps();

	// Actually perform the operation.
	return DataBase::clearPathMaps();
}

//////////////////////////////////////////////////////////////////////////
void AppDataBase::setIsObservationOn(bool isObservationOn)
{
	// Actually perform the operation.
	DataBase::setIsObservationOn(isObservationOn);

	// Controller.
	m_dataController->onIsObservationOnChanged(isObservationOn);
}

//////////////////////////////////////////////////////////////////////////
void AppDataBase::setOscPacketSize(uint oscPacketSize)
{
	// Actually perform the operation.
	DataBase::setOscPacketSize(oscPacketSize);

	// Controller.
	m_dataController->onOscPacketSizeChanged(m_oscPacketSize);
}

} // namespace SK.