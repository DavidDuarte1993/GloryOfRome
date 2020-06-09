#include "ArenaCharacter.h"
#include "PickableItemBase.h"
#include "PickableWeapon.h"
#include "Components/BoxComponent.h"

AArenaCharacter::AArenaCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AArenaCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AArenaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArenaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AArenaCharacter::PickShield(APickableItemBase * pickedShield)
{

	if (!pickedShield)
		return false;

	if (!MyShieldActor) {
	
		if (pickedShield->AttachItemTo(GetMesh(), TEXT("DualWeaponPoint")) == true) {
		
			MyShieldActor = pickedShield;
			return true;

		}

	}

	return false;
}

bool AArenaCharacter::PickWeapon(APickableWeapon * pickedWeapon)
{

	if (!pickedWeapon)
		return false;

	if (!MyWeaponActor) {
	
		if (pickedWeapon->AttachItemTo(GetMesh(), TEXT("WeaponPoint")) == true) {
		
			MyWeaponActor = pickedWeapon;
			WeaponCollider = MyWeaponActor->GetDamageBox();

			WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			return true;

		}

	}

	return false;
}

void AArenaCharacter::Attack()
{
	bIsAttacking = true;
}

