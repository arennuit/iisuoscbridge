#include "IisuDataRegistrator.h"
#include "SDK/iisuSDK.h"
#include "DataBase/PathMapItem.h"

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
	SK::DataHandle<bool>* handle = new SK::DataHandle<bool>();
	*handle = m_device->registerDataHandle<bool>(pathItem->m_iisuPath.c_str());
	m_dataHandles.push_back(handle);
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector3PathMapItem* pathItem)
{
	assert(pathItem);

	// Register iisu path.
	SK::DataHandle<SK::Vector3>* handle = new SK::DataHandle<SK::Vector3>();
	*handle = m_device->registerDataHandle<SK::Vector3>(pathItem->m_iisuPath.c_str());
	m_dataHandles.push_back(handle);
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(FloatArrayPathMapItem* pathItem)
{
	assert(pathItem);

	// Register iisu path.
	SK::DataHandle<SK::Array<float> >* handle = new SK::DataHandle<SK::Array<float> >();
	*handle = m_device->registerDataHandle<SK::Array<float> >(pathItem->m_iisuPath.c_str());
	m_dataHandles.push_back(handle);
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector3ArrayPathMapItem* pathItem)
{
	assert(pathItem);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::Vector3> >* handle = new SK::DataHandle<SK::Array<SK::Vector3> >();
	*handle = m_device->registerDataHandle<SK::Array<SK::Vector3> >(pathItem->m_iisuPath.c_str());
	m_dataHandles.push_back(handle);
}

} // namespace SK.