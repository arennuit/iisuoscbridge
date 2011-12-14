#pragma once

#include <QtGui>
#include <QStandardItemModel>
#include <Platform/SkPlatform.h>

class QStandardItem;


namespace SK
{

class PathMap;

Q_DECLARE_METATYPE(const SK::PathMap*);
Q_DECLARE_METATYPE(SK::PathMap*);

//////////////////////////////////////////////////////////////////////////
/// \brief This class is the model in the MVD / MVC pattern.
class MvdDataModel : public QStandardItemModel
{
	Q_OBJECT

public:

	enum CustomRolesEnum
	{
		RoleIndexRole = Qt::UserRole,
		PathMapRole,

		CustomRolesNum
	};

	MvdDataModel(QObject *parent = 0);

	void cleanAndReBuildAll();

	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

protected:

	/// \name Helpers.
	//@{
	void cleanAndReBuild_pathMap(const PathMap* pathMap);
	//@}

	QStandardItem* m_parentItem;
};

} // namespace SK.