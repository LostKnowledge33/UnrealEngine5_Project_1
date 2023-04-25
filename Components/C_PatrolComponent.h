// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_PatrolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_PROJECT_API UC_PatrolComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
		class AC_PatrolPath* Path;

	UPROPERTY(EditAnywhere)
		int32 Index;

	UPROPERTY(EditAnywhere)
		bool bReverse;

	UPROPERTY(EditAnywhere)
		float AcceptanceRadius = 50;

public:	
	// Sets default values for this component's properties
	UC_PatrolComponent();

	bool GetMoveTo(FVector& OutLocation, float& OutAcceptanceRadius);
	void UpdateNextIndex();

	FORCEINLINE bool IsVaild() { return Path != NULL; }


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


		
};
