#pragma once

#include <QtGui>
#include <QStandardItemModel>
#include <Platform/SkPlatform.h>
#include "DataBase/PathMapVisitor.h"

class QStandardItem;

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \brief This class is the model in the MVD / MVC pattern.
class MvdDataModel : public QStandardItemModel, public PathMapVisitor
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
	void visit(PathMap* pathMap) SK_OVERRIDE;
	void visit(DataPathMap* pathMap) SK_OVERRIDE;
	void visit(BooleanPathMap* pathMap) SK_OVERRIDE {visit((DataPathMap*)pathMap);}
	void visit(IntegerPathMap* pathMap) SK_OVERRIDE {visit((DataPathMap*)pathMap);}
	void visit(Vector3PathMap* pathMap) SK_OVERRIDE {visit((DataPathMap*)pathMap);}
	void visit(ArrayPathMap* pathMap) SK_OVERRIDE {visit((DataPathMap*)pathMap);}
	void visit(FloatArrayPathMap* pathMap) SK_OVERRIDE {visit((DataPathMap*)pathMap);}
	void visit(Vector3ArrayPathMap* pathMap) SK_OVERRIDE {visit((DataPathMap*)pathMap);}
	//@}

	QStandardItem* m_parentItem;
};

} // namespace SK.