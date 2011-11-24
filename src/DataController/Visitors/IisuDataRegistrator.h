#pragma once

#include <Platform/SkPlatform.h>
#include "DataBase/DataObjects/TypedPathMapVisitor.h"
#include <vector>

namespace SK
{

class Device;
class IIisuDataExtractor;
class TypedPathMap;

//////////////////////////////////////////////////////////////////////////
/// \brief This class is a visitor that makes the path registration in iisu for the TypedPathMap objects.
class IisuDataRegistrator : public TypedPathMapVisitor
{
public:
	IisuDataRegistrator(SK::Device* device, std::vector<SK::IIisuDataExtractor*>& dataHandles, std::vector<TypedPathMap*>& pathAssociators);
	~IisuDataRegistrator() {}

protected:
	/// \name Visitor's methods.
	//@{
	void visit(TypedPathMap* typedPathMap) SK_OVERRIDE;
	void visit(DataTypedPathMap* typedPathMap) SK_OVERRIDE {} // Cannot register a generic data.
	void visit(BooleanPathMap* typedPathMap) SK_OVERRIDE;
	void visit(IntegerPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector3PathMap* typedPathMap) SK_OVERRIDE;
	void visit(ArrayPathMap* typedPathMap) SK_OVERRIDE {} // Cannot register a generic array.
	void visit(FloatArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector3ArrayPathMap* typedPathMap) SK_OVERRIDE;
	//@}

	SK::Device* m_device;
	std::vector<IIisuDataExtractor*>& m_dataHandles;
	std::vector<TypedPathMap*>& m_pathAssociators;
};

} // namespace SK.