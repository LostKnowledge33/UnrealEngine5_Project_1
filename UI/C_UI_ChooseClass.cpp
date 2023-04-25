// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_UI_ChooseClass.h"
#include "UI/C_UI_ClassList.h"
#include "Global.h"
#include "Player/C_Character.h"
#include "UE_ProjectGameModeBase.h"


void UC_UI_ChooseClass::Click()
{
	GetClassList()->Clicked(GetName());
}

void UC_UI_ChooseClass::Hover()
{
	GetClassList()->Hovered(GetName());
}

void UC_UI_ChooseClass::Unhover()
{
	GetClassList()->Unhovered(GetName());
}

UC_UI_ClassList* UC_UI_ChooseClass::GetClassList()
{
	AUE_ProjectGameModeBase* game = Cast<AUE_ProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	return nullptr;
	//return game->GetClassList();
}
