#include "IisuReaderOscSender.h"
#include "SDK/iisuSDK.h"
#include "osc/OscOutboundPacketStream.h"
#include "Core/IisuManager/TypedPathMap/TypedPathMap.h"
#include "Core/DataBase/DataBase.h"

namespace SK
{

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
void IisuReaderOscSender::visit(BoolPathMap* typedPathMap)
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
void IisuReaderOscSender::visit(CharPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<char>* iisuDataHandle = static_cast<SK::DataHandle<char>*>(m_iisuDataHandle);
	const char& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << OscBeginMessage(m_fullOscPath);
	*m_outPacketStream << iisuData;
	*m_outPacketStream << OscEndMessage();
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(FloatPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<float>* iisuDataHandle = static_cast<SK::DataHandle<float>*>(m_iisuDataHandle);
	const float& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << OscBeginMessage(m_fullOscPath);
	*m_outPacketStream << iisuData;
	*m_outPacketStream << OscEndMessage();
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Int8PathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<int8_t>* iisuDataHandle = static_cast<SK::DataHandle<int8_t>*>(m_iisuDataHandle);
	const int8_t& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << OscBeginMessage(m_fullOscPath);
	*m_outPacketStream << iisuData;
	*m_outPacketStream << OscEndMessage();
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Int16PathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<int16_t>* iisuDataHandle = static_cast<SK::DataHandle<int16_t>*>(m_iisuDataHandle);
	const int16_t& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << OscBeginMessage(m_fullOscPath);
	*m_outPacketStream << iisuData;
	*m_outPacketStream << OscEndMessage();
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Int32PathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<int32_t>* iisuDataHandle = static_cast<SK::DataHandle<int32_t>*>(m_iisuDataHandle);
	const int32_t& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << OscBeginMessage(m_fullOscPath);
	*m_outPacketStream << iisuData;
	*m_outPacketStream << OscEndMessage();
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Int64PathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<int64_t>* iisuDataHandle = static_cast<SK::DataHandle<int64_t>*>(m_iisuDataHandle);
	const int64_t& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << OscBeginMessage(m_fullOscPath);
	*m_outPacketStream << iisuData;
	*m_outPacketStream << OscEndMessage();
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(UInt8PathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<uint8_t>* iisuDataHandle = static_cast<SK::DataHandle<uint8_t>*>(m_iisuDataHandle);
	const uint8_t& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << OscBeginMessage(m_fullOscPath);
	*m_outPacketStream << iisuData;
	*m_outPacketStream << OscEndMessage();
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(UInt16PathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<uint16_t>* iisuDataHandle = static_cast<SK::DataHandle<uint16_t>*>(m_iisuDataHandle);
	const uint16_t& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << OscBeginMessage(m_fullOscPath);
	*m_outPacketStream << iisuData;
	*m_outPacketStream << OscEndMessage();
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(UInt32PathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<uint32_t>* iisuDataHandle = static_cast<SK::DataHandle<uint32_t>*>(m_iisuDataHandle);
	const uint32_t& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: OscPack cannot stream uint32, hence we stream the data as int32 and clamp numbers above INT32_MAX.
	int32_t value = iisuData > INT32_MAX ? (int32_t)INT32_MAX : (int32_t)iisuData;
	*m_outPacketStream << OscBeginMessage(m_fullOscPath);
	*m_outPacketStream << value;
	*m_outPacketStream << OscEndMessage();
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(UInt64PathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<uint64_t>* iisuDataHandle = static_cast<SK::DataHandle<uint64_t>*>(m_iisuDataHandle);
	const uint64_t& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: OscPack cannot stream uint64, hence we stream the data as int64 and clamp numbers above INT64_MAX.
	int64_t value = iisuData > INT64_MAX ? (int64_t)INT64_MAX : (int64_t)iisuData;
	*m_outPacketStream << OscBeginMessage(m_fullOscPath);
	*m_outPacketStream << value;
	*m_outPacketStream << OscEndMessage();
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Color4cPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Color4c>* iisuDataHandle = static_cast<SK::DataHandle<SK::Color4c>*>(m_iisuDataHandle);
	const SK::Color4c& iisuData = iisuDataHandle->get();

	// Send via OSC.
	if (m_dataBase->getDecorateStream())
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/r");
		*m_outPacketStream << iisuData.r;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/g");
		*m_outPacketStream << iisuData.g;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/b");
		*m_outPacketStream << iisuData.b;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/a");
		*m_outPacketStream << iisuData.a;
		*m_outPacketStream << OscEndMessage();
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);
		*m_outPacketStream << iisuData.r << iisuData.g << iisuData.b << iisuData.a;
		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Color4fPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Color4f>* iisuDataHandle = static_cast<SK::DataHandle<SK::Color4f>*>(m_iisuDataHandle);
	const SK::Color4f& iisuData = iisuDataHandle->get();

	// Send via OSC.
	if (m_dataBase->getDecorateStream())
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/r");
		*m_outPacketStream << iisuData.r;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/g");
		*m_outPacketStream << iisuData.g;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/b");
		*m_outPacketStream << iisuData.b;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/a");
		*m_outPacketStream << iisuData.a;
		*m_outPacketStream << OscEndMessage();
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);
		*m_outPacketStream << iisuData.r << iisuData.g << iisuData.b << iisuData.a;
		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(EnumPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Enum>* iisuDataHandle = static_cast<SK::DataHandle<SK::Enum>*>(m_iisuDataHandle);
	const SK::Enum& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: OscPack cannot stream uint32, hence we stream the data as int32 and clamp numbers above INT32_MAX.
	int32_t value = iisuData.value > INT32_MAX ? (int32_t)INT32_MAX : (int32_t)iisuData.value; // Enum is actually a uint32_t.
	*m_outPacketStream << OscBeginMessage(m_fullOscPath);
	*m_outPacketStream << value;
	*m_outPacketStream << OscEndMessage();
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(FramePathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Frame>* iisuDataHandle = static_cast<SK::DataHandle<SK::Frame>*>(m_iisuDataHandle);
	const SK::Frame& iisuData = iisuDataHandle->get();

	// Send via OSC.
	if (m_dataBase->getDecorateStream())
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/quat/w");
		*m_outPacketStream << iisuData.m_quat.w;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/quat/x");
		*m_outPacketStream << iisuData.m_quat.x;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/quat/y");
		*m_outPacketStream << iisuData.m_quat.y;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/quat/z");
		*m_outPacketStream << iisuData.m_quat.z;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/pos/x");
		*m_outPacketStream << iisuData.m_pos.x;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/pos/y");
		*m_outPacketStream << iisuData.m_pos.y;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/pos/z");
		*m_outPacketStream << iisuData.m_pos.z;
		*m_outPacketStream << OscEndMessage();
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);
		*m_outPacketStream << iisuData.m_quat.w << iisuData.m_quat.x << iisuData.m_quat.y << iisuData.m_quat.z
						   << iisuData.m_pos.x << iisuData.m_pos.y << iisuData.m_pos.z;
		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Matrix3PathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Matrix3>* iisuDataHandle = static_cast<SK::DataHandle<SK::Matrix3>*>(m_iisuDataHandle);
	const SK::Matrix3& iisuData = iisuDataHandle->get();

	// Send via OSC.
	if (m_dataBase->getDecorateStream())
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/xx");
		*m_outPacketStream << iisuData._11;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/xy");
		*m_outPacketStream << iisuData._12;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/xz");
		*m_outPacketStream << iisuData._13;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/yx");
		*m_outPacketStream << iisuData._21;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/yy");
		*m_outPacketStream << iisuData._22;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/yz");
		*m_outPacketStream << iisuData._23;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/zx");
		*m_outPacketStream << iisuData._31;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/zy");
		*m_outPacketStream << iisuData._32;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/zz");
		*m_outPacketStream << iisuData._33;
		*m_outPacketStream << OscEndMessage();
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);
		*m_outPacketStream << iisuData._11 << iisuData._12 << iisuData._13
						   << iisuData._21 << iisuData._22 << iisuData._23
						   << iisuData._31 << iisuData._32 << iisuData._33;
		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Matrix4PathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Matrix4>* iisuDataHandle = static_cast<SK::DataHandle<SK::Matrix4>*>(m_iisuDataHandle);
	const SK::Matrix4& iisuData = iisuDataHandle->get();

	// Send via OSC.
	if (m_dataBase->getDecorateStream())
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/xx");
		*m_outPacketStream << iisuData._11;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/xy");
		*m_outPacketStream << iisuData._12;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/xz");
		*m_outPacketStream << iisuData._13;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/xw");
		*m_outPacketStream << iisuData._14;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/yx");
		*m_outPacketStream << iisuData._21;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/yy");
		*m_outPacketStream << iisuData._22;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/yz");
		*m_outPacketStream << iisuData._23;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/yw");
		*m_outPacketStream << iisuData._24;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/zx");
		*m_outPacketStream << iisuData._31;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/zy");
		*m_outPacketStream << iisuData._32;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/zz");
		*m_outPacketStream << iisuData._33;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/zw");
		*m_outPacketStream << iisuData._34;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/wx");
		*m_outPacketStream << iisuData._41;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/wy");
		*m_outPacketStream << iisuData._42;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/wz");
		*m_outPacketStream << iisuData._43;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/ww");
		*m_outPacketStream << iisuData._44;
		*m_outPacketStream << OscEndMessage();
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);
		*m_outPacketStream << iisuData._11 << iisuData._12 << iisuData._13 << iisuData._14
						   << iisuData._21 << iisuData._22 << iisuData._23 << iisuData._24
						   << iisuData._31 << iisuData._32 << iisuData._33 << iisuData._34
						   << iisuData._41 << iisuData._42 << iisuData._43 << iisuData._44;
		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(QuatPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Quaternion>* iisuDataHandle = static_cast<SK::DataHandle<SK::Quaternion>*>(m_iisuDataHandle);
	const SK::Quaternion& iisuData = iisuDataHandle->get();

	// Send via OSC.
	if (m_dataBase->getDecorateStream())
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/w");
		*m_outPacketStream << iisuData.w;
		*m_outPacketStream << OscEndMessage();

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
		*m_outPacketStream << iisuData.w << iisuData.x << iisuData.y << iisuData.z;
		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(StringPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::String>* iisuDataHandle = static_cast<SK::DataHandle<SK::String>*>(m_iisuDataHandle);
	const SK::String& iisuData = iisuDataHandle->get();

	// Send via OSC.
	*m_outPacketStream << OscBeginMessage(m_fullOscPath);
	*m_outPacketStream << iisuData.ptr();
	*m_outPacketStream << OscEndMessage();
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Vector2PathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Vector2>* iisuDataHandle = static_cast<SK::DataHandle<SK::Vector2>*>(m_iisuDataHandle);
	const SK::Vector2& iisuData = iisuDataHandle->get();

	// Send via OSC.
	if (m_dataBase->getDecorateStream())
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/x");
		*m_outPacketStream << iisuData.x;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/y");
		*m_outPacketStream << iisuData.y;
		*m_outPacketStream << OscEndMessage();
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);
		*m_outPacketStream << iisuData.x << iisuData.y;
		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Vector2iPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Vector2i>* iisuDataHandle = static_cast<SK::DataHandle<SK::Vector2i>*>(m_iisuDataHandle);
	const SK::Vector2i& iisuData = iisuDataHandle->get();

	// Send via OSC.
	if (m_dataBase->getDecorateStream())
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/x");
		*m_outPacketStream << iisuData.x;
		*m_outPacketStream << OscEndMessage();

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/y");
		*m_outPacketStream << iisuData.y;
		*m_outPacketStream << OscEndMessage();
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);
		*m_outPacketStream << iisuData.x << iisuData.y;
		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Vector3PathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Vector3>* iisuDataHandle = static_cast<SK::DataHandle<SK::Vector3>*>(m_iisuDataHandle);
	const SK::Vector3& iisuData = iisuDataHandle->get();

	// Send via OSC.
	if (m_dataBase->getDecorateStream())
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
void IisuReaderOscSender::visit(Vector4PathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Vector4>* iisuDataHandle = static_cast<SK::DataHandle<SK::Vector4>*>(m_iisuDataHandle);
	const SK::Vector4& iisuData = iisuDataHandle->get();

	// Send via OSC.
	if (m_dataBase->getDecorateStream())
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

		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/w");
		*m_outPacketStream << iisuData.w;
		*m_outPacketStream << OscEndMessage();
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);
		*m_outPacketStream << iisuData.x << iisuData.y << iisuData.z << iisuData.w;
		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(BoolArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<bool> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<bool> >*>(m_iisuDataHandle);
	const SK::Array<bool>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath);
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
void IisuReaderOscSender::visit(CharArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<char> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<char> >*>(m_iisuDataHandle);
	const SK::Array<char>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath);
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
void IisuReaderOscSender::visit(FloatArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<float> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<float> >*>(m_iisuDataHandle);
	const SK::Array<float>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath);
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
void IisuReaderOscSender::visit(Int8ArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<int8_t> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<int8_t> >*>(m_iisuDataHandle);
	const SK::Array<int8_t>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath);
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
void IisuReaderOscSender::visit(Int16ArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<int16_t> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<int16_t> >*>(m_iisuDataHandle);
	const SK::Array<int16_t>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath);
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
}//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Int32ArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<int32_t> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<int32_t> >*>(m_iisuDataHandle);
	const SK::Array<int32_t>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath);
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
}//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Int64ArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<int64_t> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<int64_t> >*>(m_iisuDataHandle);
	const SK::Array<int64_t>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath);
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
}//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(UInt8ArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<uint8_t> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<uint8_t> >*>(m_iisuDataHandle);
	const SK::Array<uint8_t>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath);
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
}//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(UInt16ArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<uint16_t> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<uint16_t> >*>(m_iisuDataHandle);
	const SK::Array<uint16_t>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath);
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
}//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(UInt32ArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<uint32_t> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<uint32_t> >*>(m_iisuDataHandle);
	const SK::Array<uint32_t>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			// NOTE: OscPack cannot stream uint32, hence we stream the data as int32 and clamp numbers above INT32_MAX.
			int32_t value = iisuData[i] > INT32_MAX ? (int32_t)INT32_MAX : (int32_t)iisuData[i];
			*m_outPacketStream << OscBeginMessage(messagePath);
			*m_outPacketStream << value;
			*m_outPacketStream << OscEndMessage();
		}
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);

		// Size and data in a raw.
		// NOTE: OscPack cannot stream uint32, hence we stream the data as int32 and clamp numbers above INT32_MAX.
		*m_outPacketStream << (int)iisuData.size();
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			int32_t value = iisuData[i] > INT32_MAX ? (int32_t)INT32_MAX : (int32_t)iisuData[i];
			*m_outPacketStream << value;
		}

		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(UInt64ArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<uint64_t> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<uint64_t> >*>(m_iisuDataHandle);
	const SK::Array<uint64_t>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			// NOTE: OscPack cannot stream uint64, hence we stream the data as int64 and clamp numbers above INT64_MAX.
			int64_t value = iisuData[i] > INT64_MAX ? (int64_t)INT64_MAX : (int64_t)iisuData[i];
			*m_outPacketStream << OscBeginMessage(messagePath);
			*m_outPacketStream << value;
			*m_outPacketStream << OscEndMessage();
		}
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);

		// Size and data in a raw.
		// NOTE: OscPack cannot stream uint64, hence we stream the data as int64 and clamp numbers above INT64_MAX.
		*m_outPacketStream << (int)iisuData.size();
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			int64_t value = iisuData[i] > INT64_MAX ? (int64_t)INT64_MAX : (int64_t)iisuData[i];
			*m_outPacketStream << value;
		}

		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Color4cArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<SK::Color4c> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<SK::Color4c> >*>(m_iisuDataHandle);
	const SK::Array<SK::Color4c>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath + "/r");
			*m_outPacketStream << iisuData[i].r;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/g");
			*m_outPacketStream << iisuData[i].g;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/b");
			*m_outPacketStream << iisuData[i].b;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/a");
			*m_outPacketStream << iisuData[i].a;
			*m_outPacketStream << OscEndMessage();
		}
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);

		// Size and data in a raw.
		*m_outPacketStream << (int)iisuData.size();
		for (uint i = 0; i < iisuData.size(); ++i)
			*m_outPacketStream << iisuData[i].r << iisuData[i].g << iisuData[i].b << iisuData[i].a;

		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Color4fArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<SK::Color4f> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<SK::Color4f> >*>(m_iisuDataHandle);
	const SK::Array<SK::Color4f>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath + "/r");
			*m_outPacketStream << iisuData[i].r;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/g");
			*m_outPacketStream << iisuData[i].g;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/b");
			*m_outPacketStream << iisuData[i].b;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/a");
			*m_outPacketStream << iisuData[i].a;
			*m_outPacketStream << OscEndMessage();
		}
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);

		// Size and data in a raw.
		*m_outPacketStream << (int)iisuData.size();
		for (uint i = 0; i < iisuData.size(); ++i)
			*m_outPacketStream << iisuData[i].r << iisuData[i].g << iisuData[i].b << iisuData[i].a;

		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(EnumArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<SK::Enum> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<SK::Enum> >*>(m_iisuDataHandle);
	const SK::Array<SK::Enum>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			// NOTE: OscPack cannot stream uint32, hence we stream the data as int32 and clamp numbers above INT32_MAX.
			int32_t value = iisuData[i].value > INT32_MAX ? (int32_t)INT32_MAX : (int32_t)iisuData[i].value; // Enum is actually a uint32_t.
			*m_outPacketStream << OscBeginMessage(messagePath);
			*m_outPacketStream << value;
			*m_outPacketStream << OscEndMessage();
		}
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);

		// Size and data in a raw.
		// NOTE: OscPack cannot stream uint32, hence we stream the data as int32 and clamp numbers above INT32_MAX.
		*m_outPacketStream << (int)iisuData.size();
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			int32_t value = iisuData[i].value > INT32_MAX ? (int32_t)INT32_MAX : (int32_t)iisuData[i].value; // Enum is actually a uint32_t.
			*m_outPacketStream << value;
		}

		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(FrameArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<SK::Frame> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<SK::Frame> >*>(m_iisuDataHandle);
	const SK::Array<SK::Frame>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath + "/quat/w");
			*m_outPacketStream << iisuData[i].m_quat.w;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/quat/x");
			*m_outPacketStream << iisuData[i].m_quat.x;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/quat/y");
			*m_outPacketStream << iisuData[i].m_quat.y;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/quat/z");
			*m_outPacketStream << iisuData[i].m_quat.z;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/pos/x");
			*m_outPacketStream << iisuData[i].m_pos.x;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/pos/y");
			*m_outPacketStream << iisuData[i].m_pos.y;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/pos/z");
			*m_outPacketStream << iisuData[i].m_pos.z;
			*m_outPacketStream << OscEndMessage();
		}
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);

		// Size and data in a raw.
		*m_outPacketStream << (int)iisuData.size();
		for (uint i = 0; i < iisuData.size(); ++i)
			*m_outPacketStream << iisuData[i].m_quat.w << iisuData[i].m_quat.x << iisuData[i].m_quat.y << iisuData[i].m_quat.z
							   << iisuData[i].m_pos.x << iisuData[i].m_pos.y << iisuData[i].m_pos.z;

		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Matrix3ArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<SK::Matrix3> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<SK::Matrix3> >*>(m_iisuDataHandle);
	const SK::Array<SK::Matrix3>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/xx");
			*m_outPacketStream << iisuData[i]._11;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/xy");
			*m_outPacketStream << iisuData[i]._12;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/xz");
			*m_outPacketStream << iisuData[i]._13;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/yx");
			*m_outPacketStream << iisuData[i]._21;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/yy");
			*m_outPacketStream << iisuData[i]._22;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/yz");
			*m_outPacketStream << iisuData[i]._23;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/zx");
			*m_outPacketStream << iisuData[i]._31;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/zy");
			*m_outPacketStream << iisuData[i]._32;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/zz");
			*m_outPacketStream << iisuData[i]._33;
			*m_outPacketStream << OscEndMessage();
		}
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);

		// Size and data in a raw.
		*m_outPacketStream << (int)iisuData.size();
		for (uint i = 0; i < iisuData.size(); ++i)
			*m_outPacketStream << iisuData[i]._11 << iisuData[i]._12 << iisuData[i]._13
							   << iisuData[i]._21 << iisuData[i]._22 << iisuData[i]._23
							   << iisuData[i]._31 << iisuData[i]._32 << iisuData[i]._33;

		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Matrix4ArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<SK::Matrix4> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<SK::Matrix4> >*>(m_iisuDataHandle);
	const SK::Array<SK::Matrix4>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/xx");
			*m_outPacketStream << iisuData[i]._11;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/xy");
			*m_outPacketStream << iisuData[i]._12;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/xz");
			*m_outPacketStream << iisuData[i]._13;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/xw");
			*m_outPacketStream << iisuData[i]._14;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/yx");
			*m_outPacketStream << iisuData[i]._21;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/yy");
			*m_outPacketStream << iisuData[i]._22;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/yz");
			*m_outPacketStream << iisuData[i]._23;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/yw");
			*m_outPacketStream << iisuData[i]._24;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/zx");
			*m_outPacketStream << iisuData[i]._31;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/zy");
			*m_outPacketStream << iisuData[i]._32;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/zz");
			*m_outPacketStream << iisuData[i]._33;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/zw");
			*m_outPacketStream << iisuData[i]._34;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/wx");
			*m_outPacketStream << iisuData[i]._41;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/wy");
			*m_outPacketStream << iisuData[i]._42;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/wz");
			*m_outPacketStream << iisuData[i]._43;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/ww");
			*m_outPacketStream << iisuData[i]._44;
			*m_outPacketStream << OscEndMessage();
		}
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);

		// Size and data in a raw.
		*m_outPacketStream << (int)iisuData.size();
		for (uint i = 0; i < iisuData.size(); ++i)
			*m_outPacketStream << iisuData[i]._11 << iisuData[i]._12 << iisuData[i]._13 << iisuData[i]._14
							   << iisuData[i]._21 << iisuData[i]._22 << iisuData[i]._23 << iisuData[i]._24
							   << iisuData[i]._31 << iisuData[i]._32 << iisuData[i]._33 << iisuData[i]._34
							   << iisuData[i]._41 << iisuData[i]._42 << iisuData[i]._43 << iisuData[i]._44;

		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(QuatArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<SK::Quaternion> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<SK::Quaternion> >*>(m_iisuDataHandle);
	const SK::Array<SK::Quaternion>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath + "/w");
			*m_outPacketStream << iisuData[i].w;
			*m_outPacketStream << OscEndMessage();

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
			*m_outPacketStream << iisuData[i].w << iisuData[i].x << iisuData[i].y << iisuData[i].z;

		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(StringArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<SK::String> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<SK::String> >*>(m_iisuDataHandle);
	const SK::Array<SK::String>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath);
			*m_outPacketStream << iisuData[i].ptr();
			*m_outPacketStream << OscEndMessage();
		}
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);

		// Size and data in a raw.
		*m_outPacketStream << (int)iisuData.size();
		for (uint i = 0; i < iisuData.size(); ++i)
			*m_outPacketStream << iisuData[i].ptr();

		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Vector2ArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<SK::Vector2> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<SK::Vector2> >*>(m_iisuDataHandle);
	const SK::Array<SK::Vector2>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath + "/x");
			*m_outPacketStream << iisuData[i].x;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/y");
			*m_outPacketStream << iisuData[i].y;
			*m_outPacketStream << OscEndMessage();
		}
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);

		// Size and data in a raw.
		*m_outPacketStream << (int)iisuData.size();
		for (uint i = 0; i < iisuData.size(); ++i)
			*m_outPacketStream << iisuData[i].x << iisuData[i].y;

		*m_outPacketStream << OscEndMessage();
	}
}

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Vector2iArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<SK::Vector2i> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<SK::Vector2i> >*>(m_iisuDataHandle);
	const SK::Array<SK::Vector2i>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath + "/x");
			*m_outPacketStream << iisuData[i].x;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/y");
			*m_outPacketStream << iisuData[i].y;
			*m_outPacketStream << OscEndMessage();
		}
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);

		// Size and data in a raw.
		*m_outPacketStream << (int)iisuData.size();
		for (uint i = 0; i < iisuData.size(); ++i)
			*m_outPacketStream << iisuData[i].x << iisuData[i].y;

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
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

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

//////////////////////////////////////////////////////////////////////////
void IisuReaderOscSender::visit(Vector4ArrayPathMap* typedPathMap)
{
	// Get the data from iisu.
	SK::DataHandle<SK::Array<SK::Vector4> >* iisuDataHandle = static_cast<SK::DataHandle<SK::Array<SK::Vector4> >*>(m_iisuDataHandle);
	const SK::Array<SK::Vector4>& iisuData = iisuDataHandle->get();

	// Send via OSC.
	// NOTE: an array can only stream decorated data if its size is SK::SkeletonEnum::_COUNT.
	if (m_dataBase->getDecorateStream() && iisuData.size() == SK::SkeletonEnum::_COUNT)
	{
		// Size.
		*m_outPacketStream << OscBeginMessage(m_fullOscPath + "/size");
		*m_outPacketStream << (int)iisuData.size();
		*m_outPacketStream << OscEndMessage();

		// Proper data.
		for (uint i = 0; i < iisuData.size(); ++i)
		{
			std::string messagePath = m_fullOscPath + std::string("/") + SK::SkeletonEnum::KeyPointsLabels[i].ptr();

			*m_outPacketStream << OscBeginMessage(messagePath + "/x");
			*m_outPacketStream << iisuData[i].x;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/y");
			*m_outPacketStream << iisuData[i].y;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/z");
			*m_outPacketStream << iisuData[i].z;
			*m_outPacketStream << OscEndMessage();

			*m_outPacketStream << OscBeginMessage(messagePath + "/w");
			*m_outPacketStream << iisuData[i].w;
			*m_outPacketStream << OscEndMessage();
		}
	}
	else
	{
		*m_outPacketStream << OscBeginMessage(m_fullOscPath);

		// Size and data in a raw.
		*m_outPacketStream << (int)iisuData.size();
		for (uint i = 0; i < iisuData.size(); ++i)
			*m_outPacketStream << iisuData[i].x << iisuData[i].y << iisuData[i].z << iisuData[i].w;

		*m_outPacketStream << OscEndMessage();
	}
}

} // namespace SK.