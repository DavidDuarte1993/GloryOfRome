#pragma once

#include "CoreMinimal.h"
#include "ArenaCharacter.h"
#include "AICharacter.generated.h"

UCLASS()
class GLADIATORARENA_API AAICharacter : public AArenaCharacter
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<APickableItemBase> Shield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<APickableWeapon> Weapon;

	void CreateAndAttachWeapons();

	UFUNCTION(BlueprintCallable)
	void TriggerAttack();

	UFUNCTION()
		virtual void OnWeaponBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweepFrom,
			const FHitResult & SweepResult);

	bool CanDetectCollision = false;
	bool DisableAttack;

	UPROPERTY(BlueprintReadOnly)
		float Health = 100.0f;

	bool ApplyDamage();

};
