#include "IisuDataRegistrator.h"
#include "SDK/iisuSDK.h"
#include "DataBase/PathMapItem.h"
#include "LogSystem/Logger.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
IisuDataRegistrator::IisuDataRegistrator(SK::Device* device, std::vector<SK::IIisuDataExtractor*>& dataHandles, std::vector<PathMapItem*>& pathAssociators) :
	PathMapItemVisitor(),
	m_device(device),
	m_dataHandles(dataHandles),
	m_pathAssociators(pathAssociators)
{
	assert(device);
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(PathMapItem* pathItem)
{
	assert(pathItem);

	// No iisu data is associated to a plain PathMapItem.
	m_dataHandles.push_back(0);
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(BooleanPathMapItem* pathItem)
{
	assert(pathItem);

	// Register iisu path.
	SK::DataHandle<bool> handleTmp = m_device->registerDataHandle<bool>(pathItem->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + pathItem->m_iisuPath;
		return;
	}

	SK::DataHandle<bool>* handle = new SK::DataHandle<bool>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + pathItem->m_iisuPath;
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu handle registration OK: " + pathItem->m_iisuPath;
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(IntegerPathMapItem* pathItem)
{
	assert(pathItem);

	// Register iisu path.
	SK::DataHandle<int> handleTmp = m_device->registerDataHandle<int>(pathItem->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + pathItem->m_iisuPath;
		return;
	}

	SK::DataHandle<int>* handle = new SK::DataHandle<int>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + pathItem->m_iisuPath;
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu handle registration OK: " + pathItem->m_iisuPath;
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector3PathMapItem* pathItem)
{
	assert(pathItem);

	// Register iisu path.
	SK::DataHandle<SK::Vector3> handleTmp = m_device->registerDataHandle<SK::Vector3>(pathItem->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + pathItem->m_iisuPath;
		return;
	}

	SK::DataHandle<SK::Vector3>* handle = new SK::DataHandle<SK::Vector3>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + pathItem->m_iisuPath;
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu handle registration OK: " + pathItem->m_iisuPath;
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(FloatArrayPathMapItem* pathItem)
{
	assert(pathItem);

	// Register iisu path.
	SK::DataHandle<SK::Array<float> > handleTmp = m_device->registerDataHandle<SK::Array<float> >(pathItem->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + pathItem->m_iisuPath;
		return;
	}

	SK::DataHandle<SK::Array<float> >* handle = new SK::DataHandle<SK::Array<float> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + pathItem->m_iisuPath;
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu handle registration OK: " + pathItem->m_iisuPath;
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector3ArrayPathMapItem* pathItem)
{
	assert(pathItem);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::Vector3> > handleTmp = m_device->registerDataHandle<SK::Array<SK::Vector3> >(pathItem->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + pathItem->m_iisuPath;
		return;
	}

	SK::DataHandle<SK::Array<SK::Vector3> >* handle = new SK::DataHandle<SK::Array<SK::Vector3> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + pathItem->m_iisuPath;
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu handle registration OK: " + pathItem->m_iisuPath;
}

} // namespace SK.