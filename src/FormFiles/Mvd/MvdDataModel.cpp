#include "MvdDataModel.h"

#include "assert.h"

#include <QStandardItem>
#include <QVariant>
#include <QString>
#include "Core/DataBase/PathMap.h"
#include "Core/DataBase/DataBase.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
MvdDataModel::MvdDataModel(QObject *parent) :
	QStandardItemModel(parent),
	m_parentItem(0)
{

}

//////////////////////////////////////////////////////////////////////////
bool MvdDataModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	// If the role is not PathMapRole then call the default behavior.
	int customRole = index.data(RoleIndexRole).toInt();
	if (customRole != PathMapRole)
		return QStandardItemModel::setData(index, value, role);

	QStandardItemModel::setData(index, value, role);

	// Get the PathMap.
	PathMap* pathMap = index.data(PathMapRole).value<PathMap*>();
	assert(pathMap);

	// The attribute modified depends on the column of the item.
	if (index.column() == 0)
	{
		// Change its m_oscPathBit value.
		std::string newOscPathBit = value.toString().toStdString();
		pathMap->setOscPathBit(newOscPathBit);
	}
	else if (index.column() == 1)
	{
		// Change its m_iisuPath value.
		std::string newIisuPath = value.toString().toStdString();
		pathMap->setIisuPath(newIisuPath);
	}

	// Update the views.
	emit dataChanged(index, index);

	return true;
}

//////////////////////////////////////////////////////////////////////////
void MvdDataModel::cleanAndReBuildAll()
{
	clear();
	m_parentItem = 0;

	// Describe all data objects and their properties.
	setHorizontalHeaderLabels(QStringList() << "OSC hierarchy" << "iisu path");

	// Parse the path associations.
	if (DataBase::GetInstance()->getPathMapsRoot())
		cleanAndReBuild_pathMap(DataBase::GetInstance()->getPathMapsRoot());
}

//////////////////////////////////////////////////////////////////////////
void MvdDataModel::cleanAndReBuild_pathMap(const PathMap* pathMap)
{
	assert(pathMap);

	// Row.
	QStandardItem* oscItem = new QStandardItem(pathMap->getOscPathBit().c_str());
	oscItem->setData((int)PathMapRole, RoleIndexRole);
	oscItem->setData(QVariant::fromValue((PathMap*)pathMap), PathMapRole);

	QStandardItem* iisuItem = new QStandardItem(pathMap->getIisuPath().c_str());
	iisuItem->setData((int)PathMapRole, RoleIndexRole);
	iisuItem->setData(QVariant::fromValue((PathMap*)pathMap), PathMapRole);

	if (!m_parentItem)
	{
		setItem(0, 0, oscItem);
		setItem(0, 1, iisuItem);
	}
	else
	{
		int rowIdx = m_parentItem->rowCount();
		m_parentItem->setChild(rowIdx, 0, oscItem);
		m_parentItem->setChild(rowIdx, 1, iisuItem);
	}

	// Recursive call to children.
	for (uint i = 0; i < pathMap->getChildren().size(); ++i)
	{
		m_parentItem = oscItem;
		cleanAndReBuild_pathMap(pathMap->getChildren()[i]);
	}
}

} // namespace SK.