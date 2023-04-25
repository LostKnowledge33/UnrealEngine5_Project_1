// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "C_ActionData.generated.h"


USTRUCT(BlueprintType)
struct FActionData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float Power = 5.0f;

	UPROPERTY(EditAnywhere)
		float HitStop = 0.0f;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.0f;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bPawnControl = true;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* Effect;

	UPROPERTY(EditAnywhere)
		FTransform EffectTransform;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShakeBase> ShakeClass;
};

UCLASS()
class UE_PROJECT_API UC_ActionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FActionData> NormalAttackData;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FActionData> SkillAttackData;

public:
	void BeginPlay(class ACharacter* InOwnerChraracter, class UC_Action** OutAction);

};
