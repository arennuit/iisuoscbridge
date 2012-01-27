#pragma once

namespace SK
{

class TypedPathMap;
class DataTypedPathMap;
class ArrayPathMap;

class BoolPathMap;
class CharPathMap;
class FloatPathMap;
class Int8PathMap;
class Int16PathMap;
class Int32PathMap;
class Int64PathMap;
class UInt8PathMap;
class UInt16PathMap;
class UInt32PathMap;
class UInt64PathMap;
class Color4cPathMap;
class Color4fPathMap;
class EnumPathMap;
class FramePathMap;
class Matrix3PathMap;
class Matrix4PathMap;
class QuatPathMap;
class StringPathMap;
class Vector2PathMap;
class Vector2iPathMap;
class Vector3PathMap;
class Vector4PathMap;

class BoolArrayPathMap;
class CharArrayPathMap;
class FloatArrayPathMap;
class Int8ArrayPathMap;
class Int16ArrayPathMap;
class Int32ArrayPathMap;
class Int64ArrayPathMap;
class UInt8ArrayPathMap;
class UInt16ArrayPathMap;
class UInt32ArrayPathMap;
class UInt64ArrayPathMap;
class Color4cArrayPathMap;
class Color4fArrayPathMap;
class EnumArrayPathMap;
class FrameArrayPathMap;
class Matrix3ArrayPathMap;
class Matrix4ArrayPathMap;
class QuatArrayPathMap;
class StringArrayPathMap;
class Vector2ArrayPathMap;
class Vector2iArrayPathMap;
class Vector3ArrayPathMap;
class Vector4ArrayPathMap;

//////////////////////////////////////////////////////////////////////////
class TypedPathMapVisitor
{
public:
	/// \name Visitor's methods.
	//@{
	virtual void visit(TypedPathMap* typedPathMap) = 0;
	virtual void visit(DataTypedPathMap* typedPathMap) = 0;
	virtual void visit(ArrayPathMap* typedPathMap) = 0;

	virtual void visit(BoolPathMap* typedPathMap) = 0;
	virtual void visit(CharPathMap* typedPathMap) = 0;
	virtual void visit(FloatPathMap* typedPathMap) = 0;
	virtual void visit(Int8PathMap* typedPathMap) = 0;
	virtual void visit(Int16PathMap* typedPathMap) = 0;
	virtual void visit(Int32PathMap* typedPathMap) = 0;
	virtual void visit(Int64PathMap* typedPathMap) = 0;
	virtual void visit(UInt8PathMap* typedPathMap) = 0;
	virtual void visit(UInt16PathMap* typedPathMap) = 0;
	virtual void visit(UInt32PathMap* typedPathMap) = 0;
	virtual void visit(UInt64PathMap* typedPathMap) = 0;
	virtual void visit(Color4cPathMap* typedPathMap) = 0;
	virtual void visit(Color4fPathMap* typedPathMap) = 0;
	virtual void visit(EnumPathMap* typedPathMap) = 0;
	virtual void visit(FramePathMap* typedPathMap) = 0;
	virtual void visit(Matrix3PathMap* typedPathMap) = 0;
	virtual void visit(Matrix4PathMap* typedPathMap) = 0;
	virtual void visit(QuatPathMap* typedPathMap) = 0;
	virtual void visit(StringPathMap* typedPathMap) = 0;
	virtual void visit(Vector2PathMap* typedPathMap) = 0;
	virtual void visit(Vector2iPathMap* typedPathMap) = 0;
	virtual void visit(Vector3PathMap* typedPathMap) = 0;
	virtual void visit(Vector4PathMap* typedPathMap) = 0;

	virtual void visit(BoolArrayPathMap* typedPathMap) = 0;
	virtual void visit(CharArrayPathMap* typedPathMap) = 0;
	virtual void visit(FloatArrayPathMap* typedPathMap) = 0;
	virtual void visit(Int8ArrayPathMap* typedPathMap) = 0;
	virtual void visit(Int16ArrayPathMap* typedPathMap) = 0;
	virtual void visit(Int32ArrayPathMap* typedPathMap) = 0;
	virtual void visit(Int64ArrayPathMap* typedPathMap) = 0;
	virtual void visit(UInt8ArrayPathMap* typedPathMap) = 0;
	virtual void visit(UInt16ArrayPathMap* typedPathMap) = 0;
	virtual void visit(UInt32ArrayPathMap* typedPathMap) = 0;
	virtual void visit(UInt64ArrayPathMap* typedPathMap) = 0;
	virtual void visit(Color4cArrayPathMap* typedPathMap) = 0;
	virtual void visit(Color4fArrayPathMap* typedPathMap) = 0;
	virtual void visit(EnumArrayPathMap* typedPathMap) = 0;
	virtual void visit(FrameArrayPathMap* typedPathMap) = 0;
	virtual void visit(Matrix3ArrayPathMap* typedPathMap) = 0;
	virtual void visit(Matrix4ArrayPathMap* typedPathMap) = 0;
	virtual void visit(QuatArrayPathMap* typedPathMap) = 0;
	virtual void visit(StringArrayPathMap* typedPathMap) = 0;
	virtual void visit(Vector2ArrayPathMap* typedPathMap) = 0;
	virtual void visit(Vector2iArrayPathMap* typedPathMap) = 0;
	virtual void visit(Vector3ArrayPathMap* typedPathMap) = 0;
	virtual void visit(Vector4ArrayPathMap* typedPathMap) = 0;
	//@}
};

} // namespace SK.