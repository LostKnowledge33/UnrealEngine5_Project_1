// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/NS_WeaponCollision.h"
#include "Player/C_Character.h"
#include "Global.h"
#include "Player/C_ActionProcess.h"
#include "Components/C_ActionComponent.h"
#include "Action/C_ActionProcess_Shinbi.h"

void UNS_WeaponCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ACharacter* player = Cast<ACharacter>(MeshComp->GetOwner());
	if (player == nullptr) return;

	UC_ActionComponent* action = Cast<UC_ActionComponent>(player->GetComponentByClass(UC_ActionComponent::StaticClass()));
	action->SetWeaponCollisionState(true);
}

void UNS_WeaponCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ACharacter* player = Cast<ACharacter>(MeshComp->GetOwner());
	if (player == nullptr) return;

	UC_ActionComponent* action = Cast<UC_ActionComponent>(player->GetComponentByClass(UC_ActionComponent::StaticClass()));
	action->SetWeaponCollisionState(false);
	action->ActionProcess->ResetHittedArray();
}
