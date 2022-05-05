// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FHitResult;
#ifdef AI_EVOLUTION_Boid_generated_h
#error "Boid.generated.h already included, missing '#pragma once' in Boid.h"
#endif
#define AI_EVOLUTION_Boid_generated_h

#define AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_SPARSE_DATA
#define AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnHitboxOverlapEnd); \
	DECLARE_FUNCTION(execOnHitboxOverlapBegin);


#define AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHitboxOverlapEnd); \
	DECLARE_FUNCTION(execOnHitboxOverlapBegin);


#define AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesABoid(); \
	friend struct Z_Construct_UClass_ABoid_Statics; \
public: \
	DECLARE_CLASS(ABoid, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/AI_Evolution"), NO_API) \
	DECLARE_SERIALIZER(ABoid)


#define AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_INCLASS \
private: \
	static void StaticRegisterNativesABoid(); \
	friend struct Z_Construct_UClass_ABoid_Statics; \
public: \
	DECLARE_CLASS(ABoid, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/AI_Evolution"), NO_API) \
	DECLARE_SERIALIZER(ABoid)


#define AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ABoid(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ABoid) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABoid); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABoid); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ABoid(ABoid&&); \
	NO_API ABoid(const ABoid&); \
public:


#define AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ABoid(ABoid&&); \
	NO_API ABoid(const ABoid&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABoid); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABoid); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ABoid)


#define AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_PRIVATE_PROPERTY_OFFSET
#define AI_Evolution_Source_AI_Evolution_Public_Boid_h_13_PROLOG
#define AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_PRIVATE_PROPERTY_OFFSET \
	AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_SPARSE_DATA \
	AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_RPC_WRAPPERS \
	AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_INCLASS \
	AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_PRIVATE_PROPERTY_OFFSET \
	AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_SPARSE_DATA \
	AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_INCLASS_NO_PURE_DECLS \
	AI_Evolution_Source_AI_Evolution_Public_Boid_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> AI_EVOLUTION_API UClass* StaticClass<class ABoid>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID AI_Evolution_Source_AI_Evolution_Public_Boid_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
