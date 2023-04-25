// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_StatusComponent.generated.h"

UENUM(BlueprintType)
enum class ECharacterSpeed : uint8
{
	STRAFE, WALK, RUN, SPRINT, MAX
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_PROJECT_API UC_StatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_StatusComponent();

	void SetMove();
	void SetStop();

	void SetSpeed(ECharacterSpeed InType);

	void HealthProcess(float Amount);
	void ManaProcess(float Amount);
	void StaminaProcess(float Amount);

	FORCEINLINE bool CanMove() { return bCanMove; }

	FORCEINLINE float GetCurrentHealth() { return Health; }
	FORCEINLINE float GetMaxHealth() { return MaxHealth; }

	FORCEINLINE float GetCurrentMana() { return Mana; }
	FORCEINLINE float GetMaxMana() { return MaxMana; }

	FORCEINLINE float GetCurrentStamina() { return Stamina; }
	FORCEINLINE float GetMaxStamina() { return MaxStamina; }

	FORCEINLINE float GetWalkSpeed() { return Speed[(int32)ECharacterSpeed::WALK]; }
	FORCEINLINE float GetRunSpeed() { return Speed[(int32)ECharacterSpeed::RUN]; }
	FORCEINLINE float GetSprintSpeed() { return Speed[(int32)ECharacterSpeed::SPRINT]; }

	FORCEINLINE bool IsStaminaCharging() { return bIsStaminaCharging; }
	FORCEINLINE void SetStaminaChargingState(bool bIsCharging) { bIsStaminaCharging = bIsCharging; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HealthWidget;
	
	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly)
		float MaxMana = 100.f;

	UPROPERTY(EditDefaultsOnly)
		float MaxStamina = 100.f;

	UPROPERTY(EditDefaultsOnly)
		float Speed[(int32)ECharacterSpeed::MAX] = { 100, 200, 400, 600 };

	bool bCanMove = true;

	float Health = 0.f;
	float Mana = 0.f;
	float Stamina = 0.f;

	bool bIsStaminaCharging = false;
};
