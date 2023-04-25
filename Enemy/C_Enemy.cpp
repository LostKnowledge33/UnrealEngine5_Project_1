// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_Enemy.h"
#include "Global.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/TextBlock.h"
#include "Components/TextRenderComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/C_StatusComponent.h"
#include "Components/C_StateComponent.h"
#include "Components/C_MontageComponent.h"
#include "Components/C_ActionComponent.h"
#include "UI/C_DamageText.h"
#include "Player/C_Character.h"
#include "Enemy/C_AIController.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
AC_Enemy::AC_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent<UC_StatusComponent>(this, &Status, "Status");
	CHelpers::CreateActorComponent<UC_StateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UC_MontageComponent>(this, &Montage, "Montage");
	CHelpers::CreateActorComponent<UC_ActionComponent>(this, &Action, "Action");
	
	CHelpers::GetClass<AC_DamageText>(&DamageTextClass, "/Script/Engine.Blueprint'/Game/BluePrints/UI/BP_C_DamageText.BP_C_DamageText_C'");

	Status->HealthProcess(30);

	GetCharacterMovement()->bCanWalkOffLedges = false;
}

// Called when the game starts or when spawned
void AC_Enemy::BeginPlay()
{
	Super::BeginPlay();

	State->OnStateTypeChanged.AddDynamic(this, &AC_Enemy::OnStateTypeChanged);

}

float AC_Enemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	DamageInstigator = EventInstigator;

	if(!State->IsStunMode())
		State->SetHittedMode();

	return 0.0f;
}

void AC_Enemy::Hitted()
{
	ActualDamage += (float)(UKismetMathLibrary::RandomInteger(4) - 1);

	DamageText = GetWorld()->SpawnActor<AC_DamageText>(DamageTextClass, GetActorTransform());

	DamageText->DamageRender->SetText(FText::FromString(FString::FromInt((int)ActualDamage)));
	DamageText->DamageRender->SetTextRenderColor(FColor::Red);
	DamageText->DamageRender->SetVisibility(true);

	DamageText->SetActorLocation((DamageText->GetActorUpVector() * 50) + GetActorLocation());
	DamageText->SetAttacker(DamageInstigator);

	Status->HealthProcess(-ActualDamage);

	if (Status->GetCurrentHealth() <= 0.0f)
	{
		State->SetDeadMode();
		Status->SetStop();
		return;
	}

	if (ActorHasTag(FName("Boss")))
	{
		if (State->IsStunMode()) return;

		if ((Status->GetCurrentHealth() <= 50.f) && !isStuned)
		{
			isStuned = true;
			State->SetStunMode();
			Status->SetStop();
		}
		else
		{
			State->SetIdleMode();
			Status->SetMove();
		}
		
		return;
	}
	else
	{
		Status->SetStop();
		Montage->PlayHitted();
	}

	ActualDamage = 0.f;

	FVector start = GetActorLocation();
	FVector target = DamageInstigator->GetPawn()->GetActorLocation();
	FVector direction = start - target;
	direction.X = 0;
	direction.Z = 0;
	direction.Normalize();
	
	SetActorRotation(FRotator(0, UKismetMathLibrary::FindLookAtRotation(start, target).Yaw, 0));
	LaunchCharacter(direction * 300.f, true, false);
}

void AC_Enemy::Dead()
{
	if (!State->IsDeadMode()) return;

	Montage->PlayDead();
	Action->SetWeaponCollisionState(false);
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//UKismetSystemLibrary::K2_SetTimer(this, "EndDead", 1.5f, false);
	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Montage2->FireEffectMuzzle, GetActorLocation(), GetActorRotation());
	if(ActorHasTag(FName("Boss")))
		Cast<AC_Character>(DamageInstigator->GetPawn())->StageClear();
}

void AC_Enemy::BackStep()
{
	Montage->PlayBackStep();
}

void AC_Enemy::Stun()
{
	Montage->PlayStun();
}

void AC_Enemy::EndDead()
{
	UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(Montage->FireEffectMuzzle, GetMesh(), FName(""), FVector::Zero(), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);

	//SetActorLocation(GetActorLocation() + (GetActorLocation().DownVector * 50));
	GetMesh()->SetVisibility(false);

	if(Weapon)
		Weapon->SetVisibility(false);

	UKismetSystemLibrary::K2_SetTimer(this, "DestroyActor", 1.5f, false);
}

void AC_Enemy::TakeDamageFromBP(float Damage, AController* EventInstigator)
{
	ActualDamage = Damage;

	DamageInstigator = EventInstigator;

	State->SetHittedMode();
}

void AC_Enemy::DestroyActor()
{
	Destroy();
}

// Called every frame
void AC_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Enemy::ChangeColor(FLinearColor InColor)
{

}

void AC_Enemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::IDLE:
		break;
	case EStateType::ROLL:
		break;
	case EStateType::ACTION:
		break;
	case EStateType::HITTED:
		Hitted();
		break;
	case EStateType::DEAD:
		Dead();
		break;
	case EStateType::BACKSTEP:
		BackStep();
		break;
	case EStateType::STUN:
		Stun();
		break;
	case EStateType::MAX:
		break;
	default:
		break;
	}
}

