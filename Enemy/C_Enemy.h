// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "I_Character.h"
#include "Components/C_StateComponent.h"
#include "C_Enemy.generated.h"

UCLASS()
class UE_PROJECT_API AC_Enemy : public ACharacter, public II_Character
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleDefaultsOnly)
		class UC_StatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UC_StateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UC_MontageComponent* Montage;

	UPROPERTY(VisibleDefaultsOnly)
		class UC_ActionComponent* Action;

	class AC_DamageText* DamageText;
	TSubclassOf<AC_DamageText> DamageTextClass;

	class AController* DamageInstigator;

	float ActualDamage = 0.f;

protected:
		
	TSubclassOf<class AC_AIController> AiClass;

public:

	UPROPERTY(EditDefaultsOnly)
		class UCapsuleComponent* WeaponCollision;

	UPROPERTY(EditDefaultsOnly)
		class USkeletalMeshComponent* Weapon;

	UPROPERTY(BlueprintReadWrite)
		bool bIsEngage = false;


	bool isStuned = false;

public:
	// Sets default values for this character's properties
	AC_Enemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// II_Character을(를) 통해 상속됨
	virtual void ChangeColor(FLinearColor InColor) override;

	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Hitted();
	void Dead();
	void BackStep();
	void Stun();

	UFUNCTION()
		void DestroyActor();

public:	

	FORCEINLINE class UC_ActionComponent* GetAction() { return Action; }
	FORCEINLINE class UC_StatusComponent* GetStatus() { return Status; }

	UFUNCTION()
		void EndDead();

	UFUNCTION(BlueprintCallable)
		void TakeDamageFromBP(float Damage, AController* EventInstigator);

};
