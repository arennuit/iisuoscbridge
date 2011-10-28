#include "IisuReaderOscSender.h"
#include "SDK/iisuSDK.h"
#include "osc/OscOutboundPacketStream.h"
#include "Database/PathMapItem.h"

namespace SK
{

// TODO: share and use joints names in ProtoPose.h.
static const std::string JointsName[SK::SkeletonEnum::_COUNT] =
{
	"Pelvis",
	"Waist",
	"Collar",
	"Neck",
	"Head",

	"RightShoulder",
	"RightElbow",
	"RightWrist",
	"RightHand",

	"RightHip",
	"RightKnee",
	"RightAnkle",
	"RightFoot",

	"LeftShoulder",
	"LeftElbow",
	"LeftWrist",
	"LeftHand",

	"LeftHip",
	"LeftKnee",
	"LeftAnkle",
	"LeftFoot"
};

// Make osc::BeginMessage() easier to use with std::string.
osc::BeginMessage OscBeginMessage(const std::string& oscPath) {return osc::BeginMessage(oscPath.c_str());}
osc::MessageTerminator OscEndMessage() {return osc::MessageTerminator();}

//////////////////////////////////////////////////////////////////////////
IisuReaderOscSender::IisuReaderOscSender(osc::OutboundPacketStream* outPacketStream) :
	PathMapItemVisitor(),
	m_outPacketStream(outPacketStream),
	m_iisuDataHandle(0)
{

}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(BooleanPathMapItem* pathItem)
{
	assert(m_outPacketStream);

	// Get the data from iisu.
	SK::DataHandle<bool>* iisuDataHandle = static_cast<SK::DataHandle<bool>*>(m_iisuDataHandle);
	const bool& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << OscBeginMessage(m_fullOscPath);
	*m_outPacketStream << iisuData;
	*m_outPacketStream << OscEndMessage();
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Vector3ArrayPathMapItem* pathItem)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<SK::Vector3> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<SK::Vector3> >*>(m_iisuDataHandle);
	const SK::Array<SK::Vector3>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
	*m_outPacketStream << (int)iisuData.size();
	*m_outPacketStream << OscEndMessage();

	for (uint i = 0; i < iisuData.size(); ++i)
	{
		// Concatenate the OSC path.
		std::string messagePath = m_fullOscPath + "/";
		if (pathItem->m_areJointsNamed && iisuData.size() == SK::SkeletonEnum::_COUNT)
			messagePath += JointsName[i];
		else
			messagePath += i;

		// Actually OSC stream.
		*m_outPacketStream << OscBeginMessage(messagePath + "/x");
		*m_outPacketStream << iisuData[i].x;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(messagePath + "/y");
		*m_outPacketStream << iisuData[i].y;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(messagePath + "/z");
		*m_outPacketStream << iisuData[i].z;
		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(FloatArrayPathMapItem* pathItem)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<float> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<float> >*>(m_iisuDataHandle);
	const SK::Array<float>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
	*m_outPacketStream << (int)iisuData.size();
	*m_outPacketStream << OscEndMessage();

	for (uint i = 0; i < iisuData.size(); ++i)
	{
		// Concatenate the OSC path.
		std::string messagePath = m_fullOscPath + "/";
		if (pathItem->m_areJointsNamed && iisuData.size() == SK::SkeletonEnum::_COUNT)
			messagePath += JointsName[i];
		else
			messagePath += i;

		// Actually OSC stream.
		*m_outPacketStream << OscBeginMessage(messagePath);
		*m_outPacketStream << iisuData[i];
		*m_outPacketStream << OscEndMessage();
	}
}

} // namespace SK.