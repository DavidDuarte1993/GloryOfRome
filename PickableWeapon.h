#pragma once

#include "CoreMinimal.h"
#include "PickableItemBase.h"
#include "PickableWeapon.generated.h"

class UBoxComponent;
class USphereComponent;

UCLASS()
class GLADIATORARENA_API APickableWeapon : public APickableItemBase
{
	GENERATED_BODY()

public:
	
	APickableWeapon();

	virtual void BeginPlay() override;
	
	UBoxComponent* GetDamageBox() const;

protected:

	UPROPERTY(EditAnywhere)
		USphereComponent* MySphere;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* MySkeletalMesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* DamageBox;
	

	
};
