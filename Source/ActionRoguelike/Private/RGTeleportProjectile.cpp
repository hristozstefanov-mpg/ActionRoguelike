#include "RGTeleportProjectile.h"

#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ARGTeleportProjectile::ARGTeleportProjectile()
{
}

void ARGTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_Explosion, this, &ARGTeleportProjectile::TimeElapsed_Explode, ProjectileLifetime);
}

void ARGTeleportProjectile::TimeElapsed_Explode()
{
	Explode(nullptr);
}

void ARGTeleportProjectile::Explode_Implementation(AActor* HitActor)
{
	SphereComponent->SetPhysicsLinearVelocity(FVector::Zero());
	MovementComponent->StopMovementImmediately();
	EffectComponent->SetTemplate(ExplosionParticles);
	GetWorldTimerManager().SetTimer(TimerHandle_Explosion, this, &ARGTeleportProjectile::TimeElapsed_Teleport, TeleportAnimDuration);
}

void ARGTeleportProjectile::TimeElapsed_Teleport()
{
	APawn* InstigatorPawn = GetInstigator();
	if (ensure(InstigatorPawn))
	{
		InstigatorPawn->TeleportTo(GetActorLocation(), GetActorRotation());
	}

	Destroy();
}