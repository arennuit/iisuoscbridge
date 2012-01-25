#pragma once

namespace SK
{

class TypedPathMap;
class DataTypedPathMap;
class BoolPathMap;
class Int32PathMap;
class Vector3PathMap;
class ArrayPathMap;
class FloatArrayPathMap;
class Vector3ArrayPathMap;

//////////////////////////////////////////////////////////////////////////
class TypedPathMapVisitor
{
public:
	/// \name Visitor's methods.
	//@{
	virtual void visit(TypedPathMap* typedPathMap) = 0;
	virtual void visit(DataTypedPathMap* typedPathMap) = 0;
	virtual void visit(BoolPathMap* typedPathMap) = 0;
	virtual void visit(Int32PathMap* typedPathMap) = 0;
	virtual void visit(Vector3PathMap* typedPathMap) = 0;
	virtual void visit(ArrayPathMap* typedPathMap) = 0;
	virtual void visit(FloatArrayPathMap* typedPathMap) = 0;
	virtual void visit(Vector3ArrayPathMap* typedPathMap) = 0;
	//@}
};

} // namespace SK.