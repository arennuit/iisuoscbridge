#pragma once

#include <vector>
#include <string>

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
};

//////////////////////////////////////////////////////////////////////////
class Vector3ArrayPathAssociation : public PathAssociation
{
public:
	Vector3ArrayPathAssociation(const std::string& oscPathItem, PathAssociation* parent = 0, const std::string& iisuPath = std::string()) :
		PathAssociation(oscPathItem, parent, iisuPath) {}
};

} // namespace SK.