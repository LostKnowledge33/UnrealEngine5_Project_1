
#include "C_Character.h"
#include "Global.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ProgressBar.h"

#include "GI_MyProject.h"
#include "Components/C_StatusComponent.h"
#include "Components/C_StateComponent.h"
#include "Components/C_MontageComponent.h"
#include "Components/C_ActionComponent.h"
#include "Components/C_FeetComponent.h"
#include "Player/C_ActionProcess.h"
#include "UI/C_UI_ClassList.h"
#include "UI/C_UI_ActionHUD.h"



// Sets default values
AC_Character::AC_Character()
{
	//GameInstance = Cast<UGI_MyProject>(GetGameInstance());
	GameInstance = Cast<UGI_MyProject>(UGameplayStatics::GetGameInstance(GetWorld()));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	CHelpers::CreateActorComponent<UC_StatusComponent>(this, &Status2, "Status");
	CHelpers::CreateActorComponent<UC_StateComponent>(this, &State2, "State");
	CHelpers::CreateActorComponent<UC_MontageComponent>(this, &Montage, "Montage");
	CHelpers::CreateActorComponent<UC_ActionComponent>(this, &Action, "Action");
	CHelpers::CreateActorComponent<UC_FeetComponent>(this, &Feet, "Feet");
	
	//CHelpers::GetClass<UC_UI_ClassList>(&ClassLists, "/Script/UMGEditor.WidgetBlueprint'/Game/BluePrints/UI/WBP_ClassList.WBP_ClassList_C'");

	SpringArm->SetRelativeLocation(FVector(0, 0, 90));
	SpringArm->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	Status2->HealthProcess(100);
	Status2->ManaProcess(100);
	Status2->StaminaProcess(100);
}

// Called when the game starts or when spawned
void AC_Character::BeginPlay()
{
	Super::BeginPlay();
	
	State2->OnStateTypeChanged.AddDynamic(this, &AC_Character::OnStateTypeChanged);

	//GetController<APlayerController>()->SetInputMode(FInputModeGameAndUI());
	GetController<APlayerController>()->SetInputMode(FInputModeGameOnly());
	GetController<APlayerController>()->bShowMouseCursor = false;
}

void AC_Character::Hitted()
{
	ActualDamage += (float)(UKismetMathLibrary::RandomInteger(4) - 1);

	/*
	DamageText = GetWorld()->SpawnActor<AC_DamageText>(DamageTextClass, GetActorTransform());

	DamageText->DamageRender->SetText(FText::FromString(FString::FromInt((int)ActualDamage)));
	DamageText->DamageRender->SetTextRenderColor(FColor::Red);
	DamageText->DamageRender->SetVisibility(true);

	DamageText->SetActorLocation((DamageText->GetActorUpVector() * 50) + GetActorLocation());
	DamageText->SetAttacker(DamageInstigator);
	*/
	fDeltaTime = 0.f;

	FTimerDelegate TimerDel;
	TimerDel.BindUObject(this, &AC_Character::SetHealthBar, ActualDamage, Status2->GetCurrentHealth());
	GetWorld()->GetTimerManager().SetTimer(Action->ActionProcess->HealthBarTimer, TimerDel, 0.1f, true);
	
	Status2->HealthProcess(-ActualDamage);
	ActualDamage = 0.f;
	//Status2->SetStop();
	
	if (DamageInstigator->GetPawn()->ActorHasTag(FName("Boss")))
	{
		FVector start = GetActorLocation();
		FVector target = DamageInstigator->GetPawn()->GetActorLocation();
		FVector direction = start - target;
		direction.Z = 0;
		direction.Normalize();

		LaunchCharacter(direction * 600.f, true, false);
	}

	Montage->PlayHitted();
}

float AC_Character::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (State2->IsHittedMode()) return 0.0f;
	if (State2->IsRollMode()) return 0.0f;

	DamageInstigator = EventInstigator;

	State2->SetHittedMode();

	return 0.0f;
}

// Called every frame
void AC_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	fDeltaTime += DeltaTime;

	if (Status2->IsStaminaCharging() && (Status2->GetCurrentStamina() < Status2->GetMaxStamina()) )
	{
		Status2->StaminaProcess(0.1f);
		Action->ActionProcess->StaminaBar->SetPercent(Status2->GetCurrentStamina() / Status2->GetMaxStamina());
	}

	if (Status2->GetCurrentMana() < Status2->GetMaxMana())
	{
		Status2->ManaProcess(0.01f);
		Action->ActionProcess->ManaBar->SetPercent(Status2->GetCurrentMana() / Status2->GetMaxMana());
	}
}

// Called to bind functionality to input
void AC_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AC_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AC_Character::MoveRight);

	PlayerInputComponent->BindAxis("RotateHorizontal", this, &AC_Character::RotateHorizontal);
	PlayerInputComponent->BindAxis("RotateVertical", this, &AC_Character::RotateVertical);

	PlayerInputComponent->BindAction("Jumping", EInputEvent::IE_Pressed, this, &AC_Character::Jumping);
	PlayerInputComponent->BindAction("Avoid", EInputEvent::IE_Pressed, this, &AC_Character::Avoid);
	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &AC_Character::DoAction);

	PlayerInputComponent->BindAction("SelectCharacter", EInputEvent::IE_Pressed, this, &AC_Character::OpenChangeClassList);
	PlayerInputComponent->BindAction("Skill1", EInputEvent::IE_Pressed, this, &AC_Character::SkillAction);
}

void AC_Character::MoveForward(float Axis)
{
	if (!Status2->CanMove()) return;

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void AC_Character::MoveRight(float Axis)
{
	if (!Status2->CanMove()) return;

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void AC_Character::RotateHorizontal(float Axis)
{
	AddControllerYawInput(Axis);
}

void AC_Character::RotateVertical(float Axis)
{
	AddControllerPitchInput(Axis);
}

void AC_Character::Jumping()
{

}

void AC_Character::Avoid()
{
	if (!Status2->CanMove()) return;
	if (!State2->IsIdleMode()) return;
	if (Status2->GetCurrentStamina() <= 10.f) return;

	State2->SetRollMode();

	Status2->SetStaminaChargingState(false);
	Status2->StaminaProcess(-10);
	Action->ActionProcess->StaminaBar->SetPercent(Status2->GetCurrentStamina() / Status2->GetMaxStamina());
}

void AC_Character::DoAction()
{
	Action->DoAction();
}

void AC_Character::SkillAction()
{
	Action->SkillAction();
}

void AC_Character::OpenChangeClassList()
{
	GetController();
}

void AC_Character::SetHealthBar(float amount, float current)
{
	float dest = current - amount;
	float temp = FMath::Lerp(current, dest, FMath::Clamp(fDeltaTime, 0.f, 1.f));
	Action->ActionProcess->HealthBar->SetPercent(temp / Status2->GetMaxHealth());

	if(FMath::IsNearlyEqual(temp, dest))
		GetWorld()->GetTimerManager().ClearTimer(Action->ActionProcess->HealthBarTimer);
}

void AC_Character::Begin_Roll()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	FVector start = GetActorLocation();
	FVector from = start + GetVelocity().GetSafeNormal2D();
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, from));

	Montage->PlayRoll();
}

void AC_Character::End_Roll()
{
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	State2->SetIdleMode();
	Status2->SetStaminaChargingState(true);
}

FGenericTeamId AC_Character::GetGenericTeamId() const
{
	return FGenericTeamId(TeamId);
}

void AC_Character::EndIntroCutScene()
{



}

void AC_Character::ChangeColor(FLinearColor InColor)
{

}

void AC_Character::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::ROLL:
		Begin_Roll();
		break;
	case EStateType::HITTED:
		Hitted();
		break;
	}
}

