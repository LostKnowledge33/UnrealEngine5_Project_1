// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/C_Enemy_AI_NormalMonster.h"
#include "Global.h"
#include "Components/C_ActionComponent.h"
#include "Player/C_ActionProcess.h"
#include "Enemy/C_AIController.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMesh.h"

AC_Enemy_AI_NormalMonster::AC_Enemy_AI_NormalMonster()
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "/Script/Engine.SkeletalMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Gruntling/SK_Exodus_Gruntling.SK_Exodus_Gruntling'");
	GetMesh()->SetSkeletalMesh(mesh);

	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Weapon, "WeaponMesh", GetMesh());
	CHelpers::CreateComponent<UCapsuleComponent>(this, &WeaponCollision, "WeaponCollision", Weapon);

	CHelpers::GetAsset<USkeletalMesh>(&mesh, "/Script/Engine.SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight'");

	Weapon->SetSkeletalMesh(mesh);

	isStuned = true;
//	CHelpers::GetClass<AC_AIController>(&AiClass, "/Script/Engine.Blueprint'/Game/BluePrints/BP_C_AIController.BP_C_AIController_C'");
//	AIControllerClass = AiClass;
}

void AC_Enemy_AI_NormalMonster::MyComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetAction()->GetWeaponCollisionState()) return;
	if (OtherActor == nullptr) return;
	if (this == OtherActor) return;
	if (OtherActor->GetClass() == this->GetClass()) return;

	GetAction()->ActionProcess->OnComponentBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AC_Enemy_AI_NormalMonster::MyComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetAction()->ActionProcess->OnComponentEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AC_Enemy_AI_NormalMonster::BeginPlay()
{
	Super::BeginPlay();
	
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("WeaponSocket"));

	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AC_Enemy_AI_NormalMonster::MyComponentBeginOverlap);
	WeaponCollision->OnComponentEndOverlap.AddDynamic(this, &AC_Enemy_AI_NormalMonster::MyComponentEndOverlap);
}
