#pragma once

namespace SK
{

class PathAssociation;
class BooleanPathAssociation;
class Vector3ArrayPathAssociation;
class FloatArrayPathAssociation;

//////////////////////////////////////////////////////////////////////////
class PathAssociationVisitor
{
public:
	virtual void visit(PathAssociation* pathAssociation) = 0;
	virtual void visit(BooleanPathAssociation* pathAssociation) = 0;
	virtual void visit(Vector3ArrayPathAssociation* pathAssociation) = 0;
	virtual void visit(FloatArrayPathAssociation* pathAssociation) = 0;
};

} // namespace SK.