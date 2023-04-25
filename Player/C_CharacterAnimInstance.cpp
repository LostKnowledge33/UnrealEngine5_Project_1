// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/C_CharacterAnimInstance.h"
#include "Player/C_Character.h"
#include "Global.h"

void UC_CharacterAnimInstance::NativeBeginPlay()
{
	player = Cast<ACharacter>(TryGetPawnOwner());

	Feet = CHelpers::GetComponent<UC_FeetComponent>(player);
}

void UC_CharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (player == nullptr) return;

	//Angle = CalculateDirection(player->GetVelocity(), player->GetViewRotation());
	//IsMoving = (bool)player->GetVelocity().Size();
	
	FRotator controlRotator = player->GetControlRotation();
	//controlRotator.Yaw = 0.f;
	controlRotator.Pitch = 0.f;

	//CalculateDirection(player->GetVelocity(), controlRotator);

	Angle = UKismetAnimationLibrary::CalculateDirection(player->GetVelocity(), controlRotator);
	Speed = player->GetVelocity().Size2D();

	if (Feet)
		FeetData = Feet->GetData();
}
