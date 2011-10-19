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
	setHorizontalHeaderLabels(QStringList() << "OSC hierarchy" << "iisu path");

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

	// TODO: quand je saurai ajouter un item à droite d'un item existant je pourrais appeler l'overload
	//       de visit() sur PathMapItem et compléter par un itel à droite de oscItem pour iisuItem,
	//       à la place de réécrire tout le code.

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

} // namespace SK.