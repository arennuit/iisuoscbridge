#include "IisuDataRegistrator.h"
#include "SDK/iisuSDK.h"
#include "DataBase/PathMap.h"
#include "LogSystem/Logger.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
IisuDataRegistrator::IisuDataRegistrator(SK::Device* device, std::vector<SK::IIisuDataExtractor*>& dataHandles, std::vector<PathMap*>& pathAssociators) :
	PathMapVisitor(),
	m_device(device),
	m_dataHandles(dataHandles),
	m_pathAssociators(pathAssociators)
{
	assert(device);
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(PathMap* pathMap)
{
	assert(pathMap);

	// No iisu data is associated to a plain PathMap.
	m_dataHandles.push_back(0);
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(BooleanPathMap* pathMap)
{
	assert(pathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<bool> handleTmp = m_device->registerDataHandle<bool>(pathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + pathMap->m_iisuPath;
		return;
	}

	SK::DataHandle<bool>* handle = new SK::DataHandle<bool>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + pathMap->m_iisuPath;
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu handle registration OK: " + pathMap->m_iisuPath;
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(IntegerPathMap* pathMap)
{
	assert(pathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<int> handleTmp = m_device->registerDataHandle<int>(pathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + pathMap->m_iisuPath;
		return;
	}

	SK::DataHandle<int>* handle = new SK::DataHandle<int>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + pathMap->m_iisuPath;
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu handle registration OK: " + pathMap->m_iisuPath;
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector3PathMap* pathMap)
{
	assert(pathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Vector3> handleTmp = m_device->registerDataHandle<SK::Vector3>(pathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + pathMap->m_iisuPath;
		return;
	}

	SK::DataHandle<SK::Vector3>* handle = new SK::DataHandle<SK::Vector3>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + pathMap->m_iisuPath;
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu handle registration OK: " + pathMap->m_iisuPath;
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(FloatArrayPathMap* pathMap)
{
	assert(pathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<float> > handleTmp = m_device->registerDataHandle<SK::Array<float> >(pathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + pathMap->m_iisuPath;
		return;
	}

	SK::DataHandle<SK::Array<float> >* handle = new SK::DataHandle<SK::Array<float> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + pathMap->m_iisuPath;
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu handle registration OK: " + pathMap->m_iisuPath;
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector3ArrayPathMap* pathMap)
{
	assert(pathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::Vector3> > handleTmp = m_device->registerDataHandle<SK::Array<SK::Vector3> >(pathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + pathMap->m_iisuPath;
		return;
	}

	SK::DataHandle<SK::Array<SK::Vector3> >* handle = new SK::DataHandle<SK::Array<SK::Vector3> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + pathMap->m_iisuPath;
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu handle registration OK: " + pathMap->m_iisuPath;
}

} // namespace SK.