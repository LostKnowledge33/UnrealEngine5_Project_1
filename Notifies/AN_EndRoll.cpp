// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/AN_EndRoll.h"
#include "Player/C_Character.h"

FString UAN_EndRoll::GetNotifyName_Implementation() const
{
	return "EndRoll";
}

void UAN_EndRoll::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr) return;
	if (MeshComp->GetOwner() == nullptr) return;

	AC_Character* character = Cast<AC_Character>(MeshComp->GetOwner());

	if (character == nullptr) return;

	character->End_Roll();
}
