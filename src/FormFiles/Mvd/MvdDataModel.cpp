#include "MvdDataModel.h"

#include "assert.h"

#include <QStandardItem>
#include <QVariant>
#include <QString>
#include "DataBase/DataObjects/TypedPathMap.h"
#include "DataBase/DataBase.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
MvdDataModel::MvdDataModel(QObject *parent) :
	QStandardItemModel(parent),
	TypedPathMapVisitor(),
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
			// Get the TypedPathMap.
			TypedPathMap* typedPathMap = index.data(PathMapRole).value<TypedPathMap*>();
			assert(typedPathMap);

			// Change its m_oscPathBit value.
			std::string newOscPathBit = value.toString().toStdString();
			typedPathMap->m_oscPathBit = newOscPathBit;

			emit dataChanged(index, index);
			return true;
		}
	case DataPathMapRole:
		{
			// Get the TypedPathMap.
			DataTypedPathMap* typedPathMap = index.data(DataPathMapRole).value<DataTypedPathMap*>();
			assert(typedPathMap);

			// Change its m_iisuPath value.
			std::string newIisuPath = value.toString().toStdString();
			typedPathMap->m_iisuPath = newIisuPath;

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
	m_parentItem = 0;

	// Describe all data objects and their properties.
	setHorizontalHeaderLabels(QStringList() << "OSC hierarchy" << "iisu path");

	// Parse the path associations.
	if (DataBase::GetInstance()->getPathsTreeRoot())
		DataBase::GetInstance()->getPathsTreeRoot()->accept(this);
}

//////////////////////////////////////////////////////////////////////////
void MvdDataModel::visit(TypedPathMap* typedPathMap)
{
	assert(typedPathMap);

	// Row.
	QStandardItem* oscItem = new QStandardItem(typedPathMap->m_oscPathBit.c_str());
	oscItem->setData((int)PathMapRole, RoleIndexRole);
	oscItem->setData(QVariant::fromValue(typedPathMap), PathMapRole);

	QStandardItem* iisuItem = new QStandardItem("");

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
	for (uint i = 0; i < typedPathMap->m_children.size(); ++i)
	{
		m_parentItem = oscItem;
		typedPathMap->m_children[i]->accept(this);
	}
}

//////////////////////////////////////////////////////////////////////////
void MvdDataModel::visit(DataTypedPathMap* typedPathMap)
{
	assert(typedPathMap);

	// Row.
	QStandardItem* oscItem = new QStandardItem(typedPathMap->m_oscPathBit.c_str());
	oscItem->setData((int)PathMapRole, RoleIndexRole);
	oscItem->setData(QVariant::fromValue((TypedPathMap*)typedPathMap), PathMapRole);

	QStandardItem* iisuItem = new QStandardItem(typedPathMap->m_iisuPath.c_str());
	iisuItem->setData((int)DataPathMapRole, RoleIndexRole);
	iisuItem->setData(QVariant::fromValue(typedPathMap), DataPathMapRole);

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
	for (uint i = 0; i < typedPathMap->m_children.size(); ++i)
	{
		m_parentItem = oscItem;
		typedPathMap->m_children[i]->accept(this);
	}
}

} // namespace SK.