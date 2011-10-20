#include <Platform/SkPlatform.h>
#include "DataBase/PathMapItemVisitor.h"
#include <string>

namespace osc
{
	class OutboundPacketStream;
}

namespace SK
{

class IIisuDataExtractor;

//////////////////////////////////////////////////////////////////////////
/// \name This class reads the data from the iisu pulse and streams it via OSC.
class IisuReaderOscSender : public PathMapItemVisitor
{
public:
	IisuReaderOscSender(osc::OutboundPacketStream* outPacketStream);
	~IisuReaderOscSender() {}

	void setPathItemData(const std::string& fullOscPath, SK::IIisuDataExtractor* iisuDataHandle) {m_fullOscPath = fullOscPath; m_iisuDataHandle = iisuDataHandle;}

protected:
	/// \name Visitor's methods.
	//@{
	void visit(PathMapItem* pathItem) SK_OVERRIDE {}
	void visit(DataPathMapItem* pathItem) SK_OVERRIDE {}
	void visit(BooleanPathMapItem* pathItem) SK_OVERRIDE;
	void visit(Vector3ArrayPathMapItem* pathItem) SK_OVERRIDE;
	void visit(FloatArrayPathMapItem* pathItem) SK_OVERRIDE;
	//@}

	SK::IIisuDataExtractor* m_iisuDataHandle;
	osc::OutboundPacketStream* m_outPacketStream;
	std::string m_fullOscPath;
};

} // namespace SK.