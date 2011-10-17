#include "PathAssociation.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
PathAssociation::PathAssociation(const std::string& oscPathItem, PathAssociation* parent/* = 0*/, const std::string& iisuPath/* = std::string()*/) :
	m_oscPathItem(oscPathItem),
	m_parent(parent),
	m_iisuPath(iisuPath)
{
	if (m_parent)
		m_parent->m_children.push_back(this);
}

//////////////////////////////////////////////////////////////////////////
PathAssociation::~PathAssociation()
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