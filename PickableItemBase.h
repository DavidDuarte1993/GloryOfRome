#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableItemBase.generated.h"

UCLASS()
class GLADIATORARENA_API APickableItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APickableItemBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	bool AttachItemTo(USkeletalMeshComponent* meshRoot, FName socket);

	bool IsUsed;

};
