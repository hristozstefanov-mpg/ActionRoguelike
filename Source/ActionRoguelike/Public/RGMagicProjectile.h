#pragma once

#include "CoreMinimal.h"
#include "RGMagicProjectile.generated.h"

UCLASS()
class ARGMagicProjectile : public AActor
{
	GENERATED_BODY()

protected:

	/** Sphere component used for collision. */
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComponent;

	/** Movement component for the trajectory of the magic projectile. */
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* MovementComponent;

	/** Effects particle system. */
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* EffectComponent;

public:

	ARGMagicProjectile();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};