#pragma once

#include <vector>
#include <string>
#include "Platform/SkPlatform.h"
#include "PathMapVisitor.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \brief The concrete PathMap class is used to format OSC paths. But the class is also inherited
///       by items actually pointing to proper iisu data.
class PathMap
{
public:
	PathMap(const std::string& oscPathBit, PathMap* parent = 0);
	virtual ~PathMap();

	// Map.
	std::string m_oscPathBit;

	// Handle hierarchy tree of PathMaps.
	PathMap* m_parent;
	std::vector<PathMap*> m_children;

	// Visitor.
	virtual void accept(PathMapVisitor* visitor) {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class DataPathMap : public PathMap
{
public:
	DataPathMap(const std::string& oscPathBit, const std::string& iisuPath, PathMap* parent = 0) :
		PathMap(oscPathBit, parent),
		m_iisuPath(iisuPath) {}

	// Map.
	std::string m_iisuPath;

	// Visitor.
	void accept(PathMapVisitor* visitor) SK_OVERRIDE = 0;
};

//////////////////////////////////////////////////////////////////////////
class BooleanPathMap : public DataPathMap
{
public:
	BooleanPathMap(const std::string& oscPathBit, const std::string& iisuPath, PathMap* parent = 0) :
		DataPathMap(oscPathBit, iisuPath, parent) {}

	// Visitor.
	void accept(PathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class IntegerPathMap : public DataPathMap
{
public:
	IntegerPathMap(const std::string& oscPathBit, const std::string& iisuPath, PathMap* parent = 0) :
		DataPathMap(oscPathBit, iisuPath, parent) {}

	// Visitor.
	void accept(PathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector3PathMap : public DataPathMap
{
public:
	Vector3PathMap(const std::string& oscPathBit, const std::string& iisuPath, PathMap* parent = 0) :
		DataPathMap(oscPathBit, iisuPath, parent) {}

	// Visitor.
	void accept(PathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class ArrayPathMap : public DataPathMap
{
public:
	ArrayPathMap(const std::string& oscPathBit, const std::string& iisuPath, PathMap* parent = 0) :
		DataPathMap(oscPathBit, iisuPath, parent) {}

	// Visitor.
	void accept(PathMapVisitor* visitor) = 0;
};

//////////////////////////////////////////////////////////////////////////
class FloatArrayPathMap : public ArrayPathMap
{
public:
	FloatArrayPathMap(const std::string& oscPathBit, const std::string& iisuPath, PathMap* parent = 0) :
		ArrayPathMap(oscPathBit, iisuPath, parent) {}

	// Visitor.
	void accept(PathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector3ArrayPathMap : public ArrayPathMap
{
public:
	Vector3ArrayPathMap(const std::string& oscPathBit, const std::string& iisuPath, PathMap* parent = 0) :
		ArrayPathMap(oscPathBit, iisuPath, parent) {}

	// Visitor.
	void accept(PathMapVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

} // namespace SK.