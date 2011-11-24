#include "MvdPathDelegate.h"

namespace SK
{

int MvdPathDelegate::sm_iisuPathColumnIdx = 1;

//////////////////////////////////////////////////////////////////////////
MvdPathDelegate::MvdPathDelegate(QObject *parent) :
	QItemDelegate(parent)
{
}

//////////////////////////////////////////////////////////////////////////
QWidget* MvdPathDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() == sm_iisuPathColumnIdx)
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

	return QItemDelegate::createEditor(parent, option, index);
}

//////////////////////////////////////////////////////////////////////////
void MvdPathDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (index.column() == sm_iisuPathColumnIdx)
	{
		QString val = index.model()->data(index, Qt::EditRole).toString();

		QComboBox *comboBox = static_cast<QComboBox*>(editor);
		int currentIdx = comboBox->findText(val, Qt::MatchExactly);
		if (currentIdx != -1)
			comboBox->setCurrentIndex(currentIdx);

		return;
	}

	QItemDelegate::setEditorData(editor, index);
}

//////////////////////////////////////////////////////////////////////////
void MvdPathDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	if (index.column() == sm_iisuPathColumnIdx)
	{
		QComboBox *comboBox = static_cast<QComboBox*>(editor);
		QString val = comboBox->currentText();

		model->setData(index, val, Qt::EditRole);

		return;
	}

	QItemDelegate::setModelData(editor, model, index);
}

//////////////////////////////////////////////////////////////////////////
void MvdPathDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() == sm_iisuPathColumnIdx)
	{
		editor->setGeometry(option.rect);

		return;
	}

	QItemDelegate::updateEditorGeometry(editor, option, index);
}

} // namespace SK.