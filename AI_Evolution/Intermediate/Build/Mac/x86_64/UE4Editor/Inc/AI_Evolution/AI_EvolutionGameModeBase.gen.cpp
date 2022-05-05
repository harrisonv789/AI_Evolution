// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AI_Evolution/Public/AI_EvolutionGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAI_EvolutionGameModeBase() {}
// Cross Module References
	AI_EVOLUTION_API UClass* Z_Construct_UClass_AAI_EvolutionGameModeBase_NoRegister();
	AI_EVOLUTION_API UClass* Z_Construct_UClass_AAI_EvolutionGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_AI_Evolution();
// End Cross Module References
	void AAI_EvolutionGameModeBase::StaticRegisterNativesAAI_EvolutionGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_AAI_EvolutionGameModeBase_NoRegister()
	{
		return AAI_EvolutionGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AAI_EvolutionGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AAI_EvolutionGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_AI_Evolution,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAI_EvolutionGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "AI_EvolutionGameModeBase.h" },
		{ "ModuleRelativePath", "Public/AI_EvolutionGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AAI_EvolutionGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAI_EvolutionGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AAI_EvolutionGameModeBase_Statics::ClassParams = {
		&AAI_EvolutionGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AAI_EvolutionGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AAI_EvolutionGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AAI_EvolutionGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AAI_EvolutionGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AAI_EvolutionGameModeBase, 4191253811);
	template<> AI_EVOLUTION_API UClass* StaticClass<AAI_EvolutionGameModeBase>()
	{
		return AAI_EvolutionGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AAI_EvolutionGameModeBase(Z_Construct_UClass_AAI_EvolutionGameModeBase, &AAI_EvolutionGameModeBase::StaticClass, TEXT("/Script/AI_Evolution"), TEXT("AAI_EvolutionGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AAI_EvolutionGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
