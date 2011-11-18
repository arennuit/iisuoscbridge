#include "MvdDataModel.h"

#include "assert.h"

#include <QStandardItem>
#include <QVariant>
#include <QString>
#include "DataBase/PathMapItem.h"
#include "DataBase/DataBase.h"

Q_DECLARE_METATYPE(SK::PathMapItem*);
Q_DECLARE_METATYPE(SK::DataPathMapItem*);

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
bool MvdDataModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	// Call default behavior.
	QStandardItemModel::setData(index, value, role);

	// Get the custom role, it contains the index of another role the index is related to.
	int customRole = index.data(RoleIndexRole).toInt();
	switch (customRole)
	{
	case PathMapRole:
		{
			// Get the PathMapItem.
			PathMapItem* pathMap = index.data(PathMapRole).value<PathMapItem*>();
			assert(pathMap);

			// Change its m_oscPathItem value.
			std::string newOscPathBit = value.toString().toStdString();
			pathMap->m_oscPathItem = newOscPathBit;

			emit dataChanged(index, index);
			return true;
		}
	case DataPathMapRole:
		{
			// Get the PathMapItem.
			DataPathMapItem* pathMap = index.data(DataPathMapRole).value<DataPathMapItem*>();
			assert(pathMap);

			// Change its m_oscPathItem value.
			std::string newIisuPath = value.toString().toStdString();
			pathMap->m_iisuPath = newIisuPath;

			emit dataChanged(index, index);
			return true;
		}
	}

	return false;
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
	oscItem->setData((int)PathMapRole, RoleIndexRole);
	oscItem->setData(QVariant::fromValue(pathItem), PathMapRole);

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
	oscItem->setData((int)PathMapRole, RoleIndexRole);
	oscItem->setData(QVariant::fromValue((PathMapItem*)pathItem), PathMapRole);

	QStandardItem* iisuItem = new QStandardItem(pathItem->m_iisuPath.c_str());
	iisuItem->setData((int)DataPathMapRole, RoleIndexRole);
	iisuItem->setData(QVariant::fromValue(pathItem), DataPathMapRole);

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