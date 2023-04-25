// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_SelectProcess.generated.h"

UCLASS()
class UE_PROJECT_API AC_SelectProcess : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UC_UI_ClassList> ClassLists;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AC_SelectStageController> ControllerClass;

	FORCEINLINE class UC_UI_ClassList* GetClassList() { return ClassList; }

protected:

	class UC_UI_ClassList* ClassList;

public:	
	// Sets default values for this actor's properties
	AC_SelectProcess();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
