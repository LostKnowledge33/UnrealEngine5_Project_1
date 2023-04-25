// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "C_StateComponent.h"
#include "C_MontageComponent.generated.h"

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		EStateType Type;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1.f;

	UPROPERTY(EditAnywhere)
		FName StartSection;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_PROJECT_API UC_MontageComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly)
		class UDataTable* DataTable;
	
	FMontageData* Datas[(int32)EStateType::MAX];

public:

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* FireEffectMuzzle;

public:	
	// Sets default values for this component's properties
	UC_MontageComponent();

	void PlayRoll();
	void PlayHitted();
	void PlayDead();
	void PlayBackStep();
	void PlayStun();
	void PlayKnockBack();

	void PlayDeadEffect();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	void PlayAnimMontage(EStateType InState, int32 index = 0);
		
};
