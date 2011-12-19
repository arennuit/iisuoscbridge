#include "AppDataBase.h"

#include "MainForm.h"

namespace SK
{

DEFINE_DATA_BASE(AppDataBase, DataBase)

//////////////////////////////////////////////////////////////////////////
const PathMap* AppDataBase::addPathMap(PathMap* siblingPathMap)
{
	const PathMap* newPathMap = DataBase::addPathMap(siblingPathMap);
	if (!newPathMap)
		return 0;

	// GUI.
	m_mainForm->onAddPathMap(newPathMap);

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
const PathMap* AppDataBase::insertPathMap(PathMap* siblingPathMap)
{
	const PathMap* newPathMap = DataBase::insertPathMap(siblingPathMap);
	if (!newPathMap)
		return 0;

	// GUI.
	m_mainForm->onInsertPathMap(newPathMap);

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
const PathMap* AppDataBase::addChildMap(PathMap* parentPathMap)
{
	const PathMap* newPathMap = DataBase::addChildMap(parentPathMap);
	if (!newPathMap)
		return 0;

	// GUI.
	m_mainForm->onAddChildMap(newPathMap);

	return newPathMap;
}

//////////////////////////////////////////////////////////////////////////
bool AppDataBase::deletePathMap(PathMap* pathMap)
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