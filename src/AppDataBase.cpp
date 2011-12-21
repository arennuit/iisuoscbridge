#include "AppDataBase.h"

#include "MainForm.h"

namespace SK
{

DEFINE_DATA_BASE(AppDataBase, DataBase)

//////////////////////////////////////////////////////////////////////////
const PathMap* AppDataBase::addPathMap(const PathMap* siblingPathMap, const std::string& oscPathBit /*= NEW_OSC_PATH_BIT*/, const std::string& iisuPath /*= NEW_IISU_PATH*/)
{
	const PathMap* newPathMap = DataBase::addPathMap(siblingPathMap, oscPathBit, iisuPath);
	if (!newPathMap)
		return 0;

	// GUI.
	m_mainForm->onAddPathMap(newPathMap);

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
const PathMap* AppDataBase::insertPathMap(const PathMap* siblingPathMap, const std::string& oscPathBit /*= NEW_OSC_PATH_BIT*/, const std::string& iisuPath /*= NEW_IISU_PATH*/)
{
	const PathMap* newPathMap = DataBase::insertPathMap(siblingPathMap, oscPathBit, iisuPath);
	if (!newPathMap)
		return 0;

	// GUI.
	m_mainForm->onInsertPathMap(newPathMap);

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
const PathMap* AppDataBase::addChildMap(const PathMap* parentPathMap, const std::string& oscPathBit /*= NEW_OSC_PATH_BIT*/, const std::string& iisuPath /*= NEW_IISU_PATH*/)
{
	const PathMap* newPathMap = DataBase::addChildMap(parentPathMap, oscPathBit, iisuPath);
	if (!newPathMap)
		return 0;

	// GUI.
	m_mainForm->onAddChildMap(newPathMap);

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
bool AppDataBase::deletePathMap(const PathMap* pathMap)
{
	bool retVal = DataBase::deletePathMap(pathMap);
	if (!retVal)
		return false;

	// GUI.
	m_mainForm->onDeletePathMap();

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool AppDataBase::clearPathMaps()
{
	bool retVal = DataBase::clearPathMaps();
	if (!retVal)
		return false;

	// GUI.
	m_mainForm->onClearPathMaps();

	return true;
}

//////////////////////////////////////////////////////////////////////////
void AppDataBase::setIsObservationOn(bool isObservationOn)
{
	DataBase::setIsObservationOn(isObservationOn);

	// GUI.
	m_mainForm->onIsObservationOnChanged(isObservationOn);
}

//////////////////////////////////////////////////////////////////////////
void AppDataBase::setOscPacketSize(uint oscPacketSize)
{
	DataBase::setOscPacketSize(oscPacketSize);

	// GUI.
	m_mainForm->onOscPacketSizeChanged(m_oscPacketSize);
}

} // namespace SK.