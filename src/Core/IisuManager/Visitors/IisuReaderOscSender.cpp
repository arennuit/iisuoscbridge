#include "IisuReaderOscSender.h"
#include "SDK/iisuSDK.h"
#include "osc/OscOutboundPacketStream.h"
#include "DataController/TypedPathMap/TypedPathMap.h"
#include "DataBase/DataBase.h"

namespace SK
{

// TODO: share and use joints names in ProtoPose.h.
static const std::string JointsName[SK::SkeletonEnum::_COUNT] =
{
	"pelvis",
	"waist",
	"collar",
	"neck",
	"head",

	"rightShoulder",
	"rightElbow",
	"rightWrist",
	"rightHand",

	"rightHip",
	"rightKnee",
	"rightAnkle",
	"rightFoot",

	"leftShoulder",
	"leftElbow",
	"leftWrist",
	"leftHand",

	"leftHip",
	"leftKnee",
	"leftAnkle",
	"leftFoot"
};

// Make osc::BeginMessage() easier to use with std::string.
osc::BeginMessage OscBeginMessage(const std::string& oscPath) {return osc::BeginMessage(oscPath.c_str());}
osc::MessageTerminator OscEndMessage() {return osc::MessageTerminator();}

//////////////////////////////////////////////////////////////////////////
IisuReaderOscSender::IisuReaderOscSender(DataBase* dataBase, osc::OutboundPacketStream* outPacketStream) :
	TypedPathMapVisitor(),
	m_dataBase(dataBase),
	m_outPacketStream(outPacketStream),
	m_iisuDataHandle(0)
{
	assert(m_dataBase);
	assert(m_outPacketStream);
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(BooleanPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<bool>* iisuDataHandle = static_cast<SK::DataHandle<bool>*>(m_iisuDataHandle);
	const bool& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << OscBeginMessage(m_fullOscPath);
	*m_outPacketStream << iisuData;
	*m_outPacketStream << OscEndMessage();
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(IntegerPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<int>* iisuDataHandle = static_cast<SK::DataHandle<int>*>(m_iisuDataHandle);
	const int& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << OscBeginMessage(m_fullOscPath);
	*m_outPacketStream << iisuData;
	*m_outPacketStream << OscEndMessage();
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Vector3PathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Vector3>* iisuDataHandle = static_cast<SK::DataHandle<SK::Vector3>*>(m_iisuDataHandle);
	const SK::Vector3& iisuData = iisuDataHandle->get();

	// Send via OSC.
	if (m_dataBase->getIsFoldAndNameJoints())
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/x");
		*m_outPacketStream << iisuData.x;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/y");
		*m_outPacketStream << iisuData.y;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/z");
		*m_outPacketStream << iisuData.z;
		*m_outPacketStream << OscEndMessage();
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);
		*m_outPacketStream << iisuData.x << iisuData.y << iisuData.z;
		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(FloatArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<float> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<float> >*>(m_iisuDataHandle);
	const SK::Array<float>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	if (m_dataBase->getIsFoldAndNameJoints())
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/" + JointsName[i]);
			*m_outPacketStream << iisuData[i];
			*m_outPacketStream << OscEndMessage();
		}
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);

		// Size and data in a raw.
		*m_outPacketStream << (int)iisuData.size();
		for (uint i = 0; i < iisuData.size(); ++i)
			*m_outPacketStream << iisuData[i];

		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Vector3ArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<SK::Vector3> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<SK::Vector3> >*>(m_iisuDataHandle);
	const SK::Array<SK::Vector3>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	if (m_dataBase->getIsFoldAndNameJoints())
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + "/" + JointsName[i];

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
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);

		// Size and data in a raw.
		*m_outPacketStream << (int)iisuData.size();
		for (uint i = 0; i < iisuData.size(); ++i)
			*m_outPacketStream << iisuData[i].x << iisuData[i].y << iisuData[i].z;

		*m_outPacketStream << OscEndMessage();
	}
}

} // namespace SK.