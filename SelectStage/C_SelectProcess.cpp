// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectStage/C_SelectProcess.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"

#include "Global.h"
#include "UI/C_UI_ClassList.h"


// Sets default values
AC_SelectProcess::AC_SelectProcess()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::GetClass<UC_UI_ClassList>(&ClassLists, "/Script/UMGEditor.WidgetBlueprint'/Game/BluePrints/UI/WBP_ClassList.WBP_ClassList_C'");
	//CHelpers::GetClass<AC_SelectStageController>(&ControllerClass, "/Script/CoreUObject.Class'/Script/UE_Project.C_SelectStageController_C'");

	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera");

	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	//UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->AutoPossessPlayer = EAutoReceiveInput::Player0;
	/*
	if (OurPlayerController)
	{
		if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
		{
			// 1 번 카메라로 즉시 컷해 들어갑니다.
			OurPlayerController->SetViewTarget(Camera);
		}
		else if ((OurPlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
		{
			// 2 번 카메라로 부드럽게 전환합니다.
			OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
		}
	}
	*/
}

// Called when the game starts or when spawned
void AC_SelectProcess::BeginPlay()
{
	Super::BeginPlay();
	/*
	ClassList = CreateWidget<UC_UI_ClassList>(GetWorld(), ClassLists);
	ClassList->AddToViewport();
	ClassList->SetVisibility(ESlateVisibility::Visible);

	//GetController<APlayerController>()->bShowMouseCursor = true;
	//GetController<APlayerController>()->SetInputMode(FInputModeGameAndUI());

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.f);
	//UGameplayStatics::Get
	*/
}

// Called every frame
void AC_SelectProcess::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

