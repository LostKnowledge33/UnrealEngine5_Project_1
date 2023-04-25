// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/C_ActionProcess_Shinbi.h"
#include "Global.h"
#include "Player/C_ActionData.h"
#include "Player/C_ActionProcess.h"
#include "Components/C_StateComponent.h"
#include "Components/C_StatusComponent.h"

#include "GameFramework/Character.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Engine/DamageEvents.h"
#include "TimerManager.h"

AC_ActionProcess_Shinbi::AC_ActionProcess_Shinbi()
{
	CHelpers::GetClass<ACharacter>(&wolf, "/Script/Engine.Blueprint'/Game/BluePrints/Character/Shinbi/BP_Shinbi_Wolf.BP_Shinbi_Wolf_C'");
}

void AC_ActionProcess_Shinbi::DoAction()
{
	if (!State->IsIdleMode()) return;
	if (Status->GetCurrentStamina() <= 10.f) return;

	//State->SetActionMode();
	
	if (bEnableCombo) normalAttackIndex++;

	currentData = ActionDataTable->NormalAttackData[normalAttackIndex % 3];

	OwnerCharacter->PlayAnimMontage(currentData.AnimMontage, currentData.PlayRatio);

	currentData.bCanMove ? Status->SetMove() : Status->SetStop();

	SetGlobalCooltime();
	GetWorld()->GetTimerManager().SetTimer(myTimerHandle, this, &AC_ActionProcess::GlobalCoolDownTick, 0.1f, true);

	FTimerDelegate TimerDel;
	TimerDel.BindUObject(this, &AC_ActionProcess::SetStaminaBar, 10.f, Status->GetCurrentStamina());
	GetWorld()->GetTimerManager().SetTimer(StaminaTimer, TimerDel, 1.f, false);

	Status->SetStaminaChargingState(false);
	Status->StaminaProcess(-10);
	StaminaBar->SetPercent(Status->GetCurrentStamina() / Status->GetMaxStamina());
}

void AC_ActionProcess_Shinbi::DoAction_Skill()
{
	if (!State->IsIdleMode()) return;
	if (Status->GetCurrentMana() <= 30.f) return;
	
	State->SetActionMode();

	currentData = ActionDataTable->SkillAttackData[0];

	OwnerCharacter->PlayAnimMontage(currentData.AnimMontage, currentData.PlayRatio);

	ACharacter* SpawnWolf = GetWorld()->SpawnActor<ACharacter>(wolf, OwnerCharacter->GetActorLocation(), OwnerCharacter->GetActorRotation());

	currentData.bCanMove ? Status->SetMove() : Status->SetStop();

	SetGlobalCooltime();
	GetWorld()->GetTimerManager().SetTimer(myTimerHandle, this, &AC_ActionProcess::GlobalCoolDownTick, 0.1f, true);

	Status->ManaProcess(-30);
	ManaBar->SetPercent(Status->GetCurrentMana() / Status->GetMaxMana());
}

void AC_ActionProcess_Shinbi::Begin_DoAction()
{

}

void AC_ActionProcess_Shinbi::End_DoAction()
{
	State->SetIdleMode();
	Status->SetMove();

	normalAttackIndex = 0;
}

void AC_ActionProcess_Shinbi::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* InOtherCharacter = Cast<ACharacter>(OtherActor);

	if (InOtherCharacter == nullptr) return;

	for (const ACharacter* other : HittedCharacters)
	{
		if (InOtherCharacter == other)
			return;
	}

	HittedCharacters.Add(InOtherCharacter);

	InOtherCharacter->TakeDamage(currentData.Power, FDamageEvent(), OwnerCharacter->GetController(), this);

	UParticleSystem* hitEffect = currentData.Effect;
	if (hitEffect)
	{
		FTransform transform = currentData.EffectTransform;
		transform.AddToTranslation(InOtherCharacter->GetActorLocation());

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
	}

	float hitStop = currentData.HitStop;

	if (FMath::IsNearlyZero(hitStop) == false)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.01f);
		UKismetSystemLibrary::K2_SetTimer(this, "RestoreDilation", hitStop * 0.01f, false);
	}
	/*
	TSubclassOf<UCameraShake> shakeClass = currentData.ShakeClass;

	if (shakeClass)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerCameraManager->PlayCameraShake(shakeClass);
	}
	*/
}

void AC_ActionProcess_Shinbi::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AC_ActionProcess_Shinbi::RestoreDilation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.00f);
}
