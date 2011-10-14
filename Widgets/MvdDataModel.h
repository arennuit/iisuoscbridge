#pragma once

#include <QtGui>
#include <QStandardItemModel>

class QStandardItem;

namespace SK
{

//////////////////////////////////////////////////////////////////////////
class MvdDataModel : public QStandardItemModel
{
	Q_OBJECT

public:
	MvdDataModel(QObject *parent = 0);

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
};

} // namespace SK.