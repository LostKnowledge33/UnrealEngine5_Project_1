// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTaskNode_Patrol.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_API UC_BTTaskNode_Patrol : public UBTTaskNode
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
		float Delay = 2.f;

	float TotalTime = 0.f;

public:

	UC_BTTaskNode_Patrol();

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
