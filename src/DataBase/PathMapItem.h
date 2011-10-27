#pragma once

#include <vector>
#include <string>
#include <Platform/SkPlatform.h>
#include "PathMapItemVisitor.h"

namespace SK
{

enum ArrayStreamingModeEnum
{
	INDEX_AND_FOLD,
	INDEX_AND_UNFOLD,
	NAME_AND_FOLD,
	NAME_AND_UNFOLD,

	ARRAY_STREAMING_MODES_NUM
};

static const std::string ArrayStreamingModeLabels[ARRAY_STREAMING_MODES_NUM] = 
{
	"Index and Fold",
	"Index and UnFold",
	"Name and Fold",
	"Name and UnFold"
};

//////////////////////////////////////////////////////////////////////////
/// \note The concrete PathMapItem class is used to format OSC paths. But the class is also inherited
///       by items actually pointing to proper iisu data.
class PathMapItem
{
public:
	PathMapItem(const std::string& oscPathItem, PathMapItem* parent = 0);
	virtual ~PathMapItem();

	std::string m_oscPathItem;

	PathMapItem* m_parent;
	std::vector<PathMapItem*> m_children;

	virtual void accept(PathMapItemVisitor* visitor) {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class DataPathMapItem : public PathMapItem
{
public:
	DataPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0) :
		PathMapItem(oscPathItem, parent),
		m_iisuPath(iisuPath) {}

	std::string m_iisuPath;

	void accept(PathMapItemVisitor* visitor) SK_OVERRIDE = 0;
};

//////////////////////////////////////////////////////////////////////////
class BooleanPathMapItem : public DataPathMapItem
{
public:
	BooleanPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0) :
		DataPathMapItem(oscPathItem, iisuPath, parent) {}

	void accept(PathMapItemVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class ArrayPathMapItem : public DataPathMapItem
{
public:
	ArrayPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0, ArrayStreamingModeEnum streamingMode = NAME_AND_FOLD) :
		DataPathMapItem(oscPathItem, iisuPath, parent),
		m_streamingMode(streamingMode) {}

	ArrayStreamingModeEnum m_streamingMode;

	void accept(PathMapItemVisitor* visitor) = 0;
};

//////////////////////////////////////////////////////////////////////////
class Vector3ArrayPathMapItem : public ArrayPathMapItem
{
public:
	Vector3ArrayPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0, ArrayStreamingModeEnum streamingMode = NAME_AND_FOLD) :
		ArrayPathMapItem(oscPathItem, iisuPath, parent, streamingMode) {}

	void accept(PathMapItemVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

//////////////////////////////////////////////////////////////////////////
class FloatArrayPathMapItem : public ArrayPathMapItem
{
public:
	FloatArrayPathMapItem(const std::string& oscPathItem, const std::string& iisuPath, PathMapItem* parent = 0, ArrayStreamingModeEnum streamingMode = NAME_AND_FOLD) :
		ArrayPathMapItem(oscPathItem, iisuPath, parent, streamingMode) {}

	void accept(PathMapItemVisitor* visitor) SK_OVERRIDE {visitor->visit(this);}
};

} // namespace SK.