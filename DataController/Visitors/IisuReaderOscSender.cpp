#include "IisuReaderOscSender.h"
#include "SDK/iisuSDK.h"
#include "osc/OscOutboundPacketStream.h"

namespace SK
{

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
	*m_outPacketStream << osc::BeginMessage(m_fullOscPath.c_str());

	*m_outPacketStream << iisuData;

	*m_outPacketStream << osc::EndMessage;
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Vector3ArrayPathMapItem* pathItem)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<SK::Vector3> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<SK::Vector3> >*>(m_iisuDataHandle);
	const SK::Array<SK::Vector3>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << osc::BeginMessage(m_fullOscPath.c_str());

	*m_outPacketStream << (int)iisuData.size();
	for (uint i = 0; i < iisuData.size(); ++i)
		*m_outPacketStream << iisuData[i].x << iisuData[i].y << iisuData[i].z;

	*m_outPacketStream << osc::EndMessage;
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(FloatArrayPathMapItem* pathItem)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<float> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<float> >*>(m_iisuDataHandle);
	const SK::Array<float>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << osc::BeginMessage(m_fullOscPath.c_str());

	*m_outPacketStream << (int)iisuData.size();
	for (uint i = 0; i < iisuData.size(); ++i)
		*m_outPacketStream << iisuData[i];

	*m_outPacketStream << osc::EndMessage;
}

} // namespace SK.