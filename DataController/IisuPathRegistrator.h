#pragma once

#include <Platform/SkPlatform.h>
#include "DataBase/PathMapItemVisitor.h"
#include <vector>

namespace SK
{

class Device;
class IIisuDataExtractor;
class PathMapItem;

//////////////////////////////////////////////////////////////////////////
/// \name This class is a visitor that makes the path registration in iisu for the PathMapItem objects.
class IisuPathRegistrator : public PathMapItemVisitor
{
public:
	IisuPathRegistrator(SK::Device* device, std::vector<IIisuDataExtractor*>& dataHandles, std::vector<PathMapItem*>& pathAssociators);
	~IisuPathRegistrator() {}

protected:
	void visit(PathMapItem* pathItem) SK_OVERRIDE;
	void visit(DataPathMapItem* pathItem) SK_OVERRIDE {}
	void visit(BooleanPathMapItem* pathItem) SK_OVERRIDE;
	void visit(Vector3ArrayPathMapItem* pathItem) SK_OVERRIDE;
	void visit(FloatArrayPathMapItem* pathItem) SK_OVERRIDE;

	SK::Device* m_device;
	std::vector<IIisuDataExtractor*>& m_dataHandles;
	std::vector<PathMapItem*>& m_pathAssociators;
};

} // namespace SK.