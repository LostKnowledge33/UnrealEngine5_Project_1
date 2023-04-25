// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimeLineComponent.h"
#include "C_DamageText.generated.h"

UCLASS()
class UE_PROJECT_API AC_DamageText : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_DamageText();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE void SetAttacker(class AController* target) { EventInstigator = target; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void DamageTextTick(float data);

	UFUNCTION()
		void DamageTextFinish();

public:

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* DamageRender;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timeline", Meta = (AllowPrivateAccess = "true"))
		UCurveFloat* Curve1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timeline", meta = (AllowPrivateAccess = "true"))
		float LerpTimelineLength = 2.f;

	FTimeline LerpTimeline;

	class AController* EventInstigator;
};
