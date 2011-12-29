#pragma once

#include "Core/DataController.h"
#include "MainForm.h"

namespace SK
{

/// \brief This class adds the UI update service on data change.
///
/// On PathMap creation callbacks (onAddPathMap, onInsertPathMap...), one needs to update the GUI before calling
/// the base callback, this is because we need to spread the PathMap creation operation on all layers of the app
/// (db, controller and GUI) before changing the selection (which is done in the base callback). It is exactly
/// the opposite when deleting PathMaps, one needs to call the base callback (that is changing the selection)
/// before starting the deletion operation. When editing data, we should first spread the operation and only
/// then should we perform DataController specifics (such as changing the selection).
///
/// PathMap creation and selection change are well separated. In the case of PathMap creation, the instantiation
/// is first performed on all layers to its end, then when the creation is fully finished on all layers, the
/// selection change is performed. In the case of PathMap deletion, the selection change is first performed
/// throughout all layers, then only when the selection has finished changing do we perform the PathMap deletion
/// itself, also throughout all layers.
/// In this way, all operations are done in the right order: we wait for a PathMap to be created in all the app's
/// layers before selecting it, we change the selection before deleting a PathMap, the MainForm deletes the record
/// about a PathMap before its actual deletion is performed...
///
/// Review of operations on PathMap creation:
///   - DB creates the PathMap,
///   - MainForm gets to know about the new PathMap and finishes the creation process in its layer,
///   - the controller changes the selection to the newly created PathMap,
///   - MainForm gets to know about the selection change and finished the selection process in its layer.
///
/// Review of operations on PathMap deletion:
///   - the controller changes the selection to the parent of the PathMap to be deleted,
///   - MainForm gets to know about the selection change and finished the selection process in its layer,
///   - MainForm gets to know about the deletion of the PathMap and does its cleaning job,
///   - the DB actually deletes the PathMap.
class AppDataController : public DataController
{
	DECLARE_DATA_BASE(AppDataController)

public:

	/// \name API redefinitions.
	//@{
	void editSelection(const PathMap* newSelectedPathMap) SK_OVERRIDE;
	//@}

	/// \name Accessors.
	//@{
	void setMainForm(MainForm* mainForm) {m_mainForm = mainForm;}
	//@}

	/// \name Callbacks.
	//@{
	void onAddPathMap(const PathMap* newPathMap) SK_OVERRIDE;
	void onInsertPathMap(const PathMap* newPathMap) SK_OVERRIDE;
	void onAddChildMap(const PathMap* newPathMap) SK_OVERRIDE;
	void onDeletePathMap(const PathMap* pathMapToBeDeleted) SK_OVERRIDE;
	void onClearPathMaps() SK_OVERRIDE;

	void onIpAddressChanged(const std::string& ipAddress) SK_OVERRIDE;
	void onPortChanged(int port) SK_OVERRIDE;
	void onIidFilePathChanged(const std::string& iidFilePath) SK_OVERRIDE;
	void onIsObservationOnChanged(bool isObservationOn) SK_OVERRIDE;
	void onIsFoldAndNameJointsChanged(bool isFoldAndNameJoints) SK_OVERRIDE;
	void onOscPacketSizeChanged(uint oscPacketSize) SK_OVERRIDE;
	//@}

protected:
	AppDataController() : DataController(), m_mainForm(0) {}
	virtual ~AppDataController() {}

	MainForm* m_mainForm;
};

} // namespace SK.