// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTaskNode_Hitted.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_API UC_BTTaskNode_Hitted : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UC_BTTaskNode_Hitted();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) override;

};
