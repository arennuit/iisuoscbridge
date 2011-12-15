#include "IisuDataRegistrator.h"
#include "SDK/iisuSDK.h"
#include "Core/IisuManager/TypedPathMap/TypedPathMap.h"
#include "LogSystem/Logger.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
IisuDataRegistrator::IisuDataRegistrator(SK::Device* device, std::vector<SK::IIisuDataExtractor*>& dataHandles) :
	TypedPathMapVisitor(),
	m_device(device),
	m_dataHandles(dataHandles)
{
	assert(device);
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(TypedPathMap* typedPathMap)
{
	assert(typedPathMap);

	// No iisu data is associated to a plain TypedPathMap.
	m_dataHandles.push_back(0);
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(BooleanPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<bool> handleTmp = m_device->registerDataHandle<bool>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath;
		return;
	}

	SK::DataHandle<bool>* handle = new SK::DataHandle<bool>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath;
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu handle registration OK: " + typedPathMap->m_iisuPath;
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(IntegerPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<int> handleTmp = m_device->registerDataHandle<int>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath;
		return;
	}

	SK::DataHandle<int>* handle = new SK::DataHandle<int>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath;
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu handle registration OK: " + typedPathMap->m_iisuPath;
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector3PathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Vector3> handleTmp = m_device->registerDataHandle<SK::Vector3>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath;
		return;
	}

	SK::DataHandle<SK::Vector3>* handle = new SK::DataHandle<SK::Vector3>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath;
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu handle registration OK: " + typedPathMap->m_iisuPath;
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(FloatArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<float> > handleTmp = m_device->registerDataHandle<SK::Array<float> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath;
		return;
	}

	SK::DataHandle<SK::Array<float> >* handle = new SK::DataHandle<SK::Array<float> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath;
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu handle registration OK: " + typedPathMap->m_iisuPath;
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector3ArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::Vector3> > handleTmp = m_device->registerDataHandle<SK::Array<SK::Vector3> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath;
		return;
	}

	SK::DataHandle<SK::Array<SK::Vector3> >* handle = new SK::DataHandle<SK::Array<SK::Vector3> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath;
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu handle registration OK: " + typedPathMap->m_iisuPath;
}

} // namespace SK.