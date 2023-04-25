// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/C_PatrolComponent.h"
#include "Global.h"
#include "Enemy/C_PatrolPath.h"
#include "Components/SplineComponent.h"



// Sets default values for this component's properties
UC_PatrolComponent::UC_PatrolComponent()
{

}


// Called when the game starts
void UC_PatrolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


bool UC_PatrolComponent::GetMoveTo(FVector& OutLocation, float& OutAcceptanceRadius)
{
	OutLocation = FVector::ZeroVector;
	OutAcceptanceRadius = AcceptanceRadius;

	if (Path == nullptr) return false;

	OutLocation = Path->GetSpline()->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);

	return true;
}

void UC_PatrolComponent::UpdateNextIndex()
{
	if (Path == nullptr) return;

	int32 count = Path->GetSpline()->GetNumberOfSplinePoints();

	if (bReverse)
	{
		if (Index > 0)
		{
			Index--;
			return;
		}

		if (Path->GetSpline()->IsClosedLoop())
		{
			// 스플라인이 루프일경우 마지막 노드로 바꿔주는 코드
			Index = count - 1;
			return;
		}

		Index = 1;
		bReverse = false;
		return;
	}

	if (Index < count - 1)
	{
		Index++;
		return;
	}

	if (Path->GetSpline()->IsClosedLoop())
	{
		Index = 0;
		return;
	}

	Index = count - 2;
	bReverse = true;
}

