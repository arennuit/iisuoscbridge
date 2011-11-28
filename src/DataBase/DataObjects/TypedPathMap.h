#pragma once

#include <vector>
#include <string>
#include "Platform/SkPlatform.h"
#include "TypedPathMapVisitor.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \brief The concrete TypedPathMap class is used to format OSC paths. But the class is also inherited
///       by items actually pointing to proper iisu data.
class TypedPathMap
{
public:
	TypedPathMap(const std::string& oscPathBit, TypedPathMap* parent = 0);
	virtual ~TypedPathMap();

	// Map.
	std::string m_oscPathBit;

	// Handle hierarchy tree of PathMaps.
	TypedPathMap* m_parent;
	std::vector<TypedPathMap*> m_children;

	// Visitor.
	virtual void accept(TypedPathMapVisitor* visitor) {visitor->visit(this);}

protected:

	// Helpers.
	bool unParent(TypedPathMap* child);

};

//////////////////////////////////////////////////////////////////////////
class DataTypedPathMap : public TypedPathMap
{
public:
	DataTypedPathMap(const std::string& oscPathBit, const std::string& iisuPath, TypedPathMap* parent = 0) :
		TypedPathMap(oscPathBit, parent),
		m_iisuPath(iisuPath) {}

	// Map.
	std::string m_iisuPath;

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE = 0;
};

//////////////////////////////////////////////////////////////////////////
class BooleanPathMap : public DataTypedPathMap
{
public:
	BooleanPathMap(const std::string& oscPathBit, const std::string& iisuPath, TypedPathMap* parent = 0) :
		DataTypedPathMap(oscPathBit, iisuPath, parent) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class IntegerPathMap : public DataTypedPathMap
{
public:
	IntegerPathMap(const std::string& oscPathBit, const std::string& iisuPath, TypedPathMap* parent = 0) :
		DataTypedPathMap(oscPathBit, iisuPath, parent) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector3PathMap : public DataTypedPathMap
{
public:
	Vector3PathMap(const std::string& oscPathBit, const std::string& iisuPath, TypedPathMap* parent = 0) :
		DataTypedPathMap(oscPathBit, iisuPath, parent) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class ArrayPathMap : public DataTypedPathMap
{
public:
	ArrayPathMap(const std::string& oscPathBit, const std::string& iisuPath, TypedPathMap* parent = 0) :
		DataTypedPathMap(oscPathBit, iisuPath, parent) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) = 0;
};

//////////////////////////////////////////////////////////////////////////
class FloatArrayPathMap : public ArrayPathMap
{
public:
	FloatArrayPathMap(const std::string& oscPathBit, const std::string& iisuPath, TypedPathMap* parent = 0) :
		ArrayPathMap(oscPathBit, iisuPath, parent) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector3ArrayPathMap : public ArrayPathMap
{
public:
	Vector3ArrayPathMap(const std::string& oscPathBit, const std::string& iisuPath, TypedPathMap* parent = 0) :
		ArrayPathMap(oscPathBit, iisuPath, parent) {}

	// Visitor.
	void accept(TypedPathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

} // namespace SK.