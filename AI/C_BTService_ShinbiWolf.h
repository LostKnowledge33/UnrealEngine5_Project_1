// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTService_ShinbiWolf.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_API UC_BTService_ShinbiWolf : public UBTService
{
	GENERATED_BODY()

public:

	UC_BTService_ShinbiWolf();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
