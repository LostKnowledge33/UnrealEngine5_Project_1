// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectStage/C_SelectCharacter.h"

// Sets default values
AC_SelectCharacter::AC_SelectCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_SelectCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_SelectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_SelectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

