// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_ActionProcess_NormalMonster.h"
#include "Global.h"
#include "Player/C_ActionData.h"
#include "Player/C_ActionProcess.h"
#include "Components/C_StateComponent.h"
#include "Components/C_StatusComponent.h"

#include "GameFramework/Character.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Engine/DamageEvents.h"

AC_ActionProcess_NormalMonster::AC_ActionProcess_NormalMonster()
{
}

void AC_ActionProcess_NormalMonster::DoAction()
{
	if (!State->IsIdleMode()) return;

	//State->SetActionMode();

	if (bEnableCombo) normalAttackIndex++;

	currentData = ActionDataTable->NormalAttackData[normalAttackIndex % 3];

	OwnerCharacter->PlayAnimMontage(currentData.AnimMontage, currentData.PlayRatio);

	currentData.bCanMove ? Status->SetMove() : Status->SetStop();

	//GetWorld()->GetTimerManager().SetTimer(myTimerHandle, this, &AC_ActionProcess::GlobalCoolDownTick, 0.1f, true);
}

void AC_ActionProcess_NormalMonster::Begin_DoAction()
{

}

void AC_ActionProcess_NormalMonster::End_DoAction()
{
	State->SetIdleMode();
	Status->SetMove();

	normalAttackIndex = 0;
}

void AC_ActionProcess_NormalMonster::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
}

void AC_ActionProcess_NormalMonster::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

