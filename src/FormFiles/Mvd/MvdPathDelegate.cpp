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
	QComboBox *comboBox = new QComboBox(parent);

	comboBox->setInsertPolicy(QComboBox::NoInsert);
	comboBox->setEditable(true);
	comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

	// TODO: populate the combox box correctly.
	comboBox->addItem("");
	comboBox->addItem("USER1.SKELETON.Status");
	comboBox->addItem("USER1.SKELETON.KeyPoints");
	comboBox->addItem("USER1.SKELETON.KeyPointsConfidence");

	return comboBox;
}

//////////////////////////////////////////////////////////////////////////
void MvdPathDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString val = index.model()->data(index, Qt::EditRole).toString();

	QComboBox *comboBox = static_cast<QComboBox*>(editor);
	int currentIdx = comboBox->findText(val, Qt::MatchExactly);
	if (currentIdx != -1)
		comboBox->setCurrentIndex(currentIdx);
}

//////////////////////////////////////////////////////////////////////////
void MvdPathDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	QComboBox *comboBox = static_cast<QComboBox*>(editor);
	QString val = comboBox->currentText();

	model->setData(index, val, Qt::EditRole);
}

//////////////////////////////////////////////////////////////////////////
void MvdPathDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& /*index*/) const
{
	editor->setGeometry(option.rect);
}

} // namespace SK.