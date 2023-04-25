// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/C_Enemy.h"
#include "C_Enemy_AI.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_API AC_Enemy_AI : public AC_Enemy
{
	GENERATED_BODY()
	
public:

	AC_Enemy_AI();
	
	FORCEINLINE class UBehaviorTree* GetEnemyTree() { return EnemyTree; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }

private:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 1;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* EnemyTree;

	UPROPERTY(VisibleDefaultsOnly, Category = "AI")
		class UC_PatrolComponent* Patrol2;
};
