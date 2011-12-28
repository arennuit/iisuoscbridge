#include "AppDataController.h"

namespace SK
{

DEFINE_DATA_BASE(AppDataController, DataController)

//////////////////////////////////////////////////////////////////////////
void AppDataController::editSelection(const PathMap* newSelectedPathMap)
{
	// Actual callback.
	DataController::editSelection(newSelectedPathMap);

	// GUI.
	m_mainForm->onEditSelection(newSelectedPathMap);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onAddPathMap(const PathMap* newPathMap)
{
	// GUI.
	m_mainForm->onAddPathMap(newPathMap);

	// Actual callback.
	DataController::onAddPathMap(newPathMap);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onInsertPathMap(const PathMap* newPathMap)
{
	// GUI.
	m_mainForm->onInsertPathMap(newPathMap);

	// Actual callback.
	DataController::onInsertPathMap(newPathMap);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onAddChildMap(const PathMap* newPathMap)
{
	// GUI.
	m_mainForm->onAddChildMap(newPathMap);

	// Actual callback.
	DataController::onAddChildMap(newPathMap);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onDeletePathMap(const PathMap* pathMapToBeDeleted)
{
	// Actual callback.
	DataController::onDeletePathMap(pathMapToBeDeleted);

	// GUI.
	m_mainForm->onDeletePathMap(pathMapToBeDeleted);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onClearPathMaps()
{
	// Actual callback.
	DataController::onClearPathMaps();

	// GUI.
	m_mainForm->onClearPathMaps();
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onIsObservationOnChanged(bool isObservationOn)
{
	// Actual callback.
	DataController::onIsObservationOnChanged(isObservationOn);

	// GUI.
	m_mainForm->onIsObservationOnChanged(isObservationOn);
}

//////////////////////////////////////////////////////////////////////////
void AppDataController::onOscPacketSizeChanged(uint oscPacketSize)
{
	// Actual callback.
	DataController::onOscPacketSizeChanged(oscPacketSize);

	// GUI.
	m_mainForm->onOscPacketSizeChanged(oscPacketSize);
}

} // namespace SK.