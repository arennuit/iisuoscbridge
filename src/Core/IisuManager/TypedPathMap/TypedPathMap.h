#pragma once

#include <vector>
#include <string>
#include "Platform/SkPlatform.h"
#include "TypedPathMapVisitor.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \brief The concrete TypedPathMap class is used to format OSC paths. But the class is also inherited
///        by items actually pointing to proper iisu data.
class TypedPathMap
{
public:
	TypedPathMap(const std::string& fullOscPath);
	virtual ~TypedPathMap() {}

	// Map.
	std::string m_fullOscPath;

	// Visitor.
	virtual void accept(TypedPathMapVisitor* visitor) {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class DataTypedPathMap : public TypedPathMap
{
public:
	DataTypedPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		TypedPathMap(fullOscPath),
		m_iisuPath(iisuPath) {}

	// Map.
	std::string m_iisuPath;

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE = 0;
};

//////////////////////////////////////////////////////////////////////////
class ArrayPathMap : public DataTypedPathMap
{
public:
	ArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) = 0;
};

//////////////////////////////////////////////////////////////////////////
class BoolPathMap : public DataTypedPathMap
{
public:
	BoolPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class CharPathMap : public DataTypedPathMap
{
public:
	CharPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class FloatPathMap : public DataTypedPathMap
{
public:
	FloatPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Int8PathMap : public DataTypedPathMap
{
public:
	Int8PathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Int16PathMap : public DataTypedPathMap
{
public:
	Int16PathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Int32PathMap : public DataTypedPathMap
{
public:
	Int32PathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Int64PathMap : public DataTypedPathMap
{
public:
	Int64PathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class UInt8PathMap : public DataTypedPathMap
{
public:
	UInt8PathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class UInt16PathMap : public DataTypedPathMap
{
public:
	UInt16PathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class UInt32PathMap : public DataTypedPathMap
{
public:
	UInt32PathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class UInt64PathMap : public DataTypedPathMap
{
public:
	UInt64PathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Color4cPathMap : public DataTypedPathMap
{
public:
	Color4cPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Color4fPathMap : public DataTypedPathMap
{
public:
	Color4fPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class EnumPathMap : public DataTypedPathMap
{
public:
	EnumPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class FramePathMap : public DataTypedPathMap
{
public:
	FramePathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Matrix3PathMap : public DataTypedPathMap
{
public:
	Matrix3PathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Matrix4PathMap : public DataTypedPathMap
{
public:
	Matrix4PathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class QuatPathMap : public DataTypedPathMap
{
public:
	QuatPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class StringPathMap : public DataTypedPathMap
{
public:
	StringPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector2PathMap : public DataTypedPathMap
{
public:
	Vector2PathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector2iPathMap : public DataTypedPathMap
{
public:
	Vector2iPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector3PathMap : public DataTypedPathMap
{
public:
	Vector3PathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector4PathMap : public DataTypedPathMap
{
public:
	Vector4PathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class BoolArrayPathMap : public ArrayPathMap
{
public:
	BoolArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class CharArrayPathMap : public ArrayPathMap
{
public:
	CharArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class FloatArrayPathMap : public ArrayPathMap
{
public:
	FloatArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Int8ArrayPathMap : public ArrayPathMap
{
public:
	Int8ArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Int16ArrayPathMap : public ArrayPathMap
{
public:
	Int16ArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Int32ArrayPathMap : public ArrayPathMap
{
public:
	Int32ArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Int64ArrayPathMap : public ArrayPathMap
{
public:
	Int64ArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class UInt8ArrayPathMap : public ArrayPathMap
{
public:
	UInt8ArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class UInt16ArrayPathMap : public ArrayPathMap
{
public:
	UInt16ArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class UInt32ArrayPathMap : public ArrayPathMap
{
public:
	UInt32ArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class UInt64ArrayPathMap : public ArrayPathMap
{
public:
	UInt64ArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Color4cArrayPathMap : public ArrayPathMap
{
public:
	Color4cArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Color4fArrayPathMap : public ArrayPathMap
{
public:
	Color4fArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class EnumArrayPathMap : public ArrayPathMap
{
public:
	EnumArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class FrameArrayPathMap : public ArrayPathMap
{
public:
	FrameArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Matrix3ArrayPathMap : public ArrayPathMap
{
public:
	Matrix3ArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Matrix4ArrayPathMap : public ArrayPathMap
{
public:
	Matrix4ArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class QuatArrayPathMap : public ArrayPathMap
{
public:
	QuatArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class StringArrayPathMap : public ArrayPathMap
{
public:
	StringArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector2ArrayPathMap : public ArrayPathMap
{
public:
	Vector2ArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector2iArrayPathMap : public ArrayPathMap
{
public:
	Vector2iArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector3ArrayPathMap : public ArrayPathMap
{
public:
	Vector3ArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector4ArrayPathMap : public ArrayPathMap
{
public:
	Vector4ArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		ArrayPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

} // namespace SK.