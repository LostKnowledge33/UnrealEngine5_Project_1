// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/C_Revenant.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"

AC_Revenant::AC_Revenant()
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "/Script/Engine.SkeletalMesh'/Game/ParagonRevenant/Characters/Heroes/Revenant/Meshes/Revenant.Revenant'");

	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -86));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "/Script/Engine.AnimBlueprint'/Game/ParagonRevenant/Characters/Heroes/Revenant/Animations/AnimBP_Revenant_Rigging.AnimBP_Revenant_Rigging_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	//CHelpers::GetAsset<UAnimMontage>(&Attack, "/Script/Engine.AnimMontage'/Game/ParagonShinbi/Characters/Heroes/Shinbi/Animations/PrimaryMelee_D_Slow_Montage.PrimaryMelee_D_Slow_Montage'");
}

void AC_Revenant::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("NormalAttack", EInputEvent::IE_Pressed, this, &AC_Revenant::NormalAttack);
}

void AC_Revenant::NormalAttack()
{

}

void AC_Revenant::WeaponEnableCollision()
{

}
