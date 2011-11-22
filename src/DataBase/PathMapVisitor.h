#pragma once

namespace SK
{

class PathMapItem;
class DataPathMapItem;
class BooleanPathMapItem;
class IntegerPathMapItem;
class Vector3PathMapItem;
class ArrayPathMapItem;
class FloatArrayPathMapItem;
class Vector3ArrayPathMapItem;

//////////////////////////////////////////////////////////////////////////
class PathMapItemVisitor
{
public:
	/// \name Visitor's methods.
	//@{
	virtual void visit(PathMapItem* pathItem) = 0;
	virtual void visit(DataPathMapItem* pathItem) = 0;
	virtual void visit(BooleanPathMapItem* pathItem) = 0;
	virtual void visit(IntegerPathMapItem* pathItem) = 0;
	virtual void visit(Vector3PathMapItem* pathItem) = 0;
	virtual void visit(ArrayPathMapItem* pathItem) = 0;
	virtual void visit(FloatArrayPathMapItem* pathItem) = 0;
	virtual void visit(Vector3ArrayPathMapItem* pathItem) = 0;
	//@}
};

} // namespace SK.