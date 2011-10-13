#include "DataQtModel.h"

#include <QStandardItem>
#include <QVariant>
#include <QString>

namespace SK
{

//////////////////////////////////////////////////////////////////////////
DataQtModel::DataQtModel(QObject *parent) :
	QStandardItemModel(parent)
{

}

//////////////////////////////////////////////////////////////////////////
bool DataQtModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
	{
		return false;
	}

	// Call default behavior.
	QStandardItemModel::setData(index, value, role);

	// Get the custom role and switch to the relevant edition bit of code depending on it.
	int customRole = index.data(RoleIndexRole).toInt();
	switch (customRole)
	{
	case ObjectNameRole:
		{
			DataObject* object = index.data(ObjectNameRole).value<DataObject*>();
			assert(object);

			std::string newName = value.toString().toStdString();
			object->setName(StringUtils::toWideString(newName));

			break;
		}
	case FrameQwValueRole:
		{
			Property<Frame>* prop = static_cast<Property<Frame>*>(index.data(FrameQwValueRole).value<PropertyBase*>());
			assert(prop);

			float newQw = value.toFloat();
			// TODO: set the new value to the property's data.
			//prop->set();

			break;
		}
	default:
		{
			// TODO: log error unhandled case.
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
void DataQtModel::update()
{
	clear();

	//// Get the model manager.
	//CoreManager* modelManager = CoreManager::GetInstance();
	//if (!modelManager)
	//{
	//	setHorizontalHeaderLabels(QStringList() << "!!! ALERT !!!");
	//	setItem(0, 0, new QStandardItem("No CoreManager Was Found."));

	//	return;
	//}

	//// Describe all data objects and their properties.
	//setHorizontalHeaderLabels(QStringList() << "Name" << "Value" << "Type");

	//unsigned int object_idx = 0;
	//for (CoreManager::DataObjectsList::const_iterator object_it = modelManager->getDataObjects().begin(); object_it != modelManager->getDataObjects().end(); ++object_it)
	//{
	//	DataObject* object = *object_it;
	//	assert(object);

	//	// Object.
	//	m_objectNameItem = new QStandardItem(StringUtils::toString(object->getName()).c_str());
	//	setItem(object_idx, 0, m_objectNameItem);

	//	QStandardItem* typeNameItem = new QStandardItem(StringUtils::toString(object->getTypeName()).c_str());
	//	typeNameItem->setEditable(false);
	//	setItem(object_idx, 2, typeNameItem);

	//	m_objectNameItem->setData((int)ObjectNameRole, RoleIndexRole);
	//	m_objectNameItem->setData(QVariant::fromValue(object), ObjectNameRole);

	//	// Properties.
	//	for (PropertyMap::const_iterator prop_it = object->getPropertyMap().begin(); prop_it != object->getPropertyMap().end(); ++prop_it)
	//	{
	//		m_prop = prop_it->second;
	//		assert(m_prop);

	//		m_prop->accept(this);
	//	}

	//	++object_idx;
	//}
}

} // namespace SK.