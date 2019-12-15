#pragma once

// macro for singletone
#define DECL_SINGLETONE(Target) \
public: \
	static Target* Get(); \
private: \
	static Target* _instance;

#define IMPL_SINGLETONE(Target) \
Target* Target::Get() \
{ \
check(_instance); \
return _instance; \
} \
Target* Target::_instance = nullptr; 