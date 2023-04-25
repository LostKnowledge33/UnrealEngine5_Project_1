// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/C_StatusComponent.h"
#include "Global.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UC_StatusComponent::UC_StatusComponent()
{

}

void UC_StatusComponent::SetMove()
{
	bCanMove = true;
}

void UC_StatusComponent::SetStop()
{
	bCanMove = false;
}

void UC_StatusComponent::SetSpeed(ECharacterSpeed InType)
{
	UCharacterMovementComponent* movement = CHelpers::GetComponent<UCharacterMovementComponent>(GetOwner());

	movement->MaxWalkSpeed = Speed[(int32)InType];
}

void UC_StatusComponent::HealthProcess(float Amount)
{
	Health += Amount;

	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

void UC_StatusComponent::ManaProcess(float Amount)
{
	Mana += Amount;

	Mana = FMath::Clamp(Mana, 0.0f, MaxMana);
}

void UC_StatusComponent::StaminaProcess(float Amount)
{
	Stamina += Amount;

	Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);
}

// Called when the game starts
void UC_StatusComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


