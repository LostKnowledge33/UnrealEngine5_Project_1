// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_EndRoll.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_API UAN_EndRoll : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

};
