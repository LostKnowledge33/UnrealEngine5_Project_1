// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/C_ActionProcess.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "Components/C_StateComponent.h"
#include "Components/C_StatusComponent.h"
#include "UI/C_UI_ActionHUD.h"
#include "TimerManager.h"

// Sets default values
AC_ActionProcess::AC_ActionProcess()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::GetClass<UC_UI_ActionHUD>(&ActionHUDClass, "/Script/UMGEditor.WidgetBlueprint'/Game/BluePrints/UI/WBP_ActionHUD.WBP_ActionHUD_C'");
}

void AC_ActionProcess::Tick(float DeltaTime)
{
	fDeltaTime += DeltaTime;
}

void AC_ActionProcess::GlobalCoolDownTick()
{
	if (bFirstTick)
	{
		fDeltaTime = 0.f;
		bFirstTick = false;
	}

	fGlobalCooltime -= 0.1f;
	NormalAttack->SetPercent(fGlobalCooltime / 0.8f);
	SkillAttack->SetPercent(fGlobalCooltime / 0.8f);

	if (--RepeatingCallsRemaining <= 0) 
	{
		bFirstTick = true;
		fGlobalCooltime = 0.f;
		RepeatingCallsRemaining = 8;
		GetWorld()->GetTimerManager().ClearTimer(myTimerHandle);
		// MyTimerHandle 은 이제 다른 타이머에 재사용 가능합니다.
	}
}

void AC_ActionProcess::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AC_ActionProcess::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AC_ActionProcess::ResetHittedArray()
{
}

void AC_ActionProcess::SetStaminaBar(float amount, float current)
{
	GetWorld()->GetTimerManager().ClearTimer(StaminaTimer);
	Status->SetStaminaChargingState(true);
}

// Called when the game starts or when spawned
void AC_ActionProcess::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UC_StateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UC_StatusComponent>(OwnerCharacter);

	if (!OwnerCharacter->ActorHasTag(FName("Enemy")))
	{
		ActionHUD = CreateWidget<UC_UI_ActionHUD>(OwnerCharacter->GetController<APlayerController>(), ActionHUDClass);
		ActionHUD->AddToViewport();
		ActionHUD->SetVisibility(ESlateVisibility::Visible);

		NormalAttack = Cast<UProgressBar>(ActionHUD->GetWidgetFromName("ProgressBar_118"));
		SkillAttack = Cast<UProgressBar>(ActionHUD->GetWidgetFromName("ProgressBar"));

		HealthBar = Cast<UProgressBar>(ActionHUD->GetWidgetFromName("HealthBar"));
		ManaBar = Cast<UProgressBar>(ActionHUD->GetWidgetFromName("ManaBar"));
		StaminaBar = Cast< UProgressBar>(ActionHUD->GetWidgetFromName("StaminaBar"));
	}
}

