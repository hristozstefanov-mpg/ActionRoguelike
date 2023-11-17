#include "RGBaseProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

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
}