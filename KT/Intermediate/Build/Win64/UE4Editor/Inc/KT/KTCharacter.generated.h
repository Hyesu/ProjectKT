// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef KT_KTCharacter_generated_h
#error "KTCharacter.generated.h already included, missing '#pragma once' in KTCharacter.h"
#endif
#define KT_KTCharacter_generated_h

#define KT_Source_KT_KTCharacter_h_22_RPC_WRAPPERS
#define KT_Source_KT_KTCharacter_h_22_RPC_WRAPPERS_NO_PURE_DECLS
#define KT_Source_KT_KTCharacter_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAKTCharacter(); \
	friend struct Z_Construct_UClass_AKTCharacter_Statics; \
public: \
	DECLARE_CLASS(AKTCharacter, APaperCharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/KT"), NO_API) \
	DECLARE_SERIALIZER(AKTCharacter) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define KT_Source_KT_KTCharacter_h_22_INCLASS \
private: \
	static void StaticRegisterNativesAKTCharacter(); \
	friend struct Z_Construct_UClass_AKTCharacter_Statics; \
public: \
	DECLARE_CLASS(AKTCharacter, APaperCharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/KT"), NO_API) \
	DECLARE_SERIALIZER(AKTCharacter) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define KT_Source_KT_KTCharacter_h_22_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AKTCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AKTCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AKTCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AKTCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AKTCharacter(AKTCharacter&&); \
	NO_API AKTCharacter(const AKTCharacter&); \
public:


#define KT_Source_KT_KTCharacter_h_22_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AKTCharacter(AKTCharacter&&); \
	NO_API AKTCharacter(const AKTCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AKTCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AKTCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AKTCharacter)


#define KT_Source_KT_KTCharacter_h_22_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__SideViewCameraComponent() { return STRUCT_OFFSET(AKTCharacter, SideViewCameraComponent); } \
	FORCEINLINE static uint32 __PPO__CameraBoom() { return STRUCT_OFFSET(AKTCharacter, CameraBoom); } \
	FORCEINLINE static uint32 __PPO__RunningAnimation() { return STRUCT_OFFSET(AKTCharacter, RunningAnimation); } \
	FORCEINLINE static uint32 __PPO__IdleAnimation() { return STRUCT_OFFSET(AKTCharacter, IdleAnimation); }


#define KT_Source_KT_KTCharacter_h_19_PROLOG
#define KT_Source_KT_KTCharacter_h_22_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	KT_Source_KT_KTCharacter_h_22_PRIVATE_PROPERTY_OFFSET \
	KT_Source_KT_KTCharacter_h_22_RPC_WRAPPERS \
	KT_Source_KT_KTCharacter_h_22_INCLASS \
	KT_Source_KT_KTCharacter_h_22_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define KT_Source_KT_KTCharacter_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	KT_Source_KT_KTCharacter_h_22_PRIVATE_PROPERTY_OFFSET \
	KT_Source_KT_KTCharacter_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	KT_Source_KT_KTCharacter_h_22_INCLASS_NO_PURE_DECLS \
	KT_Source_KT_KTCharacter_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID KT_Source_KT_KTCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
