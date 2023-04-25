// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_PatrolPath.h"
#include "Global.h"
#include "Components/SplineComponent.h"
#include "Components/TextRenderComponent.h"


// Sets default values
AC_PatrolPath::AC_PatrolPath()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<USplineComponent>(this, &Spline, "Spline", Scene);

	Spline->SetRelativeLocation(FVector(0, 0, 30));
}

void AC_PatrolPath::OnConstruction(const FTransform& Transform)
{
	//Text->Text = FText::FromString(GetActorLabel());

	Spline->SetClosedLoop(bLoop);
}

// Called when the game starts or when spawned
void AC_PatrolPath::BeginPlay()
{
	Super::BeginPlay();
	
}