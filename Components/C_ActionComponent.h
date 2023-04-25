// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_ActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE_PROJECT_API UC_ActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_ActionComponent();
	
	void DoAction();
	void SkillAction();

	void SetWeaponCollisionState(bool state) { bEnableWeaponCollision = state; }
	bool GetWeaponCollisionState() { return bEnableWeaponCollision; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditDefaultsOnly)
		class UC_ActionData* ActionDataTable;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class AC_ActionProcess> DoActionClass;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* ActionHUD;

	class AC_ActionProcess* ActionProcess;

private:

	bool bEnableWeaponCollision = false;

};
