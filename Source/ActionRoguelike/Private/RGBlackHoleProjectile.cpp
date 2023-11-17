#include "RGBlackHoleProjectile.h"

#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ARGBlackHoleProjectile::ARGBlackHoleProjectile()
{
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->ForceStrength = -500000.0;
	RadialForceComponent->bImpulseVelChange = false;
	RadialForceComponent->Radius = 1000.0f;
	RadialForceComponent->bIgnoreOwningActor = true;	
	RadialForceComponent->AddCollisionChannelToAffect(ECollisionChannel::ECC_PhysicsBody);	

	EObjectTypeQuery ObjectType = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
	if (ObjectType != ObjectTypeQuery_MAX)
	{
		// Remove Pawn as an affected object type
		RadialForceComponent->RemoveObjectTypeToAffect(ObjectType);
	}
	RadialForceComponent->SetupAttachment(RootComponent);

	EffectComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}