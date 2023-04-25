// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/AN_SaveCombo.h"
#include "Player/C_Shinbi.h"
#include "Player/C_ActionProcess.h"
#include "Components/C_ActionComponent.h"

void UAN_SaveCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AC_Shinbi* player = Cast<AC_Shinbi>(MeshComp->GetOwner());

	//player->Action->ActionProcess->
}
