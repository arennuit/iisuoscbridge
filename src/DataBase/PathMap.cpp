#include "PathMap.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
PathMap::PathMap(const std::string& oscPathBit, PathMap* parent/* = 0*/) :
	m_oscPathBit(oscPathBit),
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
}

} // namespace SK.