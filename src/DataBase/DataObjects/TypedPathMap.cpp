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
}

} // namespace SK.