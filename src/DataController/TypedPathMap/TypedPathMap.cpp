#include "TypedPathMap.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
TypedPathMap::TypedPathMap(const std::string& oscPathBit, TypedPathMap* parent/* = 0*/) :
	m_oscPathBit(oscPathBit),
	m_parent(parent)
{
	if (m_parent)
		m_parent->m_children.push_back(this);
}

//////////////////////////////////////////////////////////////////////////
TypedPathMap::~TypedPathMap()
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
bool TypedPathMap::unParent(TypedPathMap* child)
{
	// Look for 'child' in the array of children.
	for (std::vector<TypedPathMap*>::iterator childIt = m_children.begin(); childIt != m_children.end(); ++childIt)
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