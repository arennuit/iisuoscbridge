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
class BoolPathMap : public DataTypedPathMap
{
public:
	BoolPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
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
class Vector3PathMap : public DataTypedPathMap
{
public:
	Vector3PathMap(const std::string& fullOscPath, const std::string& iisuPath) :
		DataTypedPathMap(fullOscPath, iisuPath) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
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
class FloatArrayPathMap : public ArrayPathMap
{
public:
	FloatArrayPathMap(const std::string& fullOscPath, const std::string& iisuPath) :
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

} // namespace SK.