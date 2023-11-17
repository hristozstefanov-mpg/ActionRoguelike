#pragma once

#include "CoreMinimal.h"
#include "RGBaseProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARGBaseProjectile : public AActor
{
	GENERATED_BODY()

protected:

	/** Sphere component used for collision. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* SphereComponent;

	/** Movement component for the trajectory of the magic projectile. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UProjectileMovementComponent* MovementComponent;

	/** Effects particle system. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* EffectComponent;

public:

	ARGBaseProjectile();

protected:

	virtual void BeginPlay() override;
};