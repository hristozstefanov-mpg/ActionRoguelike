#include "RGTargetDummy.h"

#include "RGAttributesComponent.h"

ARGTargetDummy::ARGTargetDummy()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = MeshComponent;

	AttributesComponent = CreateDefaultSubobject<URGAttributesComponent>(TEXT("AttributesComponent"));		
}

void ARGTargetDummy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(AttributesComponent);
	AttributesComponent->OnHealthChanged.AddDynamic(this, &ARGTargetDummy::OnHealthChanged);
}

void ARGTargetDummy::OnHealthChanged(AActor* InstigatorActor, class URGAttributesComponent* OwningComponent, float NewHeath, float Delta)
{
	if ( Delta < 0.0f )
	{
		check(MeshComponent);
		MeshComponent->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}