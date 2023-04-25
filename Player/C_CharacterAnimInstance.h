// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/C_FeetComponent.h"
#include "C_CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_API UC_CharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	UPROPERTY(BlueprintReadOnly)
		float Angle;

	UPROPERTY(BlueprintReadOnly)
		float Speed;
	
	UPROPERTY(BlueprintReadOnly)
		bool IsMoving;

	UPROPERTY(BlueprintReadOnly)
		FFeetData FeetData;

private:
	class ACharacter* player;

	class UC_FeetComponent* Feet;
};
