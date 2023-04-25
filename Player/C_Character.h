// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "I_Character.h"
#include "GenericTeamAgentInterface.h"
#include "C_Character.generated.h"

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	SHINBI, REVENANT, TWINBLAST, MAX
};

UCLASS()
class UE_PROJECT_API AC_Character : public ACharacter, public II_Character, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class UC_StatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UC_StateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UC_MontageComponent* Montage;

	UPROPERTY(VisibleDefaultsOnly)
		class UC_ActionComponent* Action;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* ActionHUD;

	UPROPERTY(VisibleDefaultsOnly)
		class UC_FeetComponent* Feet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UParticleSystem* IntroParticle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UAnimMontage* IntroMontage;

	UPROPERTY(EditDefaultsOnly)
		uint8 TeamId = 0;

	bool bPlayingIntro = false;

protected:
	bool bIsAttacking;
	bool bEnableWeaponCollision;

	class AController* DamageInstigator;

	float ActualDamage = 0.f;

	class UGI_MyProject* GameInstance;

private:

	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

	float fDeltaTime = 0.f;

public:
	// Sets default values for this character's properties
	AC_Character();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Begin_Roll();
	void End_Roll();

	virtual void ChangeColor(FLinearColor InColor) override;

	virtual FGenericTeamId GetGenericTeamId() const override;

	UFUNCTION()
		void EndIntroCutScene();

	UFUNCTION(BlueprintImplementableEvent)
		void StageClear();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Hitted();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:

	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void RotateHorizontal(float Axis);
	void RotateVertical(float Axis);
	
	void Jumping();
	void Avoid();
	void DoAction();
	void SkillAction();

	void OpenChangeClassList();

	void SetHealthBar(float amount, float current);

	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);
};
