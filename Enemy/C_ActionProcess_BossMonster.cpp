// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_ActionProcess_BossMonster.h"
#include "Global.h"
#include "Player/C_ActionData.h"
#include "Player/C_ActionProcess.h"
#include "Enemy/C_Enemy_AI_BossMonster.h"
#include "Components/C_StateComponent.h"
#include "Components/C_StatusComponent.h"

#include "GameFramework/Character.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"


AC_ActionProcess_BossMonster::AC_ActionProcess_BossMonster()
{

}

void AC_ActionProcess_BossMonster::DoAction()
{
	if (!State->IsIdleMode()) return;

	//State->SetActionMode();

	normalAttackIndex = FMath::RandRange(0, 1);

	currentData = ActionDataTable->NormalAttackData[normalAttackIndex];

	OwnerCharacter->PlayAnimMontage(currentData.AnimMontage, currentData.PlayRatio);

	currentData.bCanMove ? Status->SetMove() : Status->SetStop();

	AC_Enemy_AI_BossMonster* Boss = Cast<AC_Enemy_AI_BossMonster>(OwnerCharacter);

	//GetWorld()->GetTimerManager().SetTimer(myTimerHandle, this, &AC_ActionProcess::GlobalCoolDownTick, 0.1f, true);

	switch (normalAttackIndex)
	{
	case 0:
		Boss->WeaponCollision->AttachToComponent(Boss->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), FName("Weapon_L"));
		break;

	case 1:
		Boss->WeaponCollision->AttachToComponent(Boss->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), FName("Weapon_R"));
		break;
	}
}

void AC_ActionProcess_BossMonster::DoAction_Skill()
{
	if (!State->IsIdleMode()) return;

	//State->SetActionMode();

	currentData = ActionDataTable->SkillAttackData[0];

	OwnerCharacter->PlayAnimMontage(currentData.AnimMontage, currentData.PlayRatio);

	currentData.bCanMove ? Status->SetMove() : Status->SetStop();
}

void AC_ActionProcess_BossMonster::Begin_DoAction()
{
}

void AC_ActionProcess_BossMonster::End_DoAction()
{
	State->SetIdleMode();
	Status->SetMove();

	normalAttackIndex = 0;

	Cast<AC_Enemy_AI_BossMonster>(OwnerCharacter)->WeaponCollision->SetActive(false);
}

void AC_ActionProcess_BossMonster::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void AC_ActionProcess_BossMonster::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
