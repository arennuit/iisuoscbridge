#pragma once

#include <QtGui>
#include <QStandardItemModel>

class QStandardItem;

namespace SK
{

//////////////////////////////////////////////////////////////////////////
class DataQtModel : public QStandardItemModel
{
	Q_OBJECT

public:
	DataQtModel(QObject *parent = 0);

	bool setData(const QModelIndex& index, const QVariant& value, int role);

	void update();

protected:

	enum CustomRolesEnum
	{
		RoleIndexRole = Qt::UserRole,
		ObjectNameRole,
		FrameQwValueRole,

		CustomRolesNum
	};

	QStandardItem* m_objectNameItem;
};

} // namespace SK.