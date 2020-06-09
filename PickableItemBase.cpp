#include "PickableItemBase.h"

APickableItemBase::APickableItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APickableItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void APickableItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool APickableItemBase::AttachItemTo(USkeletalMeshComponent * meshRoot, FName socket)
{

	if (IsUsed)
		return false;

	AttachToComponent(meshRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale, socket);

	SetActorRelativeLocation(FVector::ZeroVector);
	SetActorRelativeRotation(FRotator::ZeroRotator);

	IsUsed = true;

	return true;
}

