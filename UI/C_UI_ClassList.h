// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_UI_ClassList.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChooseClass_Clicked);


USTRUCT(BlueprintType)
struct FUI_Class_Data
{
	GENERATED_BODY()

public:
	class UC_UI_ChooseClass* Class;
	FChooseClass_Clicked OnChooseClass_Clicked;
};


UCLASS()
class UE_PROJECT_API UC_UI_ClassList : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:

	void Clicked(FString InName);
	void Hovered(FString InName);
	void Unhovered(FString InName);

private:

	TArray<FUI_Class_Data> Datas;

};
