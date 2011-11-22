#include <Platform/SkPlatform.h>
#include "DataBase/PathMapVisitor.h"
#include <string>

namespace osc
{
	class OutboundPacketStream;
}

namespace SK
{

class DataBase;
class IIisuDataExtractor;

//////////////////////////////////////////////////////////////////////////
/// \brief This class reads the data from the iisu pulse and streams it via OSC.
class IisuReaderOscSender : public PathMapVisitor
{
public:
	IisuReaderOscSender(DataBase* dataBase, osc::OutboundPacketStream* outPacketStream);
	~IisuReaderOscSender() {}

	void setPathMapData(const std::string& fullOscPath, SK::IIisuDataExtractor* iisuDataHandle) {m_fullOscPath = fullOscPath; m_iisuDataHandle = iisuDataHandle;}

protected:
	/// \name Visitor's methods.
	//@{
	void visit(PathMap* pathMap) SK_OVERRIDE {} // It makes no sense to read or stream a concrete PathMap.
	void visit(DataPathMap* pathMap) SK_OVERRIDE {} // It makes no sense to read or stream a generic data.
	void visit(BooleanPathMap* pathMap) SK_OVERRIDE;
	void visit(IntegerPathMap* pathMap) SK_OVERRIDE;
	void visit(Vector3PathMap* pathMap) SK_OVERRIDE;
	void visit(ArrayPathMap* pathMap) SK_OVERRIDE {} // It makes no sense to read or stream a generic array.
	void visit(FloatArrayPathMap* pathMap) SK_OVERRIDE;
	void visit(Vector3ArrayPathMap* pathMap) SK_OVERRIDE;
	//@}

	DataBase* m_dataBase;

	SK::IIisuDataExtractor* m_iisuDataHandle;
	osc::OutboundPacketStream* m_outPacketStream;
	std::string m_fullOscPath;
};

} // namespace SK.