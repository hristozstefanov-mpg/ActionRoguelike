#include "RGBaseProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

ARGBaseProjectile::ARGBaseProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionProfileName(TEXT("Projectile"));	
	RootComponent = SphereComponent;

	EffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComponent"));
	EffectComponent->SetupAttachment(SphereComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->InitialSpeed = 1000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;
	MovementComponent->bRotationFollowsVelocity = true;
	MovementComponent->bInitialVelocityInLocalSpace = true;
}

void ARGBaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(SphereComponent);
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARGBaseProjectile::OnActorOverlap);
	SphereComponent->OnComponentHit.AddDynamic(this, &ARGBaseProjectile::OnActorHit);
}

void ARGBaseProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		Explode(OtherActor);
	}
}

void ARGBaseProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		Explode(OtherActor);
	}
}

void ARGBaseProjectile::Explode_Implementation(AActor* HitActor)
{
	if (!ensureMsgf(!IsPendingKill(), TEXT("The projectile is already being destroyed")))
	{
		return;
	}

	if (HitExplosionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitExplosionEffect, GetActorLocation(), GetActorRotation(), true, EPSCPoolMethod::None, true);
	}

	Destroy();
}