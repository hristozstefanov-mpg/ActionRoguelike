#include "RGTeleportProjectile.h"

#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

ARGTeleportProjectile::ARGTeleportProjectile()
{
}

void ARGTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(SphereComponent);
	SphereComponent->OnComponentHit.AddDynamic(this, &ARGTeleportProjectile::OnHitCallback);

	GetWorldTimerManager().SetTimer(TimerHandle_Explosion, this, &ARGTeleportProjectile::TimeElapsed_Explosion, ProjectileLifetime);
}

void ARGTeleportProjectile::OnHitCallback(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Teleport();
}

void ARGTeleportProjectile::Teleport()
{
	APawn* InstigatorPawn = GetInstigator();
	if (ensure(InstigatorPawn))
	{
		InstigatorPawn->TeleportTo(GetActorLocation(), GetActorRotation());
	}
	Destroy();
}

void ARGTeleportProjectile::TimeElapsed_Explosion()
{
	SphereComponent->SetPhysicsLinearVelocity(FVector::Zero());
	EffectComponent->SetTemplate(ExplosionParticles);
	GetWorldTimerManager().SetTimer(TimerHandle_Explosion, this, &ARGTeleportProjectile::TimeElapsed_Teleport, TeleportAnimDuration);
}

void ARGTeleportProjectile::TimeElapsed_Teleport()
{
	Teleport();
}