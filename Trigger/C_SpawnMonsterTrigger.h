// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_SpawnMonsterTrigger.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FSpawnNormalMonster, int32);

UCLASS()
class UE_PROJECT_API AC_SpawnMonsterTrigger : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	
	TSubclassOf<class AC_Enemy_AI_NormalMonster> MonsterClass;
	TSubclassOf<AC_AIController> ttte;

public:

	UPROPERTY(EditAnywhere)
		class UAnimMontage* SpawnAnim;

	FSpawnNormalMonster OnSpawnNormalMonster;

public:

	AC_SpawnMonsterTrigger();

	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
