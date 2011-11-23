#include "MvdPathDelegate.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
MvdPathDelegate::MvdPathDelegate(QObject *parent) :
	QItemDelegate(parent)
{
}

//////////////////////////////////////////////////////////////////////////
QWidget* MvdPathDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const
{
	QSpinBox *editor = new QSpinBox(parent);
	editor->setMinimum(0);
	editor->setMaximum(100);

	return editor;
}

//////////////////////////////////////////////////////////////////////////
void MvdPathDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	int value = index.model()->data(index, Qt::EditRole).toInt();

	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	spinBox->setValue(value);
}

//////////////////////////////////////////////////////////////////////////
void MvdPathDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	spinBox->interpretText();
	int value = spinBox->value();

	model->setData(index, value, Qt::EditRole);
}

//////////////////////////////////////////////////////////////////////////
void MvdPathDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& /*index*/) const
{
	editor->setGeometry(option.rect);
}

} // namespace SK.