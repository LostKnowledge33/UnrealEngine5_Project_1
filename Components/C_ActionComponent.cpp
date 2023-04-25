// Fill out your copyright notice in the Description page of Project Settings.



#include "Components/C_ActionComponent.h"
#include "Global.h"
#include "Player/C_ActionData.h"
#include "Player/C_ActionProcess.h"

#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UC_ActionComponent::UC_ActionComponent()
{

}

void UC_ActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* character = Cast<ACharacter>(GetOwner());

	FString name;
	//name.Append(character->GetActorLabel());
	//name.Append("_");
	//name.Append(GetName().Replace(L"DA_", L""));

	FTransform transform;

	AC_ActionProcess* doAction = nullptr;
	if (DoActionClass)
	{//DoAction

		doAction = character->GetWorld()->SpawnActorDeferred<AC_ActionProcess>(DoActionClass, transform, character);
		//doAction->SetActorLabel(name + "_DoAction");
		doAction->AttachToComponent(character->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		//doAction->SetDatas(DoActionDatas);

		UGameplayStatics::FinishSpawningActor(doAction, transform);

		ActionProcess = doAction;
		ActionProcess->SetData(ActionDataTable);
	}

}

void UC_ActionComponent::DoAction()
{
	if (!ActionProcess) return;
	if (ActionProcess->IsGlobalCooldown()) return;

	ActionProcess->DoAction();
}

void UC_ActionComponent::SkillAction()
{
	if (!ActionProcess) return;
	if (ActionProcess->IsGlobalCooldown()) return;

	ActionProcess->DoAction_Skill();
}
