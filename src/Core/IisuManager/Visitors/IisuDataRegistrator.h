#pragma once

#include <Platform/SkPlatform.h>
#include "Core/IisuManager/TypedPathMap/TypedPathMapVisitor.h"
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
	IisuDataRegistrator(SK::Device* device, std::vector<SK::IIisuDataExtractor*>& dataHandles);
	~IisuDataRegistrator() {}

protected:
	/// \name Visitor's methods.
	//@{
	void visit(TypedPathMap* typedPathMap) SK_OVERRIDE;
	void visit(DataTypedPathMap* typedPathMap) SK_OVERRIDE {} // Cannot register a generic data.
	void visit(ArrayPathMap* typedPathMap) SK_OVERRIDE {} // Cannot register a generic array.

	void visit(BoolPathMap* typedPathMap) SK_OVERRIDE;
	void visit(CharPathMap* typedPathMap) SK_OVERRIDE;
	void visit(FloatPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int8PathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int16PathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int32PathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int64PathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt8PathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt16PathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt32PathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt64PathMap* typedPathMap) SK_OVERRIDE;
	void visit(Color4cPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Color4fPathMap* typedPathMap) SK_OVERRIDE;
	void visit(EnumPathMap* typedPathMap) SK_OVERRIDE;
	void visit(FramePathMap* typedPathMap) SK_OVERRIDE;
	void visit(Matrix3PathMap* typedPathMap) SK_OVERRIDE;
	void visit(Matrix4PathMap* typedPathMap) SK_OVERRIDE;
	void visit(QuatPathMap* typedPathMap) SK_OVERRIDE;
	void visit(StringPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector2PathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector2iPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector3PathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector4PathMap* typedPathMap) SK_OVERRIDE;

	void visit(BoolArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(CharArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(FloatArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int8ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int16ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int32ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int64ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt8ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt16ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt32ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt64ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Color4cArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Color4fArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(EnumArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(FrameArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Matrix3ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Matrix4ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(QuatArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(StringArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector2ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector2iArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector3ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector4ArrayPathMap* typedPathMap) SK_OVERRIDE;
	//@}

	SK::Device* m_device;
	std::vector<IIisuDataExtractor*>& m_dataHandles;
};

} // namespace SK.