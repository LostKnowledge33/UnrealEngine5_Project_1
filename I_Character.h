// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_Character.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_Character : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE_PROJECT_API II_Character
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	// 이 클래스에 인터페이스 기능을 추가합니다. 이 인터페이스를 구현하기 위해 상속되는 클래스입니다.
public:

	virtual void ChangeColor(FLinearColor InColor) = 0;

};
