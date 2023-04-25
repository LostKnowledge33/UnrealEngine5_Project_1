// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_PatrolPath.generated.h"

UCLASS()
class UE_PROJECT_API AC_PatrolPath : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class USplineComponent* Spline;

	UPROPERTY(EditAnywhere, Category = "Loop")
		bool bLoop;

public:	
	// Sets default values for this actor's properties
	AC_PatrolPath();

	FORCEINLINE class USplineComponent* GetSpline() { return Spline; }

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
