#pragma once

#include <vector>
#include <string>

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \brief This maintains the type-agnostic mapping between the iisu data path and its OSC counterpart.
///
/// See class TypedPathMap for the typed version of it. Also note that PathMap maintains the path
/// hierarchy and thus it does not store the full OSC paths but only the bit corresponding to itself.
/// This is unlike TypedPathMap which keeps the full OSC path.
class PathMap
{
public:
	PathMap(const std::string& oscPathBit, const std::string& iisuPath, PathMap* parent = 0);
	virtual ~PathMap();

	/// \name Accessors.
	//@{
	const std::string& getOscPathBit() const {return m_oscPathBit;}
	void setOscPathBit(const std::string& oscPathBit) {m_oscPathBit = oscPathBit;}

	const std::string& getIisuPath() const {return m_iisuPath;}
	void setIisuPath(const std::string& iisuPath) {m_iisuPath = iisuPath;}

	PathMap* getParent() const {return m_parent;}

	std::vector<PathMap*> getChildren() const {return m_children;}
	//@}

	/// \name API.
	//@{
	PathMap* addPathMap(const std::string& oscPathBit, const std::string& iisuPath);
	PathMap* insertPathMap(const std::string& oscPathBit, const std::string& iisuPath);
	PathMap* addChildMap(const std::string& oscPathBit, const std::string& iisuPath) {return new PathMap(oscPathBit, iisuPath, this);}
	//@}

protected:

	// Map.
	std::string m_oscPathBit;
	std::string m_iisuPath;

	// Handle hierarchy tree of PathMaps.
	PathMap* m_parent;
	std::vector<PathMap*> m_children;

	// Helpers.
	bool unParent(PathMap* child);
};

} // namespace SK.