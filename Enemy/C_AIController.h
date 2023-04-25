// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_AIController.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_API AC_AIController : public AAIController
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere)
		float BehaviorRange = 150.f;

	UPROPERTY(EditAnywhere)
		bool bDrawDebug = true;

	UPROPERTY(EditAnywhere)
		float AdjustCircleHeight = 50;

	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;

	UPROPERTY(VisibleDefaultsOnly)
		class UC_BehaviorComponent* Behavior;

	class AC_Enemy_AI* OwnerEnemy;
	class AC_Character* TargetPlayer;
	class UAISenseConfig_Sight* Sight;
	class UBlackboardComponent* Blackboard;

public:

	UPROPERTY(BlueprintReadWrite)
		float SightRange = 800.f;

	UPROPERTY(BlueprintReadWrite)
		bool bIsSightDebug = false;

public:

	AC_AIController();

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE float GetBehaviorRange() { return BehaviorRange; }

	float GetSightRadius();

	FORCEINLINE class AC_Character* GetTargetPlayer() {	return TargetPlayer; }

	void SetSightRange(float SightRadius, float LoseRadius, float Angle);

	UFUNCTION(BlueprintImplementableEvent)
		void PlayEngage();

protected:

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:

	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdateActors);

};
