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
	
	// 모든 커브가 존재할 때 타임라인을 설정합니다.
	//if (Curve1 != nullptr && Curve2 != nullptr)
	
	// 지정한 Curve에 사용할 Callback 함수들입니다.
	FOnTimelineFloat Curve1Callback;
		
	// Timeline이 끝났을 때 실행할 Callback 함수들입니다.
	FOnTimelineEvent LerpTimelineFinishedCallback;

	// Callback 함수에 사용할 함수를 바인드합니다.
	// 바인드 하는 함수에는 UFUNCTION 매크로가 적용되어야합니다.
	Curve1Callback.BindUFunction(this, FName("DamageTextTick"));
	LerpTimelineFinishedCallback.BindUFunction(this, FName("DamageTextFinish"));

	// Timeline에 Curve와 Curve를 사용할 Callback 함수를 추가합니다.
	LerpTimeline.AddInterpFloat(Curve1, Curve1Callback);
	LerpTimeline.SetLooping(false);
	// Timeline을 끝낼때 호출할 Cabllback 함수를 추가합니다.
	LerpTimeline.SetTimelineFinishedFunc(LerpTimelineFinishedCallback);

	// Timeline의 길이를 설정합니다.
	LerpTimeline.SetTimelineLength(LerpTimelineLength);

	// Timeline을 실행합니다.
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

	// Timeline에 Deltatime을 전달합니다.
	LerpTimeline.TickTimeline(DeltaTime);

	//FRotator temp = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), EventInstigator->GetPawn()->GetActorLocation());
	FRotator temp = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation());
	temp.Roll = 0;
	temp.Pitch = 0;
	SetActorRotation(temp);
}

