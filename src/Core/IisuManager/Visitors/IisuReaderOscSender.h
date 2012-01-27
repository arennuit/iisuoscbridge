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
	void visit(ArrayPathMap* typedPathMap) SK_OVERRIDE {} // It makes no sense to read or stream a generic array.

	void visit(BoolPathMap* typedPathMap) SK_OVERRIDE;
	void visit(CharPathMap* typedPathMap) SK_OVERRIDE;
	void visit(FloatPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int8PathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int16PathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int32PathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int64PathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt8PathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt16PathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt32PathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt64PathMap* typedPathMap) SK_OVERRIDE;
	void visit(Color4cPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Color4fPathMap* typedPathMap) SK_OVERRIDE;
	void visit(EnumPathMap* typedPathMap) SK_OVERRIDE;
	void visit(FramePathMap* typedPathMap) SK_OVERRIDE;
	void visit(Matrix3PathMap* typedPathMap) SK_OVERRIDE;
	void visit(Matrix4PathMap* typedPathMap) SK_OVERRIDE;
	void visit(QuatPathMap* typedPathMap) SK_OVERRIDE;
	void visit(StringPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector2PathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector2iPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector3PathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector4PathMap* typedPathMap) SK_OVERRIDE;

	void visit(BoolArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(CharArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(FloatArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int8ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int16ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int32ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Int64ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt8ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt16ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt32ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(UInt64ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Color4cArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Color4fArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(EnumArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(FrameArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Matrix3ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Matrix4ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(QuatArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(StringArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector2ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector2iArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector3ArrayPathMap* typedPathMap) SK_OVERRIDE;
	void visit(Vector4ArrayPathMap* typedPathMap) SK_OVERRIDE;
	//@}

	DataBase* m_dataBase;

	SK::IIisuDataExtractor* m_iisuDataHandle;
	osc::OutboundPacketStream* m_outPacketStream;
	std::string m_fullOscPath;
};

} // namespace SK.