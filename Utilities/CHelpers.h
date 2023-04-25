#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

class UE_PROJECT_API CHelpers
{

public:
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"Succeeded");

		*OutObject = asset.Object;
	}

	template<typename T>
	static void GetClass(TSubclassOf<T>* OutObject, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"Succeeded");

		*OutObject = asset.Class;
	}

	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		T* obj = Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *InPath));
		verifyf(obj, L"Succeeded");

		*OutObject = obj;
	}

	template<typename T>
	static void CreateComponent(AActor* InActor, T** InComponent, FName InName, USceneComponent* InParent = nullptr)
	{
		*InComponent = InActor->CreateDefaultSubobject<T>(InName);

		if (InParent)
		{
			(*InComponent)->SetupAttachment(InParent);
		}
		else
		{
			InActor->SetRootComponent((*InComponent));
		}
	}

	template<typename T>
	static void CreateActorComponent(AActor* InActor, T** InComponent, FName InName)
	{
		*InComponent = InActor->CreateDefaultSubobject<T>(InName);
	}

	template<typename T>
	static T* GetComponent(AActor* InActor)
	{
		return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
	}

	template<typename T>
	static void FindActors(class UWorld* InWorld, TArray<T*>& OutActors)
	{
		OutActors.Empty();

		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(InWorld, T::StaticClass(), actors);

		for (AActor* actor : actors)
			OutActors.Add(Cast<T>(actor));
	}

	static void FPrintF(FString FileContent, FString SaveName = "DebugOutputLog.txt")
	{
		FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::GameSourceDir()) + SaveName;

		FFileHelper::SaveStringToFile(FileContent, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
	}
};