#pragma once

#include <vector>
#include <string>

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \brief This maintains the type-agnostic mapping between the iisu data path and its OSC counterpart.
/// See class TypedPathMap for the typed version of it. Also note that PathMap maintains the path
/// hierarchy and thus it does not store the full OSC paths but only the bit corresponding to itself.
/// This is unlike TypedPathMap which keeps the full OSC path.
class PathMap
{
public:
	PathMap(const std::string& oscPathBit, const std::string& iisuPath = "", PathMap* parent = 0);
	virtual ~PathMap();

	// Map.
	std::string m_oscPathBit;
	std::string m_iisuPath;

	// Handle hierarchy tree of PathMaps.
	PathMap* m_parent;
	std::vector<PathMap*> m_children;
};

} // namespace SK.