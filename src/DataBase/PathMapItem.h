#pragma once

#include <vector>
#include <string>
#include "Platform/SkPlatform.h"
#include "PathMapItemVisitor.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \brief The concrete PathMapItem class is used to format OSC paths. But the class is also inherited
///       by items actually pointing to proper iisu data.
class PathMapItem
{
public:
	PathMapItem(const std::string& oscPathItem, PathMapItem* parent = 0);
	virtual ~PathMapItem();

	// Map.
	std::string m_oscPathItem;

	// Handle hierarchy tree of PathMapItems.
	PathMapItem* m_parent;
	std::vector<PathMapItem*> m_children;

	// Visitor.
	virtual void accept(PathMapItemVisitor* visitor) {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class DataPathMapItem : public PathMapItem
{
public:
	DataPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0) :
		PathMapItem(oscPathItem, parent),
		m_iisuPath(iisuPath) {}

	// Map.
	std::string m_iisuPath;

	// Visitor.
	void accept(PathMapItemVisitor* visitor) SK_OVERRIDE = 0;
};

//////////////////////////////////////////////////////////////////////////
class BooleanPathMapItem : public DataPathMapItem
{
public:
	BooleanPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0) :
		DataPathMapItem(oscPathItem, iisuPath, parent) {}

	// Visitor.
	void accept(PathMapItemVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector3PathMapItem : public DataPathMapItem
{
public:
	Vector3PathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0) :
		DataPathMapItem(oscPathItem, iisuPath, parent) {}

	// Visitor.
	void accept(PathMapItemVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class ArrayPathMapItem : public DataPathMapItem
{
public:
	ArrayPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0) :
		DataPathMapItem(oscPathItem, iisuPath, parent) {}

	// Visitor.
	void accept(PathMapItemVisitor* visitor) = 0;
};

//////////////////////////////////////////////////////////////////////////
class FloatArrayPathMapItem : public ArrayPathMapItem
{
public:
	FloatArrayPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0) :
		ArrayPathMapItem(oscPathItem, iisuPath, parent) {}

	// Visitor.
	void accept(PathMapItemVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector3ArrayPathMapItem : public ArrayPathMapItem
{
public:
	Vector3ArrayPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0) :
		ArrayPathMapItem(oscPathItem, iisuPath, parent) {}

	// Visitor.
	void accept(PathMapItemVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

} // namespace SK.