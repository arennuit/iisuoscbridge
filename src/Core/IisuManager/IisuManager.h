#pragma once

#include "SDK/iisuSDK.h"

#define OUTPUT_BUFFER_SIZE 32768

namespace SK
{

class DataBase;
class PathMap;
class TypedPathMap;

/// \brief This class handles the iisu-related sauce.
class IisuManager
{
public:
	IisuManager(DataBase* dataBase) : m_device(0), m_dataBase(dataBase) {}
	~IisuManager() {}

	/// \name API.
	//@{
	bool initIisu();
	bool resumeStream();
	bool pauseStream();
	void termIisu();

	bool loadIidGraph(const std::string& newIidFilePath);
	void retrieveIisuDataPaths(std::vector<std::string>& iisuDataPaths);
	//@}

protected:

	/// \name Iisu.
	//@{
	void iisuErrorListener( const SK::ErrorEvent& event );
	void newIisuDataFrameListener( const SK::DataFrameEvent& event );

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
	//@}
};
	
} // namespace SK.