#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "C_FeetComponent.generated.h"

USTRUCT(BlueprintType)
struct FFeetData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector LeftDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector RightDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector PelvisDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator LeftRotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator RightRotation;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UE_PROJECT_API UC_FeetComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "InverseKinemetics")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		FName LeftSocket = "Foot_L";

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "InverseKinemetics")
		FName RightSocket = "Foot_R";

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float TraceDistance = 55;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float InterpSpeed = 20;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float OffsetDistance = 5;

public:
	FORCEINLINE FFeetData GetData() { return Data; }

public:
	UC_FeetComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool Trace(FName InSocket, float& OutDistance, FRotator& OutRotation);

private:
	class ACharacter* OwnerCharacter;

	FFeetData Data;
};
