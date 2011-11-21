#include <Platform/SkPlatform.h>
#include "DataBase/PathMapItemVisitor.h"
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
class IisuReaderOscSender : public PathMapItemVisitor
{
public:
	IisuReaderOscSender(DataBase* dataBase, osc::OutboundPacketStream* outPacketStream);
	~IisuReaderOscSender() {}

	void setPathItemData(const std::string& fullOscPath, SK::IIisuDataExtractor* iisuDataHandle) {m_fullOscPath = fullOscPath; m_iisuDataHandle = iisuDataHandle;}

protected:
	/// \name Visitor's methods.
	//@{
	void visit(PathMapItem* pathItem) SK_OVERRIDE {} // It makes no sense to read or stream a concrete PathMapItem.
	void visit(DataPathMapItem* pathItem) SK_OVERRIDE {} // It makes no sense to read or stream a generic data.
	void visit(BooleanPathMapItem* pathItem) SK_OVERRIDE;
	void visit(IntegerPathMapItem* pathItem) SK_OVERRIDE;
	void visit(Vector3PathMapItem* pathItem) SK_OVERRIDE;
	void visit(ArrayPathMapItem* pathItem) SK_OVERRIDE {} // It makes no sense to read or stream a generic array.
	void visit(FloatArrayPathMapItem* pathItem) SK_OVERRIDE;
	void visit(Vector3ArrayPathMapItem* pathItem) SK_OVERRIDE;
	//@}

	DataBase* m_dataBase;

	SK::IIisuDataExtractor* m_iisuDataHandle;
	osc::OutboundPacketStream* m_outPacketStream;
	std::string m_fullOscPath;
};

} // namespace SK.