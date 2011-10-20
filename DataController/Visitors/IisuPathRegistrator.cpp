#include "IisuPathRegistrator.h"
#include "SDK/iisuSDK.h"
#include "DataBase/PathMapItem.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
IisuPathRegistrator::IisuPathRegistrator(SK::Device* device, std::vector<IIisuDataExtractor*>& dataHandles, std::vector<PathMapItem*>& pathAssociators) :
	PathMapItemVisitor(),
	m_device(device),
	m_dataHandles(dataHandles),
	m_pathAssociators(pathAssociators)
{
	assert(device);
}

//////////////////////////////////////////////////////////////////////////
void IisuPathRegistrator::visit(PathMapItem* pathItem)
{
	assert(pathItem);

	// No iisu data is associated to a plain PathMapItem.
	m_dataHandles.push_back(0);
}

//////////////////////////////////////////////////////////////////////////
void IisuPathRegistrator::visit(BooleanPathMapItem* pathItem)
{
	assert(pathItem);

	// Register iisu path.
	SK::DataHandle<bool>* handle = new SK::DataHandle<bool>();
	*handle = m_device->registerDataHandle<bool>(pathItem->m_iisuPath.c_str());
	m_dataHandles.push_back(handle);
}

//////////////////////////////////////////////////////////////////////////
void IisuPathRegistrator::visit(Vector3ArrayPathMapItem* pathItem)
{
	assert(pathItem);

	// TODO: register a data handle.
	m_dataHandles.push_back(0);
}

//////////////////////////////////////////////////////////////////////////
void IisuPathRegistrator::visit(FloatArrayPathMapItem* pathItem)
{
	assert(pathItem);

	// TODO: register a data handle.
	m_dataHandles.push_back(0);
}

} // namespace SK.