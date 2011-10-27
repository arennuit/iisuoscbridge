#pragma once

#include <vector>
#include <string>
#include <Platform/SkPlatform.h>
#include "PathMapItemVisitor.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \note The concrete PathMapItem class is used to format OSC paths. But the class is also inherited
///       by items actually pointing to proper iisu data.
class PathMapItem
{
public:
	PathMapItem(const std::string& oscPathItem, PathMapItem* parent = 0);
	virtual ~PathMapItem();

	std::string m_oscPathItem;

	// Handle hierarchy tree of PathMapItems.
	PathMapItem* m_parent;
	std::vector<PathMapItem*> m_children;

	virtual void accept(PathMapItemVisitor* visitor) {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class DataPathMapItem : public PathMapItem
{
public:
	DataPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0) :
		PathMapItem(oscPathItem, parent),
		m_iisuPath(iisuPath) {}

	std::string m_iisuPath;

	void accept(PathMapItemVisitor* visitor) SK_OVERRIDE = 0;
};

//////////////////////////////////////////////////////////////////////////
class BooleanPathMapItem : public DataPathMapItem
{
public:
	BooleanPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0) :
		DataPathMapItem(oscPathItem, iisuPath, parent) {}

	void accept(PathMapItemVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class ArrayPathMapItem : public DataPathMapItem
{
public:
	ArrayPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0, bool areJointsNamed = true) :
		DataPathMapItem(oscPathItem, iisuPath, parent),
		m_areJointsNamed(areJointsNamed) {}

	// Streaming mode.
	bool m_areJointsNamed;

	void accept(PathMapItemVisitor* visitor) = 0;
};

//////////////////////////////////////////////////////////////////////////
class Vector3ArrayPathMapItem : public ArrayPathMapItem
{
public:
	Vector3ArrayPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0, bool areJointsNamed = true) :
		ArrayPathMapItem(oscPathItem, iisuPath, parent, areJointsNamed) {}

	void accept(PathMapItemVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class FloatArrayPathMapItem : public ArrayPathMapItem
{
public:
	FloatArrayPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0, bool areJointsNamed = true) :
		ArrayPathMapItem(oscPathItem, iisuPath, parent, areJointsNamed) {}

	void accept(PathMapItemVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

} // namespace SK.