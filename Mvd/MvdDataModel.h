#pragma once

#include <QtGui>
#include <QStandardItemModel>
#include <Platform/SkPlatform.h>
#include "DataBase/PathMapItemVisitor.h"

class QStandardItem;

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \name This class is the model in the MVD / MVC pattern.
class MvdDataModel : public QStandardItemModel, public PathMapItemVisitor
{
	Q_OBJECT

public:
	MvdDataModel(QObject *parent = 0);

	void update();

protected:
	void visit(PathMapItem* pathItem) SK_OVERRIDE;
	void visit(DataPathMapItem* pathItem) SK_OVERRIDE;
	void visit(BooleanPathMapItem* pathItem) SK_OVERRIDE {visit((DataPathMapItem*)pathItem);}
	void visit(Vector3ArrayPathMapItem* pathItem) SK_OVERRIDE {visit((DataPathMapItem*)pathItem);}
	void visit(FloatArrayPathMapItem* pathItem) SK_OVERRIDE {visit((DataPathMapItem*)pathItem);}

	QStandardItem* m_parentItem;
};

} // namespace SK.