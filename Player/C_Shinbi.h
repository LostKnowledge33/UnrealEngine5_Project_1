// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/C_Character.h"
#include "C_Shinbi.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_API AC_Shinbi : public AC_Character
{
	GENERATED_BODY()
	
public:

	AC_Shinbi();

	UFUNCTION()
		void MyComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void MyComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void BeginPlay();

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

public:

	UPROPERTY(EditAnywhere)
		class UCapsuleComponent* WeaponComp;

};
