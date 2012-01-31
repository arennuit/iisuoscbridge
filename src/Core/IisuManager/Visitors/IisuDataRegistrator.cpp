#include "IisuDataRegistrator.h"
#include "SDK/iisuSDK.h"
#include "Core/IisuManager/TypedPathMap/TypedPathMap.h"
#include "LogSystem/Logger.h"

namespace SK
{

//////////////////////////////////////////////////////////////////////////
IisuDataRegistrator::IisuDataRegistrator(SK::Device* device, std::vector<SK::IIisuDataExtractor*>& dataHandles) :
	TypedPathMapVisitor(),
	m_device(device),
	m_dataHandles(dataHandles)
{
	assert(device);
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(TypedPathMap* typedPathMap)
{
	assert(typedPathMap);

	// No iisu data is associated to a plain TypedPathMap.
	m_dataHandles.push_back(0);
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(BoolPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<bool> handleTmp = m_device->registerDataHandle<bool>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<bool>* handle = new SK::DataHandle<bool>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'bool\': " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(CharPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<char> handleTmp = m_device->registerDataHandle<char>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<char>* handle = new SK::DataHandle<char>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'char\': " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(FloatPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<float> handleTmp = m_device->registerDataHandle<float>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<float>* handle = new SK::DataHandle<float>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'float\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Int8PathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<int8_t> handleTmp = m_device->registerDataHandle<int8_t>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<int8_t>* handle = new SK::DataHandle<int8_t>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'int8_t\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Int16PathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<int16_t> handleTmp = m_device->registerDataHandle<int16_t>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<int16_t>* handle = new SK::DataHandle<int16_t>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'int16_t\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Int32PathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<int32_t> handleTmp = m_device->registerDataHandle<int32_t>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<int32_t>* handle = new SK::DataHandle<int32_t>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'int32_t\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Int64PathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<int64_t> handleTmp = m_device->registerDataHandle<int64_t>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<int64_t>* handle = new SK::DataHandle<int64_t>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'int64_t\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(UInt8PathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<uint8_t> handleTmp = m_device->registerDataHandle<uint8_t>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<uint8_t>* handle = new SK::DataHandle<uint8_t>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'uint_8t\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(UInt16PathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<uint16_t> handleTmp = m_device->registerDataHandle<uint16_t>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<uint16_t>* handle = new SK::DataHandle<uint16_t>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'uint16_t\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(UInt32PathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<uint32_t> handleTmp = m_device->registerDataHandle<uint32_t>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<uint32_t>* handle = new SK::DataHandle<uint32_t>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'uint32_t\' : " + typedPathMap->m_iisuPath + ".";
	SK_LOGGER(LOG_WARNING) << "    ->WARNING: uint32_t streams as capped int32_t.";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(UInt64PathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<uint64_t> handleTmp = m_device->registerDataHandle<uint64_t>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<uint64_t>* handle = new SK::DataHandle<uint64_t>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'uint64_t\' : " + typedPathMap->m_iisuPath + ".";
	SK_LOGGER(LOG_WARNING) << "    ->WARNING: uint64_t streams as capped int64_t.";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Color4cPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Color4c> handleTmp = m_device->registerDataHandle<SK::Color4c>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Color4c>* handle = new SK::DataHandle<SK::Color4c>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Color4c\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Color4fPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Color4f> handleTmp = m_device->registerDataHandle<SK::Color4f>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Color4f>* handle = new SK::DataHandle<SK::Color4f>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Color4f\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(EnumPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Enum> handleTmp = m_device->registerDataHandle<SK::Enum>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Enum>* handle = new SK::DataHandle<SK::Enum>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Enum\' : " + typedPathMap->m_iisuPath + ".";
	SK_LOGGER(LOG_WARNING) << "    ->WARNING: Enum streams as capped int32_t.";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(FramePathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Frame> handleTmp = m_device->registerDataHandle<SK::Frame>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Frame>* handle = new SK::DataHandle<SK::Frame>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Frame\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Matrix3PathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Matrix3> handleTmp = m_device->registerDataHandle<SK::Matrix3>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Matrix3>* handle = new SK::DataHandle<SK::Matrix3>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Matrix3\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Matrix4PathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Matrix4> handleTmp = m_device->registerDataHandle<SK::Matrix4>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Matrix4>* handle = new SK::DataHandle<SK::Matrix4>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Matrix4\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(QuatPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Quaternion> handleTmp = m_device->registerDataHandle<SK::Quaternion>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Quaternion>* handle = new SK::DataHandle<SK::Quaternion>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Quaternion\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(StringPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::String> handleTmp = m_device->registerDataHandle<SK::String>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::String>* handle = new SK::DataHandle<SK::String>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'String\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector2PathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Vector2> handleTmp = m_device->registerDataHandle<SK::Vector2>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Vector2>* handle = new SK::DataHandle<SK::Vector2>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Vector2\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector2iPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Vector2i> handleTmp = m_device->registerDataHandle<SK::Vector2i>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Vector2i>* handle = new SK::DataHandle<SK::Vector2i>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Vector2i\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector3PathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Vector3> handleTmp = m_device->registerDataHandle<SK::Vector3>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Vector3>* handle = new SK::DataHandle<SK::Vector3>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Vector3\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector4PathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Vector4> handleTmp = m_device->registerDataHandle<SK::Vector4>(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Vector4>* handle = new SK::DataHandle<SK::Vector4>();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Vector4\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(BoolArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<bool> > handleTmp = m_device->registerDataHandle<SK::Array<bool> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<bool> >* handle = new SK::DataHandle<SK::Array<bool> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'bool array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(CharArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<char> > handleTmp = m_device->registerDataHandle<SK::Array<char> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<char> >* handle = new SK::DataHandle<SK::Array<char> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'char array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(FloatArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<float> > handleTmp = m_device->registerDataHandle<SK::Array<float> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<float> >* handle = new SK::DataHandle<SK::Array<float> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'float array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Int8ArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<int8_t> > handleTmp = m_device->registerDataHandle<SK::Array<int8_t> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<int8_t> >* handle = new SK::DataHandle<SK::Array<int8_t> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'int8_t array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Int16ArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<int16_t> > handleTmp = m_device->registerDataHandle<SK::Array<int16_t> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<int16_t> >* handle = new SK::DataHandle<SK::Array<int16_t> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'int16_t array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Int32ArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<int32_t> > handleTmp = m_device->registerDataHandle<SK::Array<int32_t> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<int32_t> >* handle = new SK::DataHandle<SK::Array<int32_t> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'int32_t array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Int64ArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<int64_t> > handleTmp = m_device->registerDataHandle<SK::Array<int64_t> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<int64_t> >* handle = new SK::DataHandle<SK::Array<int64_t> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'int64_t array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(UInt8ArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<uint8_t> > handleTmp = m_device->registerDataHandle<SK::Array<uint8_t> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<uint8_t> >* handle = new SK::DataHandle<SK::Array<uint8_t> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'uint8_t array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(UInt16ArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<uint16_t> > handleTmp = m_device->registerDataHandle<SK::Array<uint16_t> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<uint16_t> >* handle = new SK::DataHandle<SK::Array<uint16_t> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'uint16_t array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(UInt32ArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<uint32_t> > handleTmp = m_device->registerDataHandle<SK::Array<uint32_t> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<uint32_t> >* handle = new SK::DataHandle<SK::Array<uint32_t> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'uint32_t array\' : " + typedPathMap->m_iisuPath + ".";
	SK_LOGGER(LOG_WARNING) << "    ->WARNING: uint32_t streams as capped int32_t.";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(UInt64ArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<uint64_t> > handleTmp = m_device->registerDataHandle<SK::Array<uint64_t> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<uint64_t> >* handle = new SK::DataHandle<SK::Array<uint64_t> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'uint64_t array\' : " + typedPathMap->m_iisuPath + ".";
	SK_LOGGER(LOG_WARNING) << "    ->WARNING: uint64_t streams as capped int64_t.";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Color4cArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::Color4c> > handleTmp = m_device->registerDataHandle<SK::Array<SK::Color4c> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<SK::Color4c> >* handle = new SK::DataHandle<SK::Array<SK::Color4c> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Color4c array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Color4fArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::Color4f> > handleTmp = m_device->registerDataHandle<SK::Array<SK::Color4f> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<SK::Color4f> >* handle = new SK::DataHandle<SK::Array<SK::Color4f> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Color4f array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(EnumArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::Enum> > handleTmp = m_device->registerDataHandle<SK::Array<SK::Enum> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<SK::Enum> >* handle = new SK::DataHandle<SK::Array<SK::Enum> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Enum array\' : " + typedPathMap->m_iisuPath + ".";
	SK_LOGGER(LOG_WARNING) << "    ->WARNING: Enum streams as capped int32_t.";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(FrameArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::Frame> > handleTmp = m_device->registerDataHandle<SK::Array<SK::Frame> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<SK::Frame> >* handle = new SK::DataHandle<SK::Array<SK::Frame> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Frame array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Matrix3ArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::Matrix3> > handleTmp = m_device->registerDataHandle<SK::Array<SK::Matrix3> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<SK::Matrix3> >* handle = new SK::DataHandle<SK::Array<SK::Matrix3> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Matrix3 array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Matrix4ArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::Matrix4> > handleTmp = m_device->registerDataHandle<SK::Array<SK::Matrix4> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<SK::Matrix4> >* handle = new SK::DataHandle<SK::Array<SK::Matrix4> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Matrix4 array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(QuatArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::Quaternion> > handleTmp = m_device->registerDataHandle<SK::Array<SK::Quaternion> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<SK::Quaternion> >* handle = new SK::DataHandle<SK::Array<SK::Quaternion> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Quaternion array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(StringArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::String> > handleTmp = m_device->registerDataHandle<SK::Array<SK::String> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<SK::String> >* handle = new SK::DataHandle<SK::Array<SK::String> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'String array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector2ArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::Vector2> > handleTmp = m_device->registerDataHandle<SK::Array<SK::Vector2> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<SK::Vector2> >* handle = new SK::DataHandle<SK::Array<SK::Vector2> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Vector2 array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector2iArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::Vector2i> > handleTmp = m_device->registerDataHandle<SK::Array<SK::Vector2i> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<SK::Vector2i> >* handle = new SK::DataHandle<SK::Array<SK::Vector2i> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Vector2i array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector3ArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::Vector3> > handleTmp = m_device->registerDataHandle<SK::Array<SK::Vector3> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<SK::Vector3> >* handle = new SK::DataHandle<SK::Array<SK::Vector3> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Vector3 array\' : " + typedPathMap->m_iisuPath + ".";
}

//////////////////////////////////////////////////////////////////////////
void IisuDataRegistrator::visit(Vector4ArrayPathMap* typedPathMap)
{
	assert(typedPathMap);
	assert(m_device);

	// Register iisu path.
	SK::DataHandle<SK::Array<SK::Vector4> > handleTmp = m_device->registerDataHandle<SK::Array<SK::Vector4> >(typedPathMap->m_iisuPath.c_str());
	if (!handleTmp.isValid())
	{
		SK_LOGGER(LOG_ERROR) << "Iisu handle registration problem: " + typedPathMap->m_iisuPath + ".";
		return;
	}

	SK::DataHandle<SK::Array<SK::Vector4> >* handle = new SK::DataHandle<SK::Array<SK::Vector4> >();
	if (!handle)
	{
		SK_LOGGER(LOG_ERROR) << "Could not instantiate data handle for path " + typedPathMap->m_iisuPath + ".";
		return;
	}
	*handle = handleTmp;

	m_dataHandles.push_back(handle);
	SK_LOGGER(LOG_INFO) << "Iisu data registered as \'Vector4 array\' : " + typedPathMap->m_iisuPath + ".";
}

} // namespace SK.