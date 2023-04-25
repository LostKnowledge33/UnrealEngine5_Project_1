#include "Components/C_FeetComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"


UC_FeetComponent::UC_FeetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UC_FeetComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UC_FeetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float leftDistance;
	FRotator leftRotation;
	if (!Trace(LeftSocket, leftDistance, leftRotation)) return;

	float rightDistance;
	FRotator rightRotation;
	if (!Trace(RightSocket, rightDistance, rightRotation)) return;

	float offset = FMath::Min(leftDistance, rightDistance);
	Data.PelvisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PelvisDistance.Z, offset, DeltaTime, InterpSpeed);

	Data.LeftDistance.X = UKismetMathLibrary::FInterpTo(Data.LeftDistance.X, (leftDistance - offset), DeltaTime, InterpSpeed);
	Data.RightDistance.X = UKismetMathLibrary::FInterpTo(Data.RightDistance.X, -(rightDistance - offset), DeltaTime, InterpSpeed);

	Data.LeftRotation = UKismetMathLibrary::RInterpTo(Data.LeftRotation, leftRotation, DeltaTime, InterpSpeed);
	Data.RightRotation = UKismetMathLibrary::RInterpTo(Data.RightRotation, rightRotation, DeltaTime, InterpSpeed);
}

bool UC_FeetComponent::Trace(FName InSocket, float& OutDistance, FRotator& OutRotation)
{
	OutDistance = 0.0f;

	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation(InSocket);
	FVector start = FVector(location.X, location.Y, OwnerCharacter->GetActorLocation().Z);

	float traceZ = start.Z - OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - TraceDistance;
	FVector end = FVector(location.X, location.Y, traceZ);

	//DrawDebugLine(OwnerCharacter->GetWorld(), start, end, FColor::Green);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	FHitResult hitResult;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), true, ignoreActors, DrawDebugType,
		hitResult, true);

	if (!hitResult.IsValidBlockingHit()) return false;

	float length = (hitResult.ImpactPoint - hitResult.TraceEnd).Size();
	OutDistance = OffsetDistance + length - TraceDistance;

	FVector normal = hitResult.ImpactNormal;
	float roll = UKismetMathLibrary::DegAtan2(normal.Y, normal.Z);
	float pitch = -UKismetMathLibrary::DegAtan2(normal.X, normal.Z);

	OutRotation = FRotator(pitch, 0.0f, roll);

	return true;
}

