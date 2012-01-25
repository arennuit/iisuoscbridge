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
struct TypedPathMapFactory<int32_t> : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new Int32PathMap(fullOscPath, iisuPath) ;
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
struct TypedPathMapFactory<SK::Array<float> > : public BaseTypedPathMapFactory
{
	virtual TypedPathMap* create(const std::string& fullOscPath, const std::string& iisuPath)
	{ 
		return new FloatArrayPathMap(fullOscPath, iisuPath) ;
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

} // namespace SK.