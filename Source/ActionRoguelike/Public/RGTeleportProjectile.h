#pragma once

#include "CoreMinimal.h"
#include "RGBaseProjectile.h"
#include "RGTeleportProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARGTeleportProjectile : public ARGBaseProjectile
{
	GENERATED_BODY()

protected:

	/** Teleportation particle explosion. */
	UPROPERTY(EditAnywhere, Category = Particles)
	class UParticleSystem* ExplosionParticles;

	/** Duration of the projectile flight. */
	UPROPERTY(EditAnywhere)
	float ProjectileLifetime = 0.5f;

	/** Duration of the projectile flight. */
	UPROPERTY(EditAnywhere)
	float TeleportAnimDuration = 0.2f;

public:

	ARGTeleportProjectile();

protected:

	virtual void BeginPlay() override;
	void Teleport();

	void TimeElapsed_Explosion();
	void TimeElapsed_Teleport();

	UFUNCTION()
	void OnHitCallback(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

protected:

	FTimerHandle TimerHandle_Explosion;
	FTimerHandle TimerHandle_Teleport;
};