#pragma once

namespace SK
{

class PathMapItem;
class DataPathMapItem;
class BooleanPathMapItem;
class Vector3ArrayPathMapItem;
class FloatArrayPathMapItem;

//////////////////////////////////////////////////////////////////////////
class PathMapItemVisitor
{
public:
	/// \name Visitor's methods.
	//@{
	virtual void visit(PathMapItem* pathItem) = 0;
	virtual void visit(DataPathMapItem* pathItem) = 0;
	virtual void visit(BooleanPathMapItem* pathItem) = 0;
	virtual void visit(Vector3ArrayPathMapItem* pathItem) = 0;
	virtual void visit(FloatArrayPathMapItem* pathItem) = 0;
	//@}
};

} // namespace SK.