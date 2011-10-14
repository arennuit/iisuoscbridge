#pragma once

#include <QtGui>
#include <QStandardItemModel>
#include "DataBase/PathAssociationVisitor.h"

class QStandardItem;

namespace SK
{

//////////////////////////////////////////////////////////////////////////
class MvdDataModel : public QStandardItemModel, public PathAssociationVisitor
{
	Q_OBJECT

public:
	MvdDataModel(QObject *parent = 0);

	void update();

protected:
	void visit(PathAssociation* pathAssociation) override;
	void visit(BooleanPathAssociation* pathAssociation) override {visit((PathAssociation*)pathAssociation);}
	void visit(Vector3ArrayPathAssociation* pathAssociation) override {visit((PathAssociation*)pathAssociation);}
	void visit(FloatArrayPathAssociation* pathAssociation) override {visit((PathAssociation*)pathAssociation);}

	QStandardItem* m_parentItem;
};

} // namespace SK.