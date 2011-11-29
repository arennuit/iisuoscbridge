#include "AppDataBase.h"

#include "MainForm.h"

namespace SK
{

DEFINE_DATA_BASE(AppDataBase, DataBase)

//////////////////////////////////////////////////////////////////////////
void AppDataBase::setPathMapsRoot(PathMap* pathMapsRoot)
{
	DataBase::setPathMapsRoot(pathMapsRoot);

	m_mainForm->onPathMapsRootChanged();
}

//////////////////////////////////////////////////////////////////////////
void AppDataBase::setIsObservationOn(bool isObservationOn)
{
	DataBase::setIsObservationOn(isObservationOn);

	m_mainForm->onIsObservationOnChanged(isObservationOn);
}

//////////////////////////////////////////////////////////////////////////
void AppDataBase::setOscPacketSize(uint oscPacketSize)
{
	DataBase::setOscPacketSize(oscPacketSize);

	m_mainForm->onOscPacketSizeChanged(m_oscPacketSize);
}

} // namespace SK.