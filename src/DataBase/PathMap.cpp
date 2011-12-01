#include "PathMap.h"
#include <assert.h>

namespace SK
{

//////////////////////////////////////////////////////////////////////////
PathMap::PathMap(const std::string& oscPathBit, const std::string& iisuPath, PathMap* parent /*= 0*/) :
	m_oscPathBit(oscPathBit),
	m_iisuPath(iisuPath),
	m_parent(parent)
{
	if (m_parent)
		m_parent->m_children.push_back(this);
}

//////////////////////////////////////////////////////////////////////////
PathMap::~PathMap()
{
	// Recursive deletion of the children.
	for (unsigned int i = 0; i < m_children.size(); ++i)
	{
		if (!m_children[i])
			continue;

		delete m_children[i];
	}

	if (m_parent)
		m_parent->unParent(this);
}

//////////////////////////////////////////////////////////////////////////
PathMap* PathMap::addPathMap(const std::string& oscPathBit, const std::string& iisuPath)
{
	// Find the parent path map.
	PathMap* parentPathMap = this->m_parent;
	if (!parentPathMap)
		return 0;

	// Add a new child to parentPathMap.
	return new PathMap(oscPathBit, iisuPath, parentPathMap);
}

//////////////////////////////////////////////////////////////////////////
PathMap* PathMap::insertPathMap(const std::string& oscPathBit, const std::string& iisuPath)
{
	// Find the parent path map.
	PathMap* parentPathMap = this->m_parent;
	if (!parentPathMap)
		return 0;

	// Find siblingPathMap in the parent' siblings.
	std::vector<PathMap*>& children = parentPathMap->m_children;
	for (std::vector<PathMap*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		PathMap* child = *it;
		assert(child);

		if (child != this)
			continue;

		PathMap* newChild = new PathMap(oscPathBit, iisuPath, 0);
		children.insert(it, newChild);

		return newChild;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
bool PathMap::unParent(PathMap* child)
{
	// Look for 'child' in the array of children.
	for (std::vector<PathMap*>::iterator childIt = m_children.begin(); childIt != m_children.end(); ++childIt)
	{
		if (*childIt == child)
		{
			m_children.erase(childIt);

			return true;
		}
	}

	return false;
}

} // namespace SK.