#include "RGMagicProjectile.h"

#include "RGAttributesComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


ARGMagicProjectile::ARGMagicProjectile()
{
}

void ARGMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARGMagicProjectile::OnActorOverlap);
	SphereComponent->OnComponentHit.AddDynamic(this, &ARGMagicProjectile::OnActorHit);
}

void ARGMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HandleCollision(OtherActor);
}

void ARGMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	HandleCollision(OtherActor);
}

void ARGMagicProjectile::HandleCollision(AActor* OtherActor)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		if (auto* AttributesComponent = OtherActor->GetComponentByClass<URGAttributesComponent>())
		{
			AttributesComponent->ApplyHealthChange(-DamageAmount);
		}

		if (HitExplosionEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitExplosionEffect, GetActorLocation(), GetActorRotation(), true, EPSCPoolMethod::None, true);
		}

		Destroy();
	}
}