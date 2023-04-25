// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE_ProjectGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Particles/ParticleSystem.h"
#include "MovieSceneSequencePlayer.h"
#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"

#include "Global.h"
#include "UI/C_UI_ClassList.h"
#include "UI/C_UI_MainHUD.h"
#include "Player/C_Character.h"
#include "Player/C_Shinbi.h"
#include "Enemy/C_Enemy_AI_NormalMonster.h"





AUE_ProjectGameModeBase::AUE_ProjectGameModeBase()
{
	//CHelpers::GetClass<AC_Character>(&PlayerClass, "/Script/Engine.Blueprint'/Game/BluePrints/Character/Shinbi/BP_C_Shinbi.BP_C_Shinbi_C'");
	//CHelpers::GetAsset<AC_Shinbi>(&Shinbi, "/Script/Engine.Blueprint'/Game/BluePrints/Character/Shinbi/BP_C_Shinbi.BP_C_Shinbi'");
	CHelpers::GetClass<AC_Shinbi>(&ShinbiClass, "/Script/Engine.Blueprint'/Game/BluePrints/Character/Shinbi/BP_C_Shinbi.BP_C_Shinbi_C'");
	
	TSubclassOf<AC_UI_MainHUD> mainHUD;
	CHelpers::GetClass<AC_UI_MainHUD>(&mainHUD, "/Script/Engine.Blueprint'/Game/BluePrints/UI/BP_C_UI_MainHUD.BP_C_UI_MainHUD_C'");

	//CHelpers::GetClass<AC_Enemy_AI_NormalMonster>(&enemyClass, "/Script/Engine.Blueprint'/Game/BluePrints/Enemy/BP_C_Enemy_AI_NormalMonster.BP_C_Enemy_AI_NormalMonster_C'");

	HUDClass = mainHUD;
}

void AUE_ProjectGameModeBase::StartPlay()
{
	Super::StartPlay();

	//UKismetSystemLibrary::K2_SetTimer(this, "DelayedStart", 1.f, false);
	//
	
	if (!FString("MainWorld").Equals(UGameplayStatics::GetCurrentLevelName(GetWorld())))
	{
		//EndIntroCutScene();
		DelayedStart();
	}
}

void AUE_ProjectGameModeBase::DelayedStart()
{
	bIsPlayingIntro = true;

	ULevelSequence* LS;
	CHelpers::GetAssetDynamic<ULevelSequence>(&LS, "/Script/LevelSequence.LevelSequence'/Game/Sequences/LS_MainStageIntro.LS_MainStageIntro'");
	ALevelSequenceActor* LSA = Cast<ALevelSequenceActor>(UGameplayStatics::GetActorOfClass(GetWorld(), SequenceActor->StaticClass()));

	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LS, PlaybackSettings, LSA);

	// 시네머신 시퀀스가 끝나면 실행해야할 함수를 이벤트 할당 하였다.
	LevelSequencePlayer->OnFinished.AddDynamic(this, &AUE_ProjectGameModeBase::EndIntroCutScene);

	//player->SetActorRelativeLocation(FVector(-5812.106873, 4077.437538, 7545.904200));
	LevelSequencePlayer->Play();
}

void AUE_ProjectGameModeBase::EndIntroCutScene()
{
	FTransform tf;
	tf.SetLocation(FVector(-5770, 6757, 7206));
	tf.SetRotation(FRotator(0, -90, 0).Quaternion());

	AC_Shinbi* player = GetWorld()->SpawnActorAbsolute<AC_Shinbi>(ShinbiClass, tf);

	//tf.AddToTranslation(FVector(0, 0, 150));

	player->PlayAnimMontage(player->IntroMontage);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), player->IntroParticle, tf);

	bIsPlayingIntro = false;
}



