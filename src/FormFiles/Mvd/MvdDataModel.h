#pragma once

#include <QtGui>
#include <QStandardItemModel>
#include <Platform/SkPlatform.h>
#include "DataBase/DataObjects/TypedPathMapVisitor.h"

class QStandardItem;

Q_DECLARE_METATYPE(SK::TypedPathMap*);
Q_DECLARE_METATYPE(SK::DataTypedPathMap*);

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \brief This class is the model in the MVD / MVC pattern.
class MvdDataModel : public QStandardItemModel, public TypedPathMapVisitor
{
	Q_OBJECT

public:

	enum CustomRolesEnum
	{
		RoleIndexRole = Qt::UserRole,
		PathMapRole,
		DataPathMapRole,

		CustomRolesNum
	};

	MvdDataModel(QObject *parent = 0);

	void update();

	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

protected:

	/// \name Visitor's methods.
	//@{
	void visit(TypedPathMap* typedPathMap) SK_OVERRIDE;
	void visit(DataTypedPathMap* typedPathMap) SK_OVERRIDE;
	void visit(BooleanPathMap* typedPathMap) SK_OVERRIDE {visit((DataTypedPathMap*)typedPathMap);}
	void visit(IntegerPathMap* typedPathMap) SK_OVERRIDE {visit((DataTypedPathMap*)typedPathMap);}
	void visit(Vector3PathMap* typedPathMap) SK_OVERRIDE {visit((DataTypedPathMap*)typedPathMap);}
	void visit(ArrayPathMap* typedPathMap) SK_OVERRIDE {visit((DataTypedPathMap*)typedPathMap);}
	void visit(FloatArrayPathMap* typedPathMap) SK_OVERRIDE {visit((DataTypedPathMap*)typedPathMap);}
	void visit(Vector3ArrayPathMap* typedPathMap) SK_OVERRIDE {visit((DataTypedPathMap*)typedPathMap);}
	//@}

	QStandardItem* m_parentItem;
};

} // namespace SK.