#include "RGMagicProjectile.h"

#include "RGAttributesComponent.h"


void ARGMagicProjectile::Explode_Implementation(AActor* HitActor)
{
	if (HitActor && HitActor != GetInstigator())
	{
		if (auto* AttributesComponent = HitActor->GetComponentByClass<URGAttributesComponent>())
		{
			AttributesComponent->ApplyHealthChange(-DamageAmount);
		}
	}

	Super::Explode_Implementation(HitActor);
}