// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/C_MontageComponent.h"
#include "GameFramework/Character.h"
#include "Global.h"



// Sets default values for this component's properties
UC_MontageComponent::UC_MontageComponent()
{

}

void UC_MontageComponent::PlayRoll()
{
	PlayAnimMontage(EStateType::ROLL);
}

void UC_MontageComponent::PlayHitted()
{
	PlayAnimMontage(EStateType::HITTED);
}

void UC_MontageComponent::PlayDead()
{
	PlayAnimMontage(EStateType::DEAD);
}

void UC_MontageComponent::PlayBackStep()
{
	PlayAnimMontage(EStateType::BACKSTEP);
}

void UC_MontageComponent::PlayStun()
{
	PlayAnimMontage(EStateType::STUN);
}

void UC_MontageComponent::PlayKnockBack()
{
	PlayAnimMontage(EStateType::KNOCKBACK);
}

void UC_MontageComponent::PlayDeadEffect()
{
	
}

// Called when the game starts
void UC_MontageComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DataTable == nullptr) return;

	TArray<FMontageData*> datas;
	DataTable->GetAllRows<FMontageData>("", datas);

	for (int32 i = 0; i < (int32)EStateType::MAX; i++)
	{
		for (FMontageData* data : datas)
		{
			if ((EStateType)i == data->Type)
			{
				Datas[i] = data;
				continue;
			}
		}
	}
}

void UC_MontageComponent::PlayAnimMontage(EStateType InState, int32 index)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());

	const FMontageData* data = Datas[(int32)InState];
	if (data)
	{
		if (data->AnimMontage)
			character->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
	}
}
