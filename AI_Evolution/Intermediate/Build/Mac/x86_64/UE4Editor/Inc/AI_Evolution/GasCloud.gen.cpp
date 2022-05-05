// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AI_Evolution/Public/GasCloud.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGasCloud() {}
// Cross Module References
	AI_EVOLUTION_API UClass* Z_Construct_UClass_AGasCloud_NoRegister();
	AI_EVOLUTION_API UClass* Z_Construct_UClass_AGasCloud();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_AI_Evolution();
	NIAGARA_API UClass* Z_Construct_UClass_UNiagaraSystem_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USphereComponent_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(AGasCloud::execRemoveGold)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=P_THIS->RemoveGold();
		P_NATIVE_END;
	}
	void AGasCloud::StaticRegisterNativesAGasCloud()
	{
		UClass* Class = AGasCloud::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "RemoveGold", &AGasCloud::execRemoveGold },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AGasCloud_RemoveGold_Statics
	{
		struct GasCloud_eventRemoveGold_Parms
		{
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_AGasCloud_RemoveGold_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GasCloud_eventRemoveGold_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AGasCloud_RemoveGold_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AGasCloud_RemoveGold_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AGasCloud_RemoveGold_Statics::Function_MetaDataParams[] = {
		{ "Comment", "//UPROPERTY(EditAnywhere) \n" },
		{ "ModuleRelativePath", "Public/GasCloud.h" },
		{ "ToolTip", "UPROPERTY(EditAnywhere)" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AGasCloud_RemoveGold_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AGasCloud, nullptr, "RemoveGold", nullptr, nullptr, sizeof(GasCloud_eventRemoveGold_Parms), Z_Construct_UFunction_AGasCloud_RemoveGold_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AGasCloud_RemoveGold_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AGasCloud_RemoveGold_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AGasCloud_RemoveGold_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AGasCloud_RemoveGold()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AGasCloud_RemoveGold_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AGasCloud_NoRegister()
	{
		return AGasCloud::StaticClass();
	}
	struct Z_Construct_UClass_AGasCloud_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GasCloudParticle_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_GasCloudParticle;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CloudHitBox_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CloudHitBox;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGasCloud_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_AI_Evolution,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AGasCloud_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AGasCloud_RemoveGold, "RemoveGold" }, // 2411063646
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGasCloud_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GasCloud.h" },
		{ "ModuleRelativePath", "Public/GasCloud.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGasCloud_Statics::NewProp_GasCloudParticle_MetaData[] = {
		{ "Category", "GasCloud" },
		{ "ModuleRelativePath", "Public/GasCloud.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGasCloud_Statics::NewProp_GasCloudParticle = { "GasCloudParticle", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGasCloud, GasCloudParticle), Z_Construct_UClass_UNiagaraSystem_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AGasCloud_Statics::NewProp_GasCloudParticle_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGasCloud_Statics::NewProp_GasCloudParticle_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGasCloud_Statics::NewProp_CloudHitBox_MetaData[] = {
		{ "Category", "GasCloud" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GasCloud.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGasCloud_Statics::NewProp_CloudHitBox = { "CloudHitBox", nullptr, (EPropertyFlags)0x0010000000080009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGasCloud, CloudHitBox), Z_Construct_UClass_USphereComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AGasCloud_Statics::NewProp_CloudHitBox_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGasCloud_Statics::NewProp_CloudHitBox_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AGasCloud_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGasCloud_Statics::NewProp_GasCloudParticle,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGasCloud_Statics::NewProp_CloudHitBox,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGasCloud_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGasCloud>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AGasCloud_Statics::ClassParams = {
		&AGasCloud::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AGasCloud_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AGasCloud_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AGasCloud_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AGasCloud_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AGasCloud()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AGasCloud_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AGasCloud, 2214680536);
	template<> AI_EVOLUTION_API UClass* StaticClass<AGasCloud>()
	{
		return AGasCloud::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AGasCloud(Z_Construct_UClass_AGasCloud, &AGasCloud::StaticClass, TEXT("/Script/AI_Evolution"), TEXT("AGasCloud"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGasCloud);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
