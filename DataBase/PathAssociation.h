#pragma once

#include <vector>
#include <string>
#include "PathAssociationVisitor.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
class PathAssociation
{
public:
	PathAssociation(const std::string& oscPathItem, PathAssociation* parent = 0, const std::string& iisuPath = std::string());

	std::string m_oscPathItem;
	std::string m_iisuPath;

	PathAssociation* m_parent;
	std::vector<PathAssociation*> m_children;

	virtual void accept(PathAssociationVisitor* visitor) {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class BooleanPathAssociation : public PathAssociation
{
public:
	BooleanPathAssociation(const std::string& oscPathItem, PathAssociation* parent = 0, const std::string& iisuPath = std::string()) :
		PathAssociation(oscPathItem, parent, iisuPath) {}

		void accept(PathAssociationVisitor* visitor) override {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class Vector3ArrayPathAssociation : public PathAssociation
{
public:
	Vector3ArrayPathAssociation(const std::string& oscPathItem, PathAssociation* parent = 0, const std::string& iisuPath = std::string()) :
	  PathAssociation(oscPathItem, parent, iisuPath) {}

	  void accept(PathAssociationVisitor* visitor) override {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class FloatArrayPathAssociation : public PathAssociation
{
public:
	FloatArrayPathAssociation(const std::string& oscPathItem, PathAssociation* parent = 0, const std::string& iisuPath = std::string()) :
	  PathAssociation(oscPathItem, parent, iisuPath) {}

	  void accept(PathAssociationVisitor* visitor) override {visitor->visit(this);}
};

} // namespace SK.