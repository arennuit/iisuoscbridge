#pragma once

#include <vector>
#include <string>
#include <Platform/SkPlatform.h>
#include "PathAssociationVisitor.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
class PathAssociation
{
public:
	PathAssociation(const std::string& oscPathItem, PathAssociation* parent = 0);
	virtual ~PathAssociation();

	std::string m_oscPathItem;

	PathAssociation* m_parent;
	std::vector<PathAssociation*> m_children;

	virtual void accept(PathAssociationVisitor* visitor) {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class DataPathAssociation : public PathAssociation
{
public:
	DataPathAssociation(const std::string& oscPathItem, const std::string& iisuPath, PathAssociation* parent = 0) :
		PathAssociation(oscPathItem, parent),
		m_iisuPath(iisuPath) {}

	std::string m_iisuPath;

	void accept(PathAssociationVisitor* visitor) SK_OVERRIDE = 0;
};

//////////////////////////////////////////////////////////////////////////
class BooleanPathAssociation : public DataPathAssociation
{
public:
	BooleanPathAssociation(const std::string& oscPathItem, const std::string& iisuPath, PathAssociation* parent = 0) :
		DataPathAssociation(oscPathItem, iisuPath, parent) {}

	void accept(PathAssociationVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector3ArrayPathAssociation : public DataPathAssociation
{
public:
	Vector3ArrayPathAssociation(const std::string& oscPathItem, const std::string& iisuPath, PathAssociation* parent = 0) :
		DataPathAssociation(oscPathItem, iisuPath, parent) {}

	void accept(PathAssociationVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class FloatArrayPathAssociation : public DataPathAssociation
{
public:
	FloatArrayPathAssociation(const std::string& oscPathItem, const std::string& iisuPath, PathAssociation* parent = 0) :
		DataPathAssociation(oscPathItem, iisuPath, parent) {}

	void accept(PathAssociationVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

} // namespace SK.