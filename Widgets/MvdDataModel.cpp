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

	//QStandardItem* item00 = new QStandardItem("00");
	//setItem(0, 0, item00);

	//QStandardItem* item01 = new QStandardItem("01");
	//setItem(0, 1, item01);

	//QStandardItem* item10 = new QStandardItem("10");
	//setItem(1,0, item10);

	//QStandardItem* item11 = new QStandardItem("11");
	//setItem(1, 1, item11);

	//QStandardItem* sub_0_00 = new QStandardItem("sub0_00");
	//QStandardItem* sub_0_01 = new QStandardItem("sub0_01");
	//QStandardItem* sub_0_10 = new QStandardItem("sub0_10");
	//QStandardItem* sub_0_11 = new QStandardItem("sub0_11");
	//item00->appendRow(QList<QStandardItem*>() << sub_0_00 << sub_0_01);
	//item00->appendRow(QList<QStandardItem*>() << sub_0_10 << sub_0_11);

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