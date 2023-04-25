// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE_ProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_API AUE_ProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	class AC_Character* PlayerCharacter;
	class AC_Shinbi* Shinbi;
	
	TSubclassOf<class AC_Character> PlayerClass;
	TSubclassOf<class AC_Shinbi> ShinbiClass;
	TSubclassOf<class ALevelSequenceActor> SequenceActor;
	TSubclassOf<class AC_Enemy_AI_NormalMonster> enemyClass;

	bool bIsPlayingIntro = false;

public:

	AUE_ProjectGameModeBase();

	FORCEINLINE bool GetIntroState() { return bIsPlayingIntro; }

private:

	virtual void StartPlay() override;

	UFUNCTION()
		void DelayedStart();

	UFUNCTION()
		void EndIntroCutScene();

};
