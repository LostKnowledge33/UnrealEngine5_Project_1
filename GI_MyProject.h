// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_MyProject.generated.h"


UCLASS()
class UE_PROJECT_API UGI_MyProject : public UGameInstance
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadWrite)
		int32 CharacterIndex = 0;


public:

	UGI_MyProject();

	FORCEINLINE int32 GetCharacterIndex() { return CharacterIndex; }

};
