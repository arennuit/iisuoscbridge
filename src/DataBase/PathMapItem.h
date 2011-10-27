#pragma once

#include <vector>
#include <string>
#include <Platform/SkPlatform.h>
#include "PathMapItemVisitor.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
class PathMapItem
{
public:
	PathMapItem(const std::string& oscPathItem, PathMapItem* parent = 0);
	virtual ~PathMapItem();

	std::string m_oscPathItem;

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
class Vector3ArrayPathMapItem : public DataPathMapItem
{
public:
	Vector3ArrayPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0) :
		DataPathMapItem(oscPathItem, iisuPath, parent) {}

	void accept(PathMapItemVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class FloatArrayPathMapItem : public DataPathMapItem
{
public:
	FloatArrayPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0) :
		DataPathMapItem(oscPathItem, iisuPath, parent) {}

	void accept(PathMapItemVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

} // namespace SK.