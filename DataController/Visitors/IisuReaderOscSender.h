#include <Platform/SkPlatform.h>
#include "DataBase/PathMapItemVisitor.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \name This class reads the data from the iisu pulse and streams it via OSC.
class IisuReaderOscSender : public PathMapItemVisitor
{
public:
	IisuReaderOscSender() {}
	~IisuReaderOscSender() {}

protected:
	/// \name Visitor's methods.
	//@{
	void visit(PathMapItem* pathItem) SK_OVERRIDE {}
	void visit(DataPathMapItem* pathItem) SK_OVERRIDE {}
	void visit(BooleanPathMapItem* pathItem) SK_OVERRIDE;
	void visit(Vector3ArrayPathMapItem* pathItem) SK_OVERRIDE;
	void visit(FloatArrayPathMapItem* pathItem) SK_OVERRIDE;
	//@}
};

} // namespace SK.