#include "PathMapItem.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
PathMapItem::PathMapItem(const std::string& oscPathItem, PathMapItem* parent/* = 0*/) :
	m_oscPathItem(oscPathItem),
	m_parent(parent)
{
	if (m_parent)
		m_parent->m_children.push_back(this);
}

//////////////////////////////////////////////////////////////////////////
PathMapItem::~PathMapItem()
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