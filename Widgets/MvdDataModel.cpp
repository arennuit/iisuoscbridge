#include "MvdDataModel.h"

#include "assert.h"

#include <QStandardItem>
#include <QVariant>
#include <QString>
#include "DataBase//PathAssociation.h"
#include "DataBase/DataBase.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
MvdDataModel::MvdDataModel(QObject *parent) :
	QStandardItemModel(parent),
	PathAssociationVisitor(),
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
void MvdDataModel::visit(PathAssociation* pathAssociation)
{
	assert(pathAssociation);

	// Row.
	QStandardItem* oscItem = new QStandardItem(pathAssociation->m_oscPathItem.c_str());
	QStandardItem* iisuItem = new QStandardItem(pathAssociation->m_iisuPath.c_str());
	if (!m_parentItem)
	{
		setItem(0, 0, oscItem);
		setItem(0, 1, iisuItem);
	}
	else
		m_parentItem->appendRow(QList<QStandardItem*>() << oscItem << iisuItem);

	// Recursive call to children.
	for (uint i = 0; i < pathAssociation->m_children.size(); ++i)
	{
		m_parentItem = oscItem;
		pathAssociation->m_children[i]->accept(this);
	}
}

} // namespace SK.