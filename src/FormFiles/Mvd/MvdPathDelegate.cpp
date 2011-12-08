#include "MvdPathDelegate.h"
#include "DataController/DataController.h"

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
	if (index.column() != sm_iisuPathColumnIdx)
		return QItemDelegate::createEditor(parent, option, index);

	// Create a combo box delegate.
	DataController* dataController = DataController::GetInstance();
	assert(dataController);

	QComboBox *comboBox = new QComboBox(parent);

	comboBox->setInsertPolicy(QComboBox::NoInsert);
	comboBox->setEditable(true);
	comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

	// Populate combo box items.
	std::vector<std::string> iisuDataPaths;
	dataController->retrieveIisuDataPaths(iisuDataPaths);

	comboBox->addItem("");
	for (uint i = 0; i < iisuDataPaths.size(); ++i)
		comboBox->addItem(iisuDataPaths[i].c_str());

	return comboBox;
}

//////////////////////////////////////////////////////////////////////////
void MvdPathDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (index.column() != sm_iisuPathColumnIdx)
		return QItemDelegate::setEditorData(editor, index);

	// Set combo box's text.
	QString val = index.model()->data(index, Qt::EditRole).toString();

	QComboBox *comboBox = static_cast<QComboBox*>(editor);
	int currentIdx = comboBox->findText(val, Qt::MatchExactly);
	if (currentIdx != -1)
		comboBox->setCurrentIndex(currentIdx);
}

//////////////////////////////////////////////////////////////////////////
void MvdPathDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	if (index.column() != sm_iisuPathColumnIdx)
		return QItemDelegate::setModelData(editor, model, index);

	// Update model.
	QComboBox *comboBox = static_cast<QComboBox*>(editor);
	QString val = comboBox->currentText();

	model->setData(index, val, Qt::EditRole);
}

//////////////////////////////////////////////////////////////////////////
void MvdPathDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.column() != sm_iisuPathColumnIdx)
		return QItemDelegate::updateEditorGeometry(editor, option, index);

	// Update edito's geometry.
	editor->setGeometry(option.rect);
}

} // namespace SK.