#pragma once

#include <QtGui>
#include <QStandardItemModel>
#include <Platform/SkPlatform.h>
#include "DataBase/PathAssociationVisitor.h"

class QStandardItem;

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \name This class is the model in the MVD / MVC pattern.
class MvdDataModel : public QStandardItemModel, public PathAssociationVisitor
{
	Q_OBJECT

public:
	MvdDataModel(QObject *parent = 0);

	void update();

protected:
	void visit(PathAssociation* pathAssociation) SK_OVERRIDE;
	void visit(DataPathAssociation* pathAssociation) SK_OVERRIDE;
	void visit(BooleanPathAssociation* pathAssociation) SK_OVERRIDE {visit((DataPathAssociation*)pathAssociation);}
	void visit(Vector3ArrayPathAssociation* pathAssociation) SK_OVERRIDE {visit((DataPathAssociation*)pathAssociation);}
	void visit(FloatArrayPathAssociation* pathAssociation) SK_OVERRIDE {visit((DataPathAssociation*)pathAssociation);}

	QStandardItem* m_parentItem;
};

} // namespace SK.