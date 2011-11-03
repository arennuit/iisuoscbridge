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
/// \brief This class is a visitor that makes the path registration in iisu for the PathMapItem objects.
class IisuDataRegistrator : public PathMapItemVisitor
{
public:
	IisuDataRegistrator(SK::Device* device, std::vector<SK::IIisuDataExtractor*>& dataHandles, std::vector<PathMapItem*>& pathAssociators);
	~IisuDataRegistrator() {}

protected:
	/// \name Visitor's methods.
	//@{
	void visit(PathMapItem* pathItem) SK_OVERRIDE;
	void visit(DataPathMapItem* pathItem) SK_OVERRIDE {} // Cannot register a generic data.
	void visit(BooleanPathMapItem* pathItem) SK_OVERRIDE;
	void visit(Vector3PathMapItem* pathItem) SK_OVERRIDE;
	void visit(ArrayPathMapItem* pathItem) SK_OVERRIDE {} // Cannot register a generic array.
	void visit(FloatArrayPathMapItem* pathItem) SK_OVERRIDE;
	void visit(Vector3ArrayPathMapItem* pathItem) SK_OVERRIDE;
	//@}

	SK::Device* m_device;
	std::vector<IIisuDataExtractor*>& m_dataHandles;
	std::vector<PathMapItem*>& m_pathAssociators;
};

} // namespace SK.