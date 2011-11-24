#pragma once

namespace SK
{

class PathMap;
class DataPathMap;
class BooleanPathMap;
class IntegerPathMap;
class Vector3PathMap;
class ArrayPathMap;
class FloatArrayPathMap;
class Vector3ArrayPathMap;

//////////////////////////////////////////////////////////////////////////
class PathMapVisitor
{
public:
	/// \name Visitor's methods.
	//@{
	virtual void visit(PathMap* pathMap) = 0;
	virtual void visit(DataPathMap* pathMap) = 0;
	virtual void visit(BooleanPathMap* pathMap) = 0;
	virtual void visit(IntegerPathMap* pathMap) = 0;
	virtual void visit(Vector3PathMap* pathMap) = 0;
	virtual void visit(ArrayPathMap* pathMap) = 0;
	virtual void visit(FloatArrayPathMap* pathMap) = 0;
	virtual void visit(Vector3ArrayPathMap* pathMap) = 0;
	//@}
};

} // namespace SK.