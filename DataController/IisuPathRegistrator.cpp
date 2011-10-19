#include "IisuPathRegistrator.h"
#include "SDK/iisuSDK.h"
#include "DataBase/PathAssociation.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
IisuPathRegistrator::IisuPathRegistrator(SK::Device* device, std::vector<IIisuDataExtractor*>& dataHandles, std::vector<PathAssociation*>& pathAssociators) :
	PathAssociationVisitor(),
	m_device(device),
	m_dataHandles(dataHandles),
	m_pathAssociators(pathAssociators)
{
	assert(device);
}

//////////////////////////////////////////////////////////////////////////
void IisuPathRegistrator::visit(PathAssociation* pathAssociation)
{
	assert(pathAssociation);

	// No iisu data is associated to a plain PathAssociation.
	m_dataHandles.push_back(0);
}

//////////////////////////////////////////////////////////////////////////
void IisuPathRegistrator::visit(BooleanPathAssociation* pathAssociation)
{
	assert(pathAssociation);

	// Register iisu path.
	SK::DataHandle<bool>* handle = new SK::DataHandle<bool>();
	*handle = m_device->registerDataHandle<bool>(pathAssociation->m_iisuPath.c_str());
	m_dataHandles.push_back(handle);
}

//////////////////////////////////////////////////////////////////////////
void IisuPathRegistrator::visit(Vector3ArrayPathAssociation* pathAssociation)
{
	assert(pathAssociation);

	// TODO: register a data handle.
	m_dataHandles.push_back(0);
}

//////////////////////////////////////////////////////////////////////////
void IisuPathRegistrator::visit(FloatArrayPathAssociation* pathAssociation)
{
	assert(pathAssociation);

	// TODO: register a data handle.
	m_dataHandles.push_back(0);
}

} // namespace SK.