// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_UI_ChooseClass.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_API UC_UI_ChooseClass : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	
	UFUNCTION(BlueprintCallable)
		void Click();

	UFUNCTION(BlueprintCallable)
		void Hover();

	UFUNCTION(BlueprintCallable)
		void Unhover();

private:

	class UC_UI_ClassList* GetClassList();

};
