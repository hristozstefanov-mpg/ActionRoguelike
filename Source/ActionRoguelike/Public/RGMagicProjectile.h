#pragma once

#include "CoreMinimal.h"
#include "RGBaseProjectile.h"
#include "RGMagicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARGMagicProjectile : public ARGBaseProjectile
{
	GENERATED_BODY()

public:

	ARGMagicProjectile();

	/** Explosion effect. */
	UPROPERTY(EditAnywhere, Category = Particles)
	class UParticleSystem* HitExplosionEffect;

	/** Damage amount dealth to whatever gets hit */
	UPROPERTY(EditAnywhere)
	float DamageAmount = 20.0f;

protected:

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void HandleCollision(AActor* OtherActor);
};