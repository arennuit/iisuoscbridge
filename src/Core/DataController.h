#pragma once

#include "DataBase/DataBase.h"
#include "DataBase/PathMap.h"
#include "SDK/iisuSDK.h"
#include <string>

#define OUTPUT_BUFFER_SIZE 32768

namespace pugi
{
	class xml_node;
}

namespace SK
{

class TypedPathMap;

//////////////////////////////////////////////////////////////////////////
/// \brief This class is the controller in the MVD / MVC pattern.
class DataController
{
public:
	/// \name Singleton management.
	//@{
	static void CreateInstance();
	static void DestroyInstance();
	static DataController* GetInstance() {return sm_instance;}
	//@}

	/// \name Helpers.
	//@{
	void retrieveIisuDataPaths(std::vector<std::string>& iisuDataPaths);
	//@}

	/// \name API.
	//@{
	void editIpAddress(const std::string& newIpAddress) {m_dataBase->setIpAddress(newIpAddress);}
	void editPort(int newPort) {m_dataBase->setPort(newPort);}
	bool editIidFilePath(const std::string& newIidFilePath);

	void toggleResumePause();

	void editFoldAndNameJointsOption(bool isFoldAndNameJoints);

	PathMap* addPathMap(PathMap* siblingPathMap) {return m_dataBase->addPathMap(siblingPathMap);}
	PathMap* insertPathMap(PathMap* siblingPathMap) {return m_dataBase->insertPathMap(siblingPathMap);}
	PathMap* addChildMap(PathMap* parentPathMap) {return m_dataBase->addChildMap(parentPathMap);}
	void deletePathMap(PathMap* pathMap) {m_dataBase->deletePathMap(pathMap);}
	void clearPathMaps() {m_dataBase->clearPathMaps();}

	void newProject();
	void saveProjectToFile(std::string& filePath);
	void loadProjectFromFile(std::string& filePath);
	//@}

protected:
	DataController();
	virtual ~DataController();

	static DataController* sm_instance;

	/// \name Iisu.
	//@{
	bool initIisu();
	void resumeStream();
	void iisuErrorListener( const SK::ErrorEvent& event );
	void newIisuDataFrameListener( const SK::DataFrameEvent& event );
	void pauseStream();
	void termIisu();

	SK::Device* m_device;
	std::vector<SK::IIisuDataExtractor*> m_iisuDataHandles;
	//@}

	/// \name Helpers.
	//@{
	DataBase* m_dataBase;

	std::vector<const PathMap*> m_pathMapsLinearized;
	void linearizePathMap(const PathMap* pathMap);

	std::string findFullOscPath(const PathMap* pathMap) const;

	std::vector<TypedPathMap*> m_typedPathMapsLinearized;

	// TODO: check buffer is large enough when putting the message together.
	char m_oscBuffer[OUTPUT_BUFFER_SIZE];
	void oscSend();

	void saveProjectToFile_recursive(pugi::xml_node& parent, const PathMap* pathMap);
	//@}
};

} // namespace SK.

