// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_DamageText.h"
#include "Global.h"
#include "Player/C_Character.h"

#include "Components/TextRenderComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/Font.h"

// Sets default values
AC_DamageText::AC_DamageText()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UTextRenderComponent>(this, &DamageRender, "DamageText");
}

// Called when the game starts or when spawned
void AC_DamageText::BeginPlay()
{
	Super::BeginPlay();
	
	// ��� Ŀ�갡 ������ �� Ÿ�Ӷ����� �����մϴ�.
	//if (Curve1 != nullptr && Curve2 != nullptr)
	
	// ������ Curve�� ����� Callback �Լ����Դϴ�.
	FOnTimelineFloat Curve1Callback;
		
	// Timeline�� ������ �� ������ Callback �Լ����Դϴ�.
	FOnTimelineEvent LerpTimelineFinishedCallback;

	// Callback �Լ��� ����� �Լ��� ���ε��մϴ�.
	// ���ε� �ϴ� �Լ����� UFUNCTION ��ũ�ΰ� ����Ǿ���մϴ�.
	Curve1Callback.BindUFunction(this, FName("DamageTextTick"));
	LerpTimelineFinishedCallback.BindUFunction(this, FName("DamageTextFinish"));

	// Timeline�� Curve�� Curve�� ����� Callback �Լ��� �߰��մϴ�.
	LerpTimeline.AddInterpFloat(Curve1, Curve1Callback);
	LerpTimeline.SetLooping(false);
	// Timeline�� ������ ȣ���� Cabllback �Լ��� �߰��մϴ�.
	LerpTimeline.SetTimelineFinishedFunc(LerpTimelineFinishedCallback);

	// Timeline�� ���̸� �����մϴ�.
	LerpTimeline.SetTimelineLength(LerpTimelineLength);

	// Timeline�� �����մϴ�.
	LerpTimeline.PlayFromStart();

}

void AC_DamageText::DamageTextTick(float data)
{
	FVector textLocation = DamageRender->GetRelativeLocation();
	textLocation.Z += data;

	DamageRender->SetRelativeLocation(textLocation);
}

void AC_DamageText::DamageTextFinish()
{
	Destroy();
}

// Called every frame
void AC_DamageText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Timeline�� Deltatime�� �����մϴ�.
	LerpTimeline.TickTimeline(DeltaTime);

	//FRotator temp = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), EventInstigator->GetPawn()->GetActorLocation());
	FRotator temp = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation());
	temp.Roll = 0;
	temp.Pitch = 0;
	SetActorRotation(temp);
}

