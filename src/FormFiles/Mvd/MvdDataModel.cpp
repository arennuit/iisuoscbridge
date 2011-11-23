#include "MvdDataModel.h"

#include "assert.h"

#include <QStandardItem>
#include <QVariant>
#include <QString>
#include "DataBase/PathMap.h"
#include "DataBase/DataBase.h"

Q_DECLARE_METATYPE(SK::PathMap*);
Q_DECLARE_METATYPE(SK::DataPathMap*);

namespace SK
{

//////////////////////////////////////////////////////////////////////////
MvdDataModel::MvdDataModel(QObject *parent) :
	QStandardItemModel(parent),
	PathMapVisitor(),
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
			// Get the PathMap.
			PathMap* pathMap = index.data(PathMapRole).value<PathMap*>();
			assert(pathMap);

			// Change its m_oscPathBit value.
			std::string newOscPathBit = value.toString().toStdString();
			pathMap->m_oscPathBit = newOscPathBit;

			emit dataChanged(index, index);
			return true;
		}
	case DataPathMapRole:
		{
			// Get the PathMap.
			DataPathMap* pathMap = index.data(DataPathMapRole).value<DataPathMap*>();
			assert(pathMap);

			// Change its m_iisuPath value.
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
	if (DataBase::GetInstance()->getPathsTreeRoot())
		DataBase::GetInstance()->getPathsTreeRoot()->accept(this);
}

//////////////////////////////////////////////////////////////////////////
void MvdDataModel::visit(PathMap* pathMap)
{
	assert(pathMap);

	// TODO: quand je saurai ajouter un item à droite d'un item existant je pourrais appeler l'overload
	//       de visit() sur PathMap et compléter par un itel à droite de oscItem pour iisuItem,
	//       à la place de réécrire tout le code.

	// Row.
	QStandardItem* oscItem = new QStandardItem(pathMap->m_oscPathBit.c_str());
	oscItem->setData((int)PathMapRole, RoleIndexRole);
	oscItem->setData(QVariant::fromValue(pathMap), PathMapRole);

	QStandardItem* iisuItem = new QStandardItem("");

	if (!m_parentItem)
	{
		setItem(0, 0, oscItem);
		setItem(0, 1, iisuItem);
	}
	else
		m_parentItem->appendRow(QList<QStandardItem*>() << oscItem << iisuItem);

	// Recursive call to children.
	for (uint i = 0; i < pathMap->m_children.size(); ++i)
	{
		m_parentItem = oscItem;
		pathMap->m_children[i]->accept(this);
	}
}

//////////////////////////////////////////////////////////////////////////
void MvdDataModel::visit(DataPathMap* pathMap)
{
	assert(pathMap);

	// TODO: quand je saurai ajouter un item à droite d'un item existant je pourrais appeler l'overload
	//       de visit() sur PathMap et compléter par un itel à droite de oscItem pour iisuItem,
	//       à la place de réécrire tout le code.

	// Row.
	QStandardItem* oscItem = new QStandardItem(pathMap->m_oscPathBit.c_str());
	oscItem->setData((int)PathMapRole, RoleIndexRole);
	oscItem->setData(QVariant::fromValue((PathMap*)pathMap), PathMapRole);

	QStandardItem* iisuItem = new QStandardItem(pathMap->m_iisuPath.c_str());
	iisuItem->setData((int)DataPathMapRole, RoleIndexRole);
	iisuItem->setData(QVariant::fromValue(pathMap), DataPathMapRole);

	if (!m_parentItem)
	{
		setItem(0, 0, oscItem);
		setItem(0, 1, iisuItem);
	}
	else
		m_parentItem->appendRow(QList<QStandardItem*>() << oscItem << iisuItem);

	// Recursive call to children.
	for (uint i = 0; i < pathMap->m_children.size(); ++i)
	{
		m_parentItem = oscItem;
		pathMap->m_children[i]->accept(this);
	}
}

} // namespace SK.