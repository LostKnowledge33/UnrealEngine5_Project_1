// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/C_StateComponent.h"

// Sets default values for this component's properties
UC_StateComponent::UC_StateComponent()
{
	SetIdleMode();
}

void UC_StateComponent::SetIdleMode()
{
	ChangeType(EStateType::IDLE);
}

void UC_StateComponent::SetRollMode()
{
	ChangeType(EStateType::ROLL);
}

void UC_StateComponent::SetActionMode()
{
	ChangeType(EStateType::ACTION);
}

void UC_StateComponent::SetHittedMode()
{
	ChangeType(EStateType::HITTED);
}

void UC_StateComponent::SetDeadMode()
{
	ChangeType(EStateType::DEAD);
}

void UC_StateComponent::SetBackstepMode()
{
	ChangeType(EStateType::BACKSTEP);
}

void UC_StateComponent::SetStunMode()
{
	ChangeType(EStateType::STUN);
}

void UC_StateComponent::ChangeType(EStateType InType)
{
	EStateType type = Type;
	Type = InType;

	if (OnStateTypeChanged.IsBound())
	{
		OnStateTypeChanged.Broadcast(type, InType);
	}
}

// Called when the game starts
void UC_StateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



