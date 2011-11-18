#pragma once

#include <QtGui>
#include <QStandardItemModel>
#include <Platform/SkPlatform.h>
#include "DataBase/PathMapItemVisitor.h"

class QStandardItem;

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \brief This class is the model in the MVD / MVC pattern.
class MvdDataModel : public QStandardItemModel, public PathMapItemVisitor
{
	Q_OBJECT

public:
	MvdDataModel(QObject *parent = 0);

	void update();

	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

protected:

	enum CustomRolesEnum
	{
		RoleIndexRole = Qt::UserRole,
		PathMapRole,
		DataPathMapRole,

		CustomRolesNum
	};

	/// \name Visitor's methods.
	//@{
	void visit(PathMapItem* pathItem) SK_OVERRIDE;
	void visit(DataPathMapItem* pathItem) SK_OVERRIDE;
	void visit(BooleanPathMapItem* pathItem) SK_OVERRIDE {visit((DataPathMapItem*)pathItem);}
	void visit(Vector3PathMapItem* pathItem) SK_OVERRIDE {visit((DataPathMapItem*)pathItem);}
	void visit(ArrayPathMapItem* pathItem) SK_OVERRIDE {visit((DataPathMapItem*)pathItem);}
	void visit(FloatArrayPathMapItem* pathItem) SK_OVERRIDE {visit((DataPathMapItem*)pathItem);}
	void visit(Vector3ArrayPathMapItem* pathItem) SK_OVERRIDE {visit((DataPathMapItem*)pathItem);}
	//@}

	QStandardItem* m_parentItem;
};

} // namespace SK.