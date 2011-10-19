#pragma once

#include <Platform/SkPlatform.h>
#include "DataBase/PathAssociationVisitor.h"
#include <vector>

namespace SK
{

class Device;
class IIisuDataExtractor;
class PathAssociation;

//////////////////////////////////////////////////////////////////////////
/// \name This class is a visitor that makes the path registration in iisu for the PathAssociation objects.
class IisuPathRegistrator : public PathAssociationVisitor
{
public:
	IisuPathRegistrator(SK::Device* device, std::vector<IIisuDataExtractor*>& dataHandles, std::vector<PathAssociation*>& pathAssociators);
	~IisuPathRegistrator() {}

protected:
	void visit(PathAssociation* pathAssociation) SK_OVERRIDE;
	void visit(DataPathAssociation* pathAssociation) SK_OVERRIDE {}
	void visit(BooleanPathAssociation* pathAssociation) SK_OVERRIDE;
	void visit(Vector3ArrayPathAssociation* pathAssociation) SK_OVERRIDE;
	void visit(FloatArrayPathAssociation* pathAssociation) SK_OVERRIDE;

	SK::Device* m_device;
	std::vector<IIisuDataExtractor*>& m_dataHandles;
	std::vector<PathAssociation*>& m_pathAssociators;
};

} // namespace SK.