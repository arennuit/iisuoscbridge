#include "MvdDataModel.h"

#include "assert.h"

#include <QStandardItem>
#include <QVariant>
#include <QString>
#include "DataBase//PathMapItem.h"
#include "DataBase/DataBase.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
MvdDataModel::MvdDataModel(QObject *parent) :
	QStandardItemModel(parent),
	PathMapItemVisitor(),
	m_parentItem(0)
{

}

//////////////////////////////////////////////////////////////////////////
void MvdDataModel::update()
{
	clear();

	// Describe all data objects and their properties.
	setHorizontalHeaderLabels(QStringList() << "OSC hierarchy" << "iisu path" << "Fold and name joints");

	// Parse the path associations.
	DataBase::GetInstance()->getPathsTreeRoot()->accept(this);
}

//////////////////////////////////////////////////////////////////////////
void MvdDataModel::visit(PathMapItem* pathItem)
{
	assert(pathItem);

	// Row.
	QStandardItem* oscItem = new QStandardItem(pathItem->m_oscPathItem.c_str());
	if (!m_parentItem)
	{
		setItem(0, 0, oscItem);
	}
	else
		m_parentItem->appendRow(QList<QStandardItem*>() << oscItem);

	// Recursive call to children.
	for (uint i = 0; i < pathItem->m_children.size(); ++i)
	{
		m_parentItem = oscItem;
		pathItem->m_children[i]->accept(this);
	}
}

//////////////////////////////////////////////////////////////////////////
void MvdDataModel::visit(DataPathMapItem* pathItem)
{
	assert(pathItem);

	// TODO: quand je saurai ajouter un item � droite d'un item existant je pourrais appeler l'overload
	//       de visit() sur PathMapItem et compl�ter par un itel � droite de oscItem pour iisuItem,
	//       � la place de r��crire tout le code.

	// Row.
	QStandardItem* oscItem = new QStandardItem(pathItem->m_oscPathItem.c_str());
	QStandardItem* iisuItem = new QStandardItem(pathItem->m_iisuPath.c_str());
	if (!m_parentItem)
	{
		setItem(0, 0, oscItem);
		setItem(0, 1, iisuItem);
	}
	else
		m_parentItem->appendRow(QList<QStandardItem*>() << oscItem << iisuItem);

	// Recursive call to children.
	for (uint i = 0; i < pathItem->m_children.size(); ++i)
	{
		m_parentItem = oscItem;
		pathItem->m_children[i]->accept(this);
	}
}

//////////////////////////////////////////////////////////////////////////
void MvdDataModel::visit(FoldableDataPathMapItem* pathItem)
{
	assert(pathItem);

	// TODO: quand je saurai ajouter un item � droite d'un item existant je pourrais appeler l'overload
	//       de visit() sur PathMapItem et compl�ter par un itel � droite de oscItem pour iisuItem,
	//       � la place de r��crire tout le code.

	// Row.
	QStandardItem* oscPathItem = new QStandardItem(pathItem->m_oscPathItem.c_str());

	QStandardItem* iisuPathItem = new QStandardItem(pathItem->m_iisuPath.c_str());

	QStandardItem* unFoldedModeItem = new QStandardItem();
	unFoldedModeItem->setCheckable(true);
	pathItem->m_isFoldAndNameMode ? unFoldedModeItem->setCheckState(Qt::Checked) : unFoldedModeItem->setCheckState(Qt::Unchecked);	

	if (!m_parentItem)
	{
		setItem(0, 0, oscPathItem);
		setItem(0, 1, iisuPathItem);
		setItem(0, 2, unFoldedModeItem);
	}
	else
		m_parentItem->appendRow(QList<QStandardItem*>() << oscPathItem << iisuPathItem << 0 << unFoldedModeItem);

	// Recursive call to children.
	for (uint i = 0; i < pathItem->m_children.size(); ++i)
	{
		m_parentItem = oscPathItem;
		pathItem->m_children[i]->accept(this);
	}
}

//////////////////////////////////////////////////////////////////////////
void MvdDataModel::visit(ArrayPathMapItem* pathItem)
{
	assert(pathItem);

	// TODO: quand je saurai ajouter un item � droite d'un item existant je pourrais appeler l'overload
	//       de visit() sur PathMapItem et compl�ter par un itel � droite de oscItem pour iisuItem,
	//       � la place de r��crire tout le code.

	// Row.
	QStandardItem* oscPathItem = new QStandardItem(pathItem->m_oscPathItem.c_str());

	QStandardItem* iisuPathItem = new QStandardItem(pathItem->m_iisuPath.c_str());

	QStandardItem* unFoldedModeItem = new QStandardItem();
	unFoldedModeItem->setCheckable(true);
	pathItem->m_isFoldAndNameMode ? unFoldedModeItem->setCheckState(Qt::Checked) : unFoldedModeItem->setCheckState(Qt::Unchecked);	

	if (!m_parentItem)
	{
		setItem(0, 0, oscPathItem);
		setItem(0, 1, iisuPathItem);
		setItem(0, 2, unFoldedModeItem);
	}
	else
		m_parentItem->appendRow(QList<QStandardItem*>() << oscPathItem << iisuPathItem << unFoldedModeItem);

	// Recursive call to children.
	for (uint i = 0; i < pathItem->m_children.size(); ++i)
	{
		m_parentItem = oscPathItem;
		pathItem->m_children[i]->accept(this);
	}
}

} // namespace SK.