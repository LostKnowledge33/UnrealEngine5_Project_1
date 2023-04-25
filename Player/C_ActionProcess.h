// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_ActionProcess.generated.h"


UCLASS()
class UE_PROJECT_API AC_ActionProcess : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_ActionProcess();

	virtual void Tick(float DeltaTime) override;

	virtual void DoAction() {}
	virtual void DoAction_Skill() {}
	virtual void Begin_DoAction() {}
	virtual void End_DoAction() {}

	void SetData(class UC_ActionData* data) { ActionDataTable = data; }

	void GlobalCoolDownTick();

	inline bool IsGlobalCooldown() { return fGlobalCooltime > 0 ? true : false; }
	inline void SetGlobalCooltime() { fGlobalCooltime = 0.8f; }

	inline void SetEnableCombo(bool state) { bEnableCombo = state; }

	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void ResetHittedArray();

	void SetStaminaBar(float amount, float current);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	class UProgressBar* HealthBar;
	class UProgressBar* ManaBar;
	class UProgressBar* StaminaBar;

	FTimerHandle HealthBarTimer;
	FTimerHandle ManaBarTimer;
	FTimerHandle StaminaTimer;



protected:

	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UC_StateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UC_StatusComponent* Status;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UC_UI_ActionHUD> ActionHUDClass;

	
	class UC_ActionData* ActionDataTable;
	class UC_UI_ActionHUD* ActionHUD;

	class UProgressBar* NormalAttack;
	class UProgressBar* SkillAttack;

	FTimerHandle myTimerHandle;
	int32 RepeatingCallsRemaining = 8;

	float fGlobalCooltime = 0.f;
	float fDeltaTime = 0.f;

	bool bEnableCombo = false;
	bool bFirstTick = true;

	float fStaminaDelta = 0.f;
};
