#include "RGExplodingBarrel.h"

#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ARGExplodingBarrel::ARGExplodingBarrel()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetCollisionProfileName("PhysicsActor");
	StaticMeshComponent->SetSimulatePhysics(true);
	RootComponent = StaticMeshComponent;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->ImpulseStrength = 2000.0;
	RadialForceComponent->bImpulseVelChange = true;
	RadialForceComponent->Radius = 1000.0f;
	RadialForceComponent->SetupAttachment(StaticMeshComponent);

	EffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionEffectComponent"));
	EffectComponent->SetAutoActivate(false);
	EffectComponent->SetupAttachment(StaticMeshComponent);
}

void ARGExplodingBarrel::BeginPlay()
{
	Super::BeginPlay();

	check(StaticMeshComponent);
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &ARGExplodingBarrel::OnHitCallback);
}

void ARGExplodingBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARGExplodingBarrel::OnHitCallback(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComponent->FireImpulse();
	EffectComponent->Activate(true);
}