// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef AI_EVOLUTION_GasCloud_generated_h
#error "GasCloud.generated.h already included, missing '#pragma once' in GasCloud.h"
#endif
#define AI_EVOLUTION_GasCloud_generated_h

#define AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_SPARSE_DATA
#define AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execRemoveGold);


#define AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execRemoveGold);


#define AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAGasCloud(); \
	friend struct Z_Construct_UClass_AGasCloud_Statics; \
public: \
	DECLARE_CLASS(AGasCloud, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/AI_Evolution"), NO_API) \
	DECLARE_SERIALIZER(AGasCloud)


#define AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_INCLASS \
private: \
	static void StaticRegisterNativesAGasCloud(); \
	friend struct Z_Construct_UClass_AGasCloud_Statics; \
public: \
	DECLARE_CLASS(AGasCloud, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/AI_Evolution"), NO_API) \
	DECLARE_SERIALIZER(AGasCloud)


#define AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AGasCloud(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AGasCloud) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGasCloud); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGasCloud); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AGasCloud(AGasCloud&&); \
	NO_API AGasCloud(const AGasCloud&); \
public:


#define AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AGasCloud(AGasCloud&&); \
	NO_API AGasCloud(const AGasCloud&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AGasCloud); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AGasCloud); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AGasCloud)


#define AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_PRIVATE_PROPERTY_OFFSET
#define AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_11_PROLOG
#define AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_PRIVATE_PROPERTY_OFFSET \
	AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_SPARSE_DATA \
	AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_RPC_WRAPPERS \
	AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_INCLASS \
	AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_PRIVATE_PROPERTY_OFFSET \
	AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_SPARSE_DATA \
	AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_INCLASS_NO_PURE_DECLS \
	AI_Evolution_Source_AI_Evolution_Public_GasCloud_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> AI_EVOLUTION_API UClass* StaticClass<class AGasCloud>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID AI_Evolution_Source_AI_Evolution_Public_GasCloud_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
