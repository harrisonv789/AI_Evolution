// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AI_Evolution/Public/ShipSpawner.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeShipSpawner() {}
// Cross Module References
	AI_EVOLUTION_API UClass* Z_Construct_UClass_AShipSpawner_NoRegister();
	AI_EVOLUTION_API UClass* Z_Construct_UClass_AShipSpawner();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_AI_Evolution();
	AI_EVOLUTION_API UClass* Z_Construct_UClass_ABoid_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	AI_EVOLUTION_API UClass* Z_Construct_UClass_AGasCloud_NoRegister();
// End Cross Module References
	void AShipSpawner::StaticRegisterNativesAShipSpawner()
	{
	}
	UClass* Z_Construct_UClass_AShipSpawner_NoRegister()
	{
		return AShipSpawner::StaticClass();
	}
	struct Z_Construct_UClass_AShipSpawner_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxShipCount_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MaxShipCount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HarvestShip_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_HarvestShip;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GasCloud_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_GasCloud;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AShipSpawner_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_AI_Evolution,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AShipSpawner_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "ShipSpawner.h" },
		{ "ModuleRelativePath", "Public/ShipSpawner.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AShipSpawner_Statics::NewProp_MaxShipCount_MetaData[] = {
		{ "Category", "Entities" },
		{ "ModuleRelativePath", "Public/ShipSpawner.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AShipSpawner_Statics::NewProp_MaxShipCount = { "MaxShipCount", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AShipSpawner, MaxShipCount), METADATA_PARAMS(Z_Construct_UClass_AShipSpawner_Statics::NewProp_MaxShipCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AShipSpawner_Statics::NewProp_MaxShipCount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AShipSpawner_Statics::NewProp_HarvestShip_MetaData[] = {
		{ "Category", "Entities" },
		{ "ModuleRelativePath", "Public/ShipSpawner.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AShipSpawner_Statics::NewProp_HarvestShip = { "HarvestShip", nullptr, (EPropertyFlags)0x0014000000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AShipSpawner, HarvestShip), Z_Construct_UClass_ABoid_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AShipSpawner_Statics::NewProp_HarvestShip_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AShipSpawner_Statics::NewProp_HarvestShip_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AShipSpawner_Statics::NewProp_GasCloud_MetaData[] = {
		{ "Category", "Entities" },
		{ "ModuleRelativePath", "Public/ShipSpawner.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AShipSpawner_Statics::NewProp_GasCloud = { "GasCloud", nullptr, (EPropertyFlags)0x0014000000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AShipSpawner, GasCloud), Z_Construct_UClass_AGasCloud_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AShipSpawner_Statics::NewProp_GasCloud_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AShipSpawner_Statics::NewProp_GasCloud_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AShipSpawner_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AShipSpawner_Statics::NewProp_MaxShipCount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AShipSpawner_Statics::NewProp_HarvestShip,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AShipSpawner_Statics::NewProp_GasCloud,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AShipSpawner_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AShipSpawner>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AShipSpawner_Statics::ClassParams = {
		&AShipSpawner::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AShipSpawner_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AShipSpawner_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AShipSpawner_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AShipSpawner_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AShipSpawner()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AShipSpawner_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AShipSpawner, 435860809);
	template<> AI_EVOLUTION_API UClass* StaticClass<AShipSpawner>()
	{
		return AShipSpawner::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AShipSpawner(Z_Construct_UClass_AShipSpawner, &AShipSpawner::StaticClass, TEXT("/Script/AI_Evolution"), TEXT("AShipSpawner"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AShipSpawner);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
