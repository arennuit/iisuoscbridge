#include <Platform/SkPlatform.h>
#include "Core/IisuManager/TypedPathMap/TypedPathMapVisitor.h"
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
/// \note An array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT. Any other type
///       of data only needto check m_dataBase->getDecorateStream() in order to know whether to stream
///       decorated or not.
class IisuReaderOscSender : public TypedPathMapVisitor
{
public:
	IisuReaderOscSender(DataBase* dataBase, osc::OutboundPacketStream* outPacketStream);
	~IisuReaderOscSender() {}

	void setPathMapData(const std::string& fullOscPath, SK::IIisuDataExtractor* iisuDataHandle) {m_fullOscPath = fullOscPath; m_iisuDataHandle = iisuDataHandle;}

protected:
	/// \name Visitor's methods.
	//@{
	void visit(TypedPathMap* typedPathMap) SK_OVERRIDE {} // It makes no sense to read or stream an abstract TypedPathMap.
	void visit(DataTypedPathMap* typedPathMap) SK_OVERRIDE {} // It makes no sense to read or stream a generic data.
	void visit(BooleanPathMap* typedPathMap) SK_OVERRIDE;
	void visit(IntegerPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector3PathMap* typedPathMap) SK_OVERRIDE;
	void visit(ArrayPathMap* typedPathMap) SK_OVERRIDE {} // It makes no sense to read or stream a generic array.
	void visit(FloatArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector3ArrayPathMap* typedPathMap) SK_OVERRIDE;
	//@}

	DataBase* m_dataBase;

	SK::IIisuDataExtractor* m_iisuDataHandle;
	osc::OutboundPacketStream* m_outPacketStream;
	std::string m_fullOscPath;
};

} // namespace SK.