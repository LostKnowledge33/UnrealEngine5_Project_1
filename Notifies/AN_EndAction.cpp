// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/AN_EndAction.h"
#include "Global.h"
#include "Components/C_ActionComponent.h"
#include "Player/C_ActionProcess.h"

void UAN_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	UC_ActionComponent* action = CHelpers::GetComponent<UC_ActionComponent>(MeshComp->GetOwner());
	if (action == nullptr) return;

	action->ActionProcess->End_DoAction();
}
