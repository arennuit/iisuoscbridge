#pragma once

namespace SK
{

//////////////////////////////////////////////////////////////////////////
/// \brief This is the base type for templated TypedPathMap factories.
struct BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath) = 0;
};

//////////////////////////////////////////////////////////////////////////
template<typename T>
struct TypedPathMapFactory : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{
		// Type is not handled.
		return 0 ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<bool> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new BoolPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<char> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new CharPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<float> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new FloatPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<int8_t> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Int8PathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<int16_t> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Int16PathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<int32_t> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Int32PathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<int64_t> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Int64PathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<uint8_t> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new UInt8PathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<uint16_t> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new UInt16PathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<uint32_t> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new UInt32PathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<uint64_t> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new UInt64PathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Color4c> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Color4cPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Color4f> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Color4fPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Enum> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new EnumPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Frame> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new FramePathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Matrix3> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Matrix3PathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Matrix4> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Matrix4PathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Quaternion> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new QuatPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::String> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new StringPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Vector2> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Vector2PathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Vector2i> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Vector2iPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Vector3> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Vector3PathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Vector4> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Vector4PathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<bool> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new BoolArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<char> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new CharArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<float> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new FloatArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<int8_t> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Int8ArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<int16_t> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Int16ArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<int32_t> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Int32ArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<int64_t> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Int64ArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<uint8_t> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new UInt8ArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<uint16_t> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new UInt16ArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<uint32_t> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new UInt32ArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<uint64_t> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new UInt64ArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<SK::Color4c> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Color4cArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<SK::Color4f> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Color4fArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<SK::Enum> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new EnumArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<SK::Frame> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new FrameArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<SK::Matrix3> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Matrix3ArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<SK::Matrix4> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Matrix4ArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<SK::Quaternion> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new QuatArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<SK::String> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new StringArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<SK::Vector2> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Vector2ArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<SK::Vector2i> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Vector2iArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<SK::Vector3> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Vector3ArrayPathMap(fullOscPath, iisuPath) ;
	};
};

//////////////////////////////////////////////////////////////////////////
template<>
struct TypedPathMapFactory<SK::Array<SK::Vector4> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Vector4ArrayPathMap(fullOscPath, iisuPath) ;
	};
};

} // namespace SK.