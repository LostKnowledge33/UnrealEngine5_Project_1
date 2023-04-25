// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_UI_ClassList.h"
#include "UI/C_UI_ChooseClass.h"
#include "Components/GridPanel.h"
#include "Components/Border.h"
#include "Blueprint/UserWidget.h"



void UC_UI_ClassList::NativeConstruct()
{
	UGridPanel* gridPanel = Cast<UGridPanel>(GetWidgetFromName(FName("GridPanel_163")));
	TArray<UWidget*> widgets = gridPanel->GetAllChildren();

	for (UWidget* widget : widgets)
	{
		FUI_Class_Data data;
		data.Class = Cast<UC_UI_ChooseClass>(widget);

		Datas.Add(data);
	}

	Super::NativeConstruct();
}

void UC_UI_ClassList::Clicked(FString InName)
{

}

void UC_UI_ClassList::Hovered(FString InName)
{
	for (const FUI_Class_Data& data : Datas)
	{
		UBorder* border = Cast<UBorder>(data.Class->GetWidgetFromName("Border_0"));

		if (data.Class->GetName() == InName)
		{
			border->SetBrushColor(FLinearColor::Red);
		}
	}
}

void UC_UI_ClassList::Unhovered(FString InName)
{
	for (const FUI_Class_Data& data : Datas)
	{
		UBorder* border = Cast<UBorder>(data.Class->GetWidgetFromName("Border_0"));

		if (data.Class->GetName() == InName)
		{
			border->SetBrushColor(FLinearColor::White);
		}
	}
}
