// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/C_Character.h"
#include "C_Revenant.generated.h"


UCLASS()
class UE_PROJECT_API AC_Revenant : public AC_Character
{
	GENERATED_BODY()
	
private:
	AC_Revenant();

public:

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	void NormalAttack();

	//UPROPERTY(VisibleDefaultsOnly)
	FORCEINLINE int GetComboCount() { return iComboCount; }
	FORCEINLINE void ComboCountUp()
	{
		iComboCount++;
		iComboCount %= 3;
	}

	virtual void WeaponEnableCollision();

private:

	UPROPERTY(VisibleDefaultsOnly)
		class UAnimMontage* Attack;

	int iComboCount = 0;
};
