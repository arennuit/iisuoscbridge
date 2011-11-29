#include "PathMap.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
PathMap::PathMap(const std::string& oscPathBit, const std::string& iisuPath /*= ""*/, PathMap* parent /*= 0*/) :
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