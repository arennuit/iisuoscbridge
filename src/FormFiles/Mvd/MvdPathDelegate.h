#pragma once

#include <QtGui>
#include <QItemDelegate>

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \brief This delegate displays a combo box in order to select iisu data paths.
class MvdPathDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	MvdPathDelegate(QObject *parent = 0);

	QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

protected:
	static int sm_iisuPathColumnIdx;
};

} // namespace SK.

