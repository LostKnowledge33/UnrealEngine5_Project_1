// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_BehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, Approach, Strafe, Skill, Action, Patrol, Hitted, Avoid, ArmsLength,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBehaviorTypeChanged, EBehaviorType, InPrevType, EBehaviorType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_PROJECT_API UC_BehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditAnywhere)
		FName BehaviorKey = "Behavior";

	UPROPERTY(EditAnywhere)
		FName PlayerKey = "Player";

	UPROPERTY(EditAnywhere)
		FName TargetKey = "Target";

	class UBlackboardComponent* Blackboard;

public:

	UPROPERTY(BlueprintAssignable)
		FBehaviorTypeChanged OnBehaviorTypeChanged;

public:	
	// Sets default values for this component's properties
	UC_BehaviorComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	class AC_Character* GetTargetPlayer();
	class ACharacter* GetTarget();

	void ChangeType(EBehaviorType InType);

	EBehaviorType GetType();

	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

	UFUNCTION(BlueprintPure)
		bool IsTypeMode(EBehaviorType InType);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
};
