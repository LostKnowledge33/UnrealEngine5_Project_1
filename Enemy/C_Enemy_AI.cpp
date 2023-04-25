// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_Enemy_AI.h"
#include "Global.h"
#include "Components/C_PatrolComponent.h"

AC_Enemy_AI::AC_Enemy_AI()
{
	CHelpers::CreateActorComponent<UC_PatrolComponent>(this, &Patrol2, "Patrol");
}
