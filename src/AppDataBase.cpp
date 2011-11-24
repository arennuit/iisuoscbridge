#include "AppDataBase.h"

#include "MainForm.h"

namespace SK
{

DEFINE_DATA_BASE(AppDataBase, DataBase)

//////////////////////////////////////////////////////////////////////////
void AppDataBase::setPathMapsTreeRoot(TypedPathMap* pathMapsTreeRoot)
{
	DataBase::setPathMapsTreeRoot(pathMapsTreeRoot);

	m_mainForm->onIsPathMapsTreeRootChanged();
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