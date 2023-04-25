// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/C_ActionProcess.h"
#include "Player/C_ActionData.h"
#include "C_ActionProcess_BossMonster.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_API AC_ActionProcess_BossMonster : public AC_ActionProcess
{
	GENERATED_BODY()
	
public:

	AC_ActionProcess_BossMonster();

	virtual void DoAction() override;
	virtual void DoAction_Skill() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void ResetHittedArray() { HittedCharacters.Empty(); }

private:

	int32 normalAttackIndex = 0;

	TArray<ACharacter*> HittedCharacters;

	FActionData currentData;


};
