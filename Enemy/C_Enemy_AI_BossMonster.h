// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/C_Enemy_AI.h"
#include "C_Enemy_AI_BossMonster.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_API AC_Enemy_AI_BossMonster : public AC_Enemy_AI
{
	GENERATED_BODY()

public:

	AC_Enemy_AI_BossMonster();

	UFUNCTION()
		void MyComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void MyComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void BeginPlay();
};
