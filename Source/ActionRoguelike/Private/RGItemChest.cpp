#include "RGItemChest.h"

ARGItemChest::ARGItemChest()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);
}

void ARGItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch,0,0));
}

void ARGItemChest::BeginPlay()
{
	Super::BeginPlay();
}

void ARGItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}