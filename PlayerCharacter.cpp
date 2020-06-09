#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"

#include "PickableItemBase.h"
#include "PickableWeapon.h"

#include "Components/BoxComponent.h"

#include "AICharacter.h"
#include "Kismet/GameplayStatics.h"


void APlayerCharacter::BeginPlay() {

	Super::BeginPlay();


	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, 
		&APlayerCharacter::OnBeginOverlap);


}

void APlayerCharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (bIsAttacking) {
	
		if (WeaponCollider != nullptr) {
		
			WeaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

		}

	} else {
	
		if (WeaponCollider != nullptr) {

			WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		}

	}


}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Mouse_X", this, &APlayerCharacter::Mouse_X);
	PlayerInputComponent->BindAxis("Mouse_Y", this, &APlayerCharacter::Mouse_Y);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::TriggerAttack);

}

void APlayerCharacter::MoveForward(float Value)
{

	if (!bIsAlive)
		return;

	if (!bIsAttacking) {
	
		FRotator CamRot = GetControlRotation();
		CamRot.Pitch = 0.0f;
		FVector MoveDir = CamRot.Vector();

		GetCharacterMovement()->AddInputVector(MoveDir * Value);

	}


}

void APlayerCharacter::MoveRight(float Value)
{

	if (!bIsAlive)
		return;

	if (!bIsAttacking) {

		FRotator CamRot = GetControlRotation();
		CamRot.Pitch = 0.0f;
		FVector MoveDir = CamRot.RotateVector(FVector::RightVector);

		GetCharacterMovement()->AddInputVector(MoveDir * Value);

	}

}

void APlayerCharacter::Mouse_X(float Value)
{

	float Input = Value * 100.0f * GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(Input);

}

void APlayerCharacter::Mouse_Y(float Value)
{

	float Input = Value * 100.0f * GetWorld()->GetDeltaSeconds();
	AddControllerPitchInput(Input);

}

void APlayerCharacter::TriggerAttack()
{

	if (!bIsAlive)
		return;

	
	if (MyWeaponActor) {
	
		if (!AddedOverlapToWeapon) {
		
			AddedOverlapToWeapon = true;

			WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, 
				&APlayerCharacter::OnWeaponBeginOverlap);

		}

		CanDetectCollision = true;
		Attack();

	}

}


void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent * OverlapComp, 
	AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor->ActorHasTag("Shield")) {
	
		APickableItemBase* PickedShield = Cast<APickableItemBase>(OtherActor);
		PickShield(PickedShield);

	}

	if (OtherActor->ActorHasTag("Hammer")) {

		APickableWeapon* PickedWeapon = Cast<APickableWeapon>(OtherActor);
		PickWeapon(PickedWeapon);

	}
}

void APlayerCharacter::OnWeaponBeginOverlap(UPrimitiveComponent * OverlapComp, 
	AActor * OtherActor, UPrimitiveComponent * OtherComp, 
	int32 OtherBodyIndex, bool bSweepFrom, const FHitResult & SweepResult)
{

	if (OtherActor->ActorHasTag("Enemy")) {
	
		if (CanDetectCollision) {
		
			CanDetectCollision = false;

			AAICharacter* EnemyChar = Cast<AAICharacter>(OtherActor);
			bool EnemyDead = EnemyChar->ApplyDamage();

			if (EnemyDead) {
			
				FTimerHandle UnusedHandle;
				GetWorldTimerManager().SetTimer(
					UnusedHandle, this, &APlayerCharacter::RestartGame, 3.0f, false);

			}

		}

	}

}

bool APlayerCharacter::ApplyDamage()
{

	Health -= 10.0f;

	if (Health <= 0.0f) {
	
		bIsAlive = false;

		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(
			UnusedHandle, this, &APlayerCharacter::RestartGame, 3.0f, false);

		return true;

	}

	return false;
}

void APlayerCharacter::RestartGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

