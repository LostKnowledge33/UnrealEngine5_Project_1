// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTaskNode_ArmsLength.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_API UC_BTTaskNode_ArmsLength : public UBTTaskNode
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
		float fDelay = 5.f;

	float fTotalTime = 0.f;
	float fDistance = 900.f;

public:

	UC_BTTaskNode_ArmsLength();

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
