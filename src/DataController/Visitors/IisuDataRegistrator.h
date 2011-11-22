#pragma once

#include <Platform/SkPlatform.h>
#include "DataBase/PathMapVisitor.h"
#include <vector>

namespace SK
{

class Device;
class IIisuDataExtractor;
class PathMap;

//////////////////////////////////////////////////////////////////////////
/// \brief This class is a visitor that makes the path registration in iisu for the PathMap objects.
class IisuDataRegistrator : public PathMapVisitor
{
public:
	IisuDataRegistrator(SK::Device* device, std::vector<SK::IIisuDataExtractor*>& dataHandles, std::vector<PathMap*>& pathAssociators);
	~IisuDataRegistrator() {}

protected:
	/// \name Visitor's methods.
	//@{
	void visit(PathMap* pathMap) SK_OVERRIDE;
	void visit(DataPathMap* pathMap) SK_OVERRIDE {} // Cannot register a generic data.
	void visit(BooleanPathMap* pathMap) SK_OVERRIDE;
	void visit(IntegerPathMap* pathMap) SK_OVERRIDE;
	void visit(Vector3PathMap* pathMap) SK_OVERRIDE;
	void visit(ArrayPathMap* pathMap) SK_OVERRIDE {} // Cannot register a generic array.
	void visit(FloatArrayPathMap* pathMap) SK_OVERRIDE;
	void visit(Vector3ArrayPathMap* pathMap) SK_OVERRIDE;
	//@}

	SK::Device* m_device;
	std::vector<IIisuDataExtractor*>& m_dataHandles;
	std::vector<PathMap*>& m_pathAssociators;
};

} // namespace SK.