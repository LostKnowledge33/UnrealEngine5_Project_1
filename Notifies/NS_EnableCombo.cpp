// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/NS_EnableCombo.h"
#include "Global.h"
#include "Player/C_Character.h"
#include "Player/C_ActionProcess.h"
#include "Components/C_ActionComponent.h"


void UNS_EnableCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AC_Character* player = Cast<AC_Character>(MeshComp->GetOwner());
	if (player == nullptr) return;

	player->Action->ActionProcess->SetEnableCombo(true);
}

void UNS_EnableCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AC_Character* player = Cast<AC_Character>(MeshComp->GetOwner());
	if (player == nullptr) return;

	player->Action->ActionProcess->SetEnableCombo(false);
}
