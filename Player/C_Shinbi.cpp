// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/C_Shinbi.h"
#include "Global.h"
#include "Player/C_ActionProcess.h"
#include "Components/C_ActionComponent.h"
#include "Components/C_StatusComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMesh.h"

AC_Shinbi::AC_Shinbi()
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "/Script/Engine.SkeletalMesh'/Game/ParagonShinbi/Characters/Heroes/Shinbi/Meshes/Shinbi.Shinbi'");

	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -86));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "/Script/Engine.AnimBlueprint'/Game/BluePrints/Character/Shinbi/ABP_Shinbi.ABP_Shinbi_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	CHelpers::CreateComponent<UCapsuleComponent>(this, &WeaponComp, "WeaponCollider", GetMesh());

	Status->HealthProcess(100);
}

//void AC_DoAction_Melee::OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter)
void AC_Shinbi::MyComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Action->GetWeaponCollisionState()) return;
	if (OtherActor == nullptr) return;
	if (this == OtherActor) return;
	if (OtherActor->GetClass() == this->GetClass()) return;

	Action->ActionProcess->OnComponentBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AC_Shinbi::MyComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Action->ActionProcess->OnComponentEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AC_Shinbi::BeginPlay()
{
	Super::BeginPlay();

	WeaponComp->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), FName("weapon_r"));
	WeaponComp->SetRelativeLocation(FVector(0, -60, 0));
	WeaponComp->SetRelativeRotation(FRotator(0, 0, 89.99999));
	WeaponComp->SetRelativeScale3D(FVector(-0.25f, 0.25f, 1.f));

	WeaponComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	WeaponComp->OnComponentBeginOverlap.AddDynamic(this, &AC_Shinbi::MyComponentBeginOverlap);
	WeaponComp->OnComponentEndOverlap.AddDynamic(this, &AC_Shinbi::MyComponentEndOverlap);
}

void AC_Shinbi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}