// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Components/C_StatusComponent.h"
#include "C_BTTaskNode_SetSpeed.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_API UC_BTTaskNode_SetSpeed : public UBTTaskNode
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere)
		ECharacterSpeed SpeedType;

public:

	UC_BTTaskNode_SetSpeed();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
