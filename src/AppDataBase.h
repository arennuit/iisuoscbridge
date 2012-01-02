#pragma once

#include "Core/DataBase/DataBase.h"

namespace SK
{

class DataController;

//////////////////////////////////////////////////////////////////////////
/// \brief This class adds the UI update service on data change.
///
///      The application is built out of 3 main layers: the GUI, the control (which stores selections and more
/// generally maintains the app logic) and the database (which maintains the data logic). The way these layers
/// talk together is very important for the consistency of the overall application.
///      Each layer defines a base API and callbacks. The API is called by the upper layers whereas the callbacks
/// are called by the lower layers as a result of the API functions being called. The GUI and control layers
/// updates occur on callbacks rather than in their API function which only transfer the orders downstream. This
/// ensures that the upper layers are updated even when a lower level function is called. Eg, the GUI is updated
/// the same way whether we call a database update function from the GUI layer or from the database layer itself.
/// This would not be possible without the callbacks.
///      Note that practically speaking a layer is two-fold, the 'base' layer knows about the lower layers but does
/// not know anything about the upper layers. So the base layer cannot call the upper layer's callbacks. The base
/// layer is inherited by an 'app' layer that knows about the contiguous application-specific upper layer. It is
/// this app layer that calls the upper layer's callbacks.
///      We will define the term 'functions stream' as the set of all API functions and callbacks called throughout
/// all layers when an API function of callback is called.
///      The order of the function calls in a stream is extremely important to have layers updated properly. In	a
/// stream, several actions may be undertaken, like creating a new object and changing the selection to this new
/// object. In all cases it is important to propagate an action until the end before performing another action,
/// hence if you create the new object before changing the selection to this object, then make sure the creation
/// action was propagated throughout all layers before beginning the selection change - so this selection change
/// must occur after returning from the upper layers callbacks. There are families of streams, or stream types,
/// depending on what the stream actually does. 
///
/// Practically speaking we distinguish the following 3:
///         - objects creation: on PathMap creation (addPathMap, insertPathMap...), one needs to update the GUI
///                             before calling the base callback, this is because we need to spread the PathMap
///                             creation operation on all layers of the app (db, controller and GUI) before
///                             changing the selection (which is done in the base callback).
///         - objects deletion: on PathMap deletion (deletePathMap...) it is exactly the opposite, one needs
///                             to call the base callback (that is changing the selection) before starting the
///                             deletion operation.
///         - objects edition : on db edition, we should first spread the operation and only then should we
///                             perform DataController specifics (such as changing the selection).
///
/// In this way, all operations are done in the right order: we wait for a PathMap to be created in all the app's
/// layers before selecting it, we change the selection before deleting a PathMap, the MainForm deletes the record
/// about a PathMap before its actual deletion is performed...
///
/// The streaming functions of the app logic being only pass-through (the real work is not done in these streaming
/// functions), there are actually only four types of function calls in them:
///         - propagate the operation down-stream,
///         - perform the operation (actually do something),
///         - propagate the operation up-stream (ie calling an upper layer's callback),
///         - call the base callback (ie process the layer's logic)
///
/// Review of operations on PathMap creation (addPathMap, insertPathMap...):
///   - propagate the operation up-stream:
///        * DB creates the PathMap,
///        * MainForm gets to know about the new PathMap and finishes the creation process in its layer,
///   - call the base callback:
///        * the controller changes the selection to the newly created PathMap,
///        * MainForm gets to know about the selection change and finishes the selection process in its layer.
///
/// Review of operations on PathMap deletion (deletePathMap...):
///   - call the base callback:
///        * the controller changes the selection to the parent of the PathMap to be deleted,
///        * MainForm gets to know about the selection change and finishes the selection process in its layer,
///   - propagate the operation up-stream:
///        * MainForm gets to know about the deletion of the PathMap and does its cleaning job,
///        * the DB actually deletes the PathMap.
class AppDataBase : public DataBase
{
	DECLARE_DATA_BASE(AppDataBase)

public:

	/// \name API.
	//@{
	const PathMap* addPathMap(const PathMap* siblingPathMap, const std::string& oscPathBit = NEW_OSC_PATH_BIT, const std::string& iisuPath = NEW_IISU_PATH) SK_OVERRIDE;
	const PathMap* insertPathMap(const PathMap* siblingPathMap, const std::string& oscPathBit = NEW_OSC_PATH_BIT, const std::string& iisuPath = NEW_IISU_PATH) SK_OVERRIDE;
	const PathMap* addChildMap(const PathMap* parentPathMap, const std::string& oscPathBit = NEW_OSC_PATH_BIT, const std::string& iisuPath = NEW_IISU_PATH) SK_OVERRIDE;
	bool deletePathMap(const PathMap* pathMap) SK_OVERRIDE;
	bool clearPathMaps() SK_OVERRIDE;
	//@}

	/// \name Accessors.
	//@{
	void setIpAddress(const std::string& ipAddress) SK_OVERRIDE;
	void setPort(int port) SK_OVERRIDE;
	void setIidFilePath(const std::string& iidFilePath) SK_OVERRIDE;
	void setIsObservationOn(bool isObservationOn) SK_OVERRIDE;
	void setIsFoldAndNameJoints(bool isFoldAndNameJoints) SK_OVERRIDE;
	void setOscPacketSize(uint oscPacketSize) SK_OVERRIDE;
	//@}

	void setDataController(DataController* dataController) {m_dataController = dataController;}

protected:
	AppDataBase() : DataBase(), m_dataController(0) {}
	virtual ~AppDataBase() {}

	DataController* m_dataController;
};

} // namespace SK.