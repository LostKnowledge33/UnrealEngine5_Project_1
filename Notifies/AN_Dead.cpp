// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/AN_Dead.h"
#include "Global.h"
#include "Components/C_ActionComponent.h"
#include "Player/C_ActionProcess.h"
#include "Enemy/C_Enemy.h"

void UAN_Dead::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	AC_Enemy* character = Cast<AC_Enemy>(MeshComp->GetOwner());
	if (character == nullptr) return;

	character->EndDead();
}

