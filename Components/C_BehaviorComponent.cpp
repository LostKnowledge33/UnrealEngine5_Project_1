// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/C_BehaviorComponent.h"
#include "Global.h"
#include "Player/C_Character.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values for this component's properties
UC_BehaviorComponent::UC_BehaviorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}

// Called when the game starts
void UC_BehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UC_BehaviorComponent::ChangeType(EBehaviorType InType)
{
	EBehaviorType type = GetType();
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InType);

	if (OnBehaviorTypeChanged.IsBound())
		OnBehaviorTypeChanged.Broadcast(type, InType);
}

EBehaviorType UC_BehaviorComponent::GetType()
{
	return (EBehaviorType)Blackboard->GetValueAsEnum(BehaviorKey);
}

// Called every frame
void UC_BehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UC_BehaviorComponent::IsTypeMode(EBehaviorType InType)
{
	return GetType() == InType;
}

AC_Character* UC_BehaviorComponent::GetTargetPlayer()
{
	return Cast<AC_Character>(Blackboard->GetValueAsObject(PlayerKey));
}

ACharacter* UC_BehaviorComponent::GetTarget()
{
	return Cast<ACharacter>(Blackboard->GetValueAsObject(TargetKey));
}

