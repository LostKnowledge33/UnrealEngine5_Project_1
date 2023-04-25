// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_StateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	IDLE, ROLL, BACKSTEP, KNOCKBACK, ACTION, HITTED, STUN, DEAD, MAX
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_PROJECT_API UC_StateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_StateComponent();

	void SetIdleMode();
	void SetRollMode();
	void SetActionMode();
	void SetHittedMode();
	void SetDeadMode();
	void SetBackstepMode();
	void SetStunMode();

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsIdleMode() { return Type == EStateType::IDLE; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsRollMode() { return Type == EStateType::ROLL; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsActionMode() { return Type == EStateType::ACTION; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsHittedMode() { return Type == EStateType::HITTED; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsDeadMode() { return Type == EStateType::DEAD; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsBackStepMode() { return Type == EStateType::BACKSTEP; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsStunMode() { return Type == EStateType::STUN; }

	FORCEINLINE void SetType(EStateType InType) { Type = InType; }
	FORCEINLINE EStateType GetType() { return Type; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void ChangeType(EStateType InType);

public:	
	UPROPERTY(BlueprintAssignable)
		FStateTypeChanged OnStateTypeChanged;

private:
	EStateType Type;
		
};
