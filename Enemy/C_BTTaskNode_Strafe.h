// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTaskNode_Strafe.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_API UC_BTTaskNode_Strafe : public UBTTaskNode
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
		float Delay = 3.f;

	float TotalTime = 0.f;
	float StrafeDistance = 700.f;

	int32 iWhatDoState = -1;
	int32 iBeforeState = -1;

public:

	UC_BTTaskNode_Strafe();

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
